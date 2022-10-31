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

#include "sql/operator/operator.h"
#include <queue>

class OrderByOperator : public Operator {
public:
  OrderByOperator(const std::vector<Field> &order_fields) : order_fields_(order_fields)
  {}

  virtual ~OrderByOperator()
  {}

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

private:
  void do_sort();
  const std::vector<Field> &order_fields_;
  std::deque<Tuple *> tuples_;
};
