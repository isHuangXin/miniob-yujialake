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

#include "sql/expr/tuple.h"
#include "sql/parser/parse.h"
#include "sql/operator/operator.h"
#include "rc.h"
#include "sql/stmt/filter_stmt.h"

// TODO fixme
class JoinOperator : public Operator {
public:
  JoinOperator(Operator *left, Operator *right, FilterStmt *filter = nullptr)
      : left_(left), right_(right), filter_(filter)
  {}

  virtual ~JoinOperator()
  {
    if (left_) {
      delete left_;
    }
    if (right_) {
      delete right_;
    }
  }

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

private:
  RC next_internal();
  bool do_predicate(JoinTuple &tuple);
  JoinTuple *tuple_ = nullptr;
  Operator *left_ = nullptr;
  Operator *right_ = nullptr;
  FilterStmt *filter_ = nullptr;
  bool round_done_ = false;
};
