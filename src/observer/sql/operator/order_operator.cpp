/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Tanziyi on 2022/10/22.
//

#include "sql/operator/order_operator.h"
#include <algorithm>

RC OrderByOperator::open()
{
  if (order_fields_.empty()) {
    return children_[0]->open();
  }

  RC rc = RC::SUCCESS;
  if ((rc = children_[0]->open()) != RC::SUCCESS) {
    return rc;
  }

  // 取出所有元素，等待排序
  while (children_[0]->next() == RC::SUCCESS) {
    Tuple *tuple = children_[0]->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("tuple should not be null!");
      return RC::INTERNAL;
    }
    tuples_.push_back(new OrderByTuple(tuple));
  }

  do_sort();
  return rc;
}

void OrderByOperator::do_sort()
{
  std::sort(tuples_.begin(), tuples_.end(), [this](const Tuple *lhs, const Tuple *rhs) {
    TupleCell left_cell;
    TupleCell right_cell;
    int compare = 0;
    for (const Field &order_field : order_fields_) {
      lhs->find_cell(order_field, left_cell);
      rhs->find_cell(order_field, right_cell);
      compare = left_cell.compare(right_cell);
      if (compare == 0) {
        continue;
      }
      return order_field.is_desc() ? compare > 0 : compare < 0;
    }
    return order_fields_.back().is_desc() ? compare > 0 : compare < 0;
  });
}

RC OrderByOperator::next()
{
  if (order_fields_.empty()) {
    return children_[0]->next();
  }

  return tuples_.empty() ? RC::RECORD_EOF : RC::SUCCESS;
}

RC OrderByOperator::close()
{
  return children_[0]->close();
}

Tuple *OrderByOperator::current_tuple()
{
  if (order_fields_.empty()) {
    return children_[0]->current_tuple();
  }

  Tuple *tuple = tuples_.front();
  tuples_.pop_front();
  return tuple;
}
