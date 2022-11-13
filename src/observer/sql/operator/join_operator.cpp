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

#include "sql/operator/join_operator.h"

RC JoinOperator::open()
{
  if (left_ == nullptr || right_ == nullptr) {
    LOG_WARN("join operator must has 2 children");
    return RC::INTERNAL;
  }

  RC rc = RC::SUCCESS;
  if ((rc = left_->open()) != RC::SUCCESS) {
    return rc;
  }

  if (left_->next() != RC::SUCCESS) {
    round_done_ = true;
  }

  return right_->open();
}

RC JoinOperator::next_internal()
{
  RC rc = RC::SUCCESS;
  // 右表遍历结束，重新遍历
  if ((rc = right_->next()) != RC::SUCCESS && (right_->open() == RC::SUCCESS) && (right_->next() == RC::SUCCESS)) {
    rc = left_->next();
  }
  return rc;
}

RC JoinOperator::next()
{
  if (round_done_) {
    return RC::RECORD_EOF;
  }

  RC rc = RC::SUCCESS;
  while (RC::SUCCESS == (rc = next_internal())) {
    Tuple *tuple = current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    if (do_predicate(static_cast<JoinTuple &>(*tuple))) {
      return rc;
    }
  }

  return rc;
}

RC JoinOperator::close()
{
  if (left_ == nullptr || right_ == nullptr) {
    LOG_WARN("join operator must has 2 children");
    return RC::INTERNAL;
  }

  RC rc = RC::SUCCESS;
  if ((rc = left_->close()) != RC::SUCCESS) {
    return rc;
  }

  return right_->close();
}

Tuple *JoinOperator::current_tuple()
{
  if (nullptr == left_->current_tuple() || nullptr == right_->current_tuple()) {
    return nullptr;
  }
  return new JoinTuple(left_->current_tuple(), right_->current_tuple());
}

bool JoinOperator::do_predicate(JoinTuple &tuple)
{
  if (filter_ == nullptr || filter_->filter_units().empty()) {
    return true;
  }

  for (const FilterUnit *filter_unit : filter_->filter_units()) {
    Expression *left_expr = filter_unit->left();
    Expression *right_expr = filter_unit->right();
    CompOp comp = filter_unit->comp();
    TupleCell left_cell;
    TupleCell right_cell;
    left_expr->get_value(tuple, left_cell);
    right_expr->get_value(tuple, right_cell);

    // IS NULL or IS NOT NULL
    if (comp == IS_OP && right_cell.attr_type() == NULLS) {
      return left_cell.attr_type() == NULLS;
    } else if (comp == IS_NOT_OP && right_cell.attr_type() == NULLS) {
      return left_cell.attr_type() != NULLS;
    }

    if (left_cell.attr_type() == NULLS || right_cell.attr_type() == NULLS) {
      return false;
    }

    bool like_comp = (comp == LIKE || comp == NOT_LIKE);
    int compare = 1;
    if (like_comp) {
      compare = left_cell.compare_like(right_cell);
    } else {
      compare = left_cell.compare(right_cell);
    }
    bool filter_result = false;
    switch (comp) {
      case LIKE:
      case EQUAL_TO: {
        filter_result = (0 == compare);
      } break;
      case LESS_EQUAL: {
        filter_result = (compare <= 0);
      } break;
      case NOT_LIKE:
      case NOT_EQUAL: {
        filter_result = (compare != 0);
      } break;
      case LESS_THAN: {
        filter_result = (compare < 0);
      } break;
      case GREAT_EQUAL: {
        filter_result = (compare >= 0);
      } break;
      case GREAT_THAN: {
        filter_result = (compare > 0);
      } break;
      default: {
        LOG_WARN("invalid compare type: %d", comp);
      } break;
    }
    if (!filter_result) {
      return false;
    }
  }
  return true;
}
