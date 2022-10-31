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

#include "sql/operator/aggr_operator.h"
#include "common/lang/string.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/field_meta.h"
#include "storage/common/table.h"
#include "util/typecast.h"
#include "rc.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

RC AggrOperator::open()
{
  return children_[0]->open();
}

RC AggrOperator::next()
{
  if (aggr_fields_.empty()) {
    return children_[0]->next();
  }

  while (RC::SUCCESS == children_[0]->next()) {
    std::vector<TupleCell> cells;
    Tuple *tuple = children_[0]->current_tuple();
    aggr_tuple->set_tuple(tuple);
    for (const auto &field : aggr_fields_) {
      TupleCell cell;
      if (field.aggr_param().empty()) {
        tuple->find_cell(field, cell);
      }
      cells.push_back(cell);
    }
    tuples_.push_back(cells);
  }

  // 每一列分别做聚合
  for (int i = 0; i < aggr_fields_.size(); i++) {
    const auto &field = aggr_fields_[i];
    TupleCell &res_cell = aggr_tuple->cell_at(i);
    // 参数为常数
    if (field.aggr_type() != COUNT && !field.aggr_param().empty()) {
      const char *data = field.aggr_param().data();
      res_cell.set_type(CHARS);
      res_cell.set_length(field.aggr_param().size());
      res_cell.set_data(strdup(data));
      break;
    }
    switch (field.aggr_type()) {
      case COUNT:
        do_aggr_count(i, res_cell);
        break;
      case MAX:
        do_aggr_max(i, res_cell);
        break;
      case MIN:
        do_aggr_min(i, res_cell);
        break;
      case AVG:
        do_aggr_avg(i, res_cell);
        break;
      case SUM:
        do_aggr_sum(i, res_cell);
        break;
      default:
        return RC::RECORD_EOF;
    }
  }

  return is_aggr ? RC::RECORD_EOF : RC::SUCCESS;
}

RC AggrOperator::close()
{
  return children_[0]->close();
}

Tuple *AggrOperator::current_tuple()
{
  if (aggr_fields_.empty()) {
    return children_[0]->current_tuple();
  }

  is_aggr = true;
  return aggr_tuple;
}

AttrType AggrOperator::get_return_type(const Field &aggr_field) const
{
  switch (aggr_field.aggr_type()) {
    case COUNT:
      return INTS;
      break;
    case MAX:
    case MIN:
      if (!common::is_blank(aggr_field.field_name())) {
        return aggr_field.attr_type();
      }
      return CHARS;
      break;
    case AVG:
      return FLOATS;
    case SUM:
      if (!common::is_blank(aggr_field.field_name())) {
        if (aggr_field.attr_type() == CHARS) {
          return FLOATS;
        }
        return aggr_field.attr_type();
      }
      return FLOATS;
      break;
    default:
      return UNDEFINED;
  }
}

RC AggrOperator::do_aggr_max(const int index, TupleCell &res_cell)
{
  RC rc = RC::SUCCESS;
  res_cell = tuples_[0][index];

  // 获取每列对应字段的数据
  for (size_t i = 1; i < tuples_.size(); i++) {
    TupleCell rhs = tuples_[i][index];
    if (res_cell.compare(rhs) < 0) {
      res_cell = rhs;
    }
  }
  return rc;
}
RC AggrOperator::do_aggr_min(const int index, TupleCell &res_cell)
{
  RC rc = RC::SUCCESS;
  res_cell = tuples_[0][index];

  // 获取每列对应字段的数据
  for (size_t i = 1; i < tuples_.size(); i++) {
    TupleCell rhs = tuples_[i][index];
    if (res_cell.compare(rhs) > 0) {
      res_cell = rhs;
    }
  }

  return rc;
}
RC AggrOperator::do_aggr_avg(const int index, TupleCell &res_cell)
{
  RC rc = RC::SUCCESS;

  float res = 0;
  int cnt = 0;
  // 获取每列对应字段的数据
  for (size_t i = 0; i < tuples_.size(); i++) {
    TupleCell cell = tuples_[i][index];
    switch (cell.attr_type()) {
      case INTS: {
        res += *(int *)cell.data();
        cnt++;
      } break;
      case FLOATS: {
        res += *(float *)cell.data();
        cnt++;
      } break;
      // 字符类型需要隐式转换float
      case CHARS: {
        res += chars_to_floats(cell.data());
        cnt++;
      } break;
      default: {
        continue;
      }
    }
  }

  res_cell.set_type(FLOATS);
  size_t length = sizeof(float) + 1;
  char *data = new char[length];
  memset(data, 0, length);
  res_cell.set_length(length);
  if (cnt != 0) {
    res /= cnt;
  }
  memcpy(data, &res, length - 1);
  res_cell.set_data(data);
  return rc;
}

RC AggrOperator::do_aggr_sum(const int index, TupleCell &res_cell)
{
  RC rc = RC::SUCCESS;

  float res = 0;
  // 获取每列对应字段的数据
  for (size_t i = 0; i < tuples_.size(); i++) {
    TupleCell cell = tuples_[i][index];
    switch (cell.attr_type()) {
      case INTS: {
        res += *(int *)cell.data();
      } break;
      case FLOATS: {
        res += *(float *)cell.data();
      } break;
      case CHARS: {
        res += chars_to_floats(cell.data());
      } break;
      default: {
        continue;
      }
    }
  }
  res_cell.set_type(aggr_fields_[index].attr_type());
  if (aggr_fields_[index].attr_type() == CHARS) {
    res_cell.set_type(FLOATS);
  }
  size_t length = sizeof(float) + 1;
  char *data = new char[length];
  memset(data, 0, length);
  res_cell.set_length(length);
  if (res_cell.attr_type() == INTS) {
    int i_res = res;
    memcpy(data, &i_res, sizeof(int));
  } else {
    memcpy(data, &res, length - 1);
  }

  res_cell.set_data(data);
  return rc;
}

RC AggrOperator::do_aggr_count(const int index, TupleCell &res_cell)
{
  RC rc = RC::SUCCESS;
  int cnt = 0;
  for (size_t i = 0; i < tuples_.size(); i++) {
    cnt++;
  }
  res_cell.set_type(INTS);
  size_t length = sizeof(int) + 1;
  char *data = new char[length];
  memset(data, 0, length);
  res_cell.set_length(length);
  memcpy(data, &cnt, length - 1);
  res_cell.set_data(data);
  return rc;
}
