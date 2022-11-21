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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <string.h>
#include "storage/common/field.h"
#include "sql/expr/tuple_cell.h"

class Tuple;

enum class ExprType { NONE, FIELD, VALUE, SUB_SELECT };

class Expression {
public:
  Expression() = default;
  virtual ~Expression() = default;

  virtual RC get_value(const Tuple &tuple, TupleCell &cell) const = 0;
  virtual ExprType type() const = 0;
  virtual bool in(const TupleCell &cell) const
  {
    return RC::UNIMPLENMENT;
  }

  virtual bool not_in(const TupleCell &cell) const
  {
    return RC::UNIMPLENMENT;
  }
};

class FieldExpr : public Expression {
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field)
  {}

  virtual ~FieldExpr() = default;

  ExprType type() const override
  {
    return ExprType::FIELD;
  }

  Field &field()
  {
    return field_;
  }

  const Field &field() const
  {
    return field_;
  }

  const char *table_name() const
  {
    return field_.table_name();
  }

  const char *field_name() const
  {
    return field_.field_name();
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;

private:
  Field field_;
};

class ValueExpr : public Expression {
public:
  ValueExpr() = default;
  ValueExpr(const Value &value) : tuple_cell_(value.type, (char *)value.data)
  {
    if (value.type == CHARS) {
      tuple_cell_.set_length(strlen((const char *)value.data));
    }
  }

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;
  ExprType type() const override
  {
    return ExprType::VALUE;
  }

  void get_tuple_cell(TupleCell &cell) const
  {
    cell = tuple_cell_;
  }

private:
  TupleCell tuple_cell_;
};

class SelectStmt;
class SubSelectExpr : public Expression {
public:
  SubSelectExpr(SelectStmt *select_stmt) : select_stmt_(select_stmt)
  {}

  ~SubSelectExpr() = default;

  RC get_value(const Tuple &tuple, TupleCell &cell) const override
  {
    return RC::UNIMPLENMENT;
  }

  ExprType type() const override
  {
    return ExprType::SUB_SELECT;
  }

  void get_tuple_cell(TupleCell &cell) const
  {}

  bool in(const TupleCell &cell) const override;
  bool not_in(const TupleCell &cell) const override;

private:
  void execute();

private:
  SelectStmt *select_stmt_ = nullptr;
  std::vector<Tuple *> tuples_;
  bool is_executed = false;
};
