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
// Created by WangYunlai on 2021/6/10.
//

#pragma once

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/operator.h"
#include "rc.h"
#include "sql/parser/parse_defs.h"
#include <vector>

// TODO fixme
class AggrOperator : public Operator {
public:
  AggrOperator(const std::vector<Field> &aggr_fields)
      : aggr_fields_(aggr_fields), aggr_tuple(new AggrTuple), is_aggr(false)
  {
    for (auto i = 0; i < aggr_fields.size(); i++) {
      TupleCell cell;
      aggr_tuple->add_cell(cell);
      aggr_tuple->add_cell_spec(new TupleCellSpec(new FieldExpr(aggr_fields[i].table(), aggr_fields[i].meta())));
    }
  }

  virtual ~AggrOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

private:
  RC do_aggr_max(const int index, TupleCell &cell);
  RC do_aggr_min(const int index, TupleCell &cell);
  RC do_aggr_avg(const int index, TupleCell &cell);
  RC do_aggr_sum(const int index, TupleCell &cell);
  RC do_aggr_count(const int index, TupleCell &cell);
  AttrType get_return_type(const Field &aggr_field) const;
  const std::vector<Field> &aggr_fields_;
  std::vector<std::vector<TupleCell>> tuples_;
  AggrTuple *aggr_tuple;
  bool is_aggr;
};
