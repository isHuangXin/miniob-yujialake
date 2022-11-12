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
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <bitset>
#include <memory>
#include <vector>

#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/expression.h"
#include "storage/record/record.h"

class Table;

class TupleCellSpec {
public:
  TupleCellSpec() = default;
  TupleCellSpec(Expression *expr) : expression_(expr)
  {}

  ~TupleCellSpec()
  {
    if (expression_) {
      delete expression_;
      expression_ = nullptr;
    }
  }

  void set_alias(const char *alias)
  {
    this->alias_ = alias;
  }
  const char *alias() const
  {
    return alias_;
  }

  Expression *expression() const
  {
    return expression_;
  }

private:
  const char *alias_ = nullptr;
  Expression *expression_ = nullptr;
};

class Tuple {
public:
  Tuple() = default;
  virtual ~Tuple() = default;

  virtual int cell_num() const = 0;
  virtual RC cell_at(int index, TupleCell &cell) const = 0;
  virtual RC find_cell(const Field &field, TupleCell &cell) const = 0;
  /**
   * @brief tuple cell index in a tuple
   *
   * @param field
   * @return int index
   */
  virtual int find_cell_index(const Field &field) const = 0;

  virtual RC cell_spec_at(int index, const TupleCellSpec *&spec) const = 0;
};

class RowTuple : public Tuple {
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_record(Record *record)
  {
    this->record_ = record;
  }

  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new TupleCellSpec(new FieldExpr(table, &field)));
    }
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    const TupleCellSpec *spec = speces_[index];
    FieldExpr *field_expr = (FieldExpr *)spec->expression();
    const FieldMeta *field_meta = field_expr->field().meta();
    cell.set_type(field_meta->type());
    cell.set_data(this->record_->data() + field_meta->offset());
    std::bitset<32> null_map(*(int *)this->record_->data());
    // 检查标志位
    const int sys_field_num = table_->table_meta().sys_field_num();
    if (index >= sys_field_num && null_map.test(index - sys_field_num)) {
      cell.set_type(NULLS);
    }
    cell.set_length(field_meta->len());
    return RC::SUCCESS;
  }

  int find_cell_index(const Field &field) const override
  {
    const char *table_name = field.table_name();
    if (0 != strcmp(table_name, table_->name())) {
      return -1;
    }

    const char *field_name = field.field_name();
    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = (const FieldExpr *)speces_[i]->expression();
      const Field &field = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return i;
      }
    }

    return -1;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const int idx = find_cell_index(field);
    return idx == -1 ? RC::NOTFOUND : cell_at(idx, cell);
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  Record &record()
  {
    return *record_;
  }

  const Record &record() const
  {
    return *record_;
  }

private:
  Record *record_ = nullptr;
  const Table *table_ = nullptr;
  std::vector<TupleCellSpec *> speces_;
};

/*
class CompositeTuple : public Tuple
{
public:
  int cell_num() const override;
  RC  cell_at(int index, TupleCell &cell) const = 0;
private:
  int cell_num_ = 0;
  std::vector<Tuple *> tuples_;
};
*/

class AggrTuple : public Tuple {
public:
  AggrTuple() = default;
  virtual ~AggrTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple)
  {
    this->tuple_ = tuple;
  }

  void add_cell_spec(TupleCellSpec *spec)
  {
    speces_.push_back(spec);
  }

  void add_cell(TupleCell &cell)
  {
    cells_.push_back(cell);
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::GENERIC_ERROR;
    }
    if (tuple_ == nullptr) {
      return RC::GENERIC_ERROR;
    }

    cell = cells_[index];
    return RC::SUCCESS;
  }

  TupleCell &cell_at(int index)
  {
    return cells_[index];
  }

  int find_cell_index(const Field &field) const override
  {
    const char *field_name = field.field_name();
    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = (const FieldExpr *)speces_[i]->expression();
      const Field &field = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return i;
      }
    }

    return -1;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const int idx = find_cell_index(field);
    if (idx == -1) {
      return RC::NOTFOUND;
    }

    return cell_at(idx, cell);
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

private:
  Tuple *tuple_ = nullptr;
  std::vector<TupleCellSpec *> speces_;
  std::vector<TupleCell> cells_;
};

class OrderByTuple : public Tuple {
public:
  OrderByTuple() = default;
  OrderByTuple(Tuple *tuple) : tuple_(tuple)
  {
    for (size_t i = 0; i < tuple_->cell_num(); i++) {
      TupleCell cell;
      tuple->cell_at(i, cell);
      cells_.push_back(cell);
    }
  }
  virtual ~OrderByTuple() = default;

  int cell_num() const override
  {
    return cells_.size();
  }

  int find_cell_index(const Field &field) const override
  {
    return tuple_->find_cell_index(field);
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(cell_num())) {
      return RC::GENERIC_ERROR;
    }
    if (tuple_ == nullptr) {
      return RC::GENERIC_ERROR;
    }

    cell = cells_[index];
    return RC::SUCCESS;
  }

  TupleCell &cell_at(int index)
  {
    return cells_[index];
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const int idx = find_cell_index(field);
    if (idx == -1) {
      return RC::NOTFOUND;
    }

    cell = cells_[idx];
    return RC::SUCCESS;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    return tuple_->cell_spec_at(index, spec);
  }

private:
  Tuple *tuple_ = nullptr;
  std::vector<TupleCell> cells_;
};

class ProjectTuple : public Tuple {
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple)
  {
    this->tuple_ = tuple;
  }

  void add_cell_spec(TupleCellSpec *spec)
  {
    speces_.push_back(spec);
  }
  int cell_num() const override
  {
    return speces_.size();
  }

  int find_cell_index(const Field &field) const override
  {
    return tuple_->find_cell_index(field);
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::GENERIC_ERROR;
    }
    if (tuple_ == nullptr) {
      return RC::GENERIC_ERROR;
    }

    if (dynamic_cast<AggrTuple *>(tuple_)) {
      return tuple_->cell_at(index, cell);
    }

    const TupleCellSpec *spec = speces_[index];
    return spec->expression()->get_value(*tuple_, cell);
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    return tuple_->find_cell(field, cell);
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

private:
  std::vector<TupleCellSpec *> speces_;
  Tuple *tuple_ = nullptr;
};

class JoinTuple : public Tuple {
public:
  JoinTuple() = default;
  JoinTuple(Tuple *left, Tuple *right) : left_(left), right_(right)
  {}
  virtual ~JoinTuple()
  {}

  int cell_num() const override
  {
    return left_->cell_num() + right_->cell_num();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(cell_num())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    Tuple *tuple = index < left_->cell_num() ? left_ : right_;
    if (index >= left_->cell_num()) {
      index = index - left_->cell_num();
    }

    return tuple->cell_at(index, cell);
  }

  int find_cell_index(const Field &field) const override
  {
    int left_idx = -1;
    if ((left_idx = left_->find_cell_index(field)) != -1) {
      return left_idx;
    }
    int right_idx = -1;
    if ((right_idx = right_->find_cell_index(field)) != -1) {
      return left_->cell_num() + right_idx;
    }
    return -1;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    RC rc = RC::SUCCESS;
    rc = left_->find_cell(field, cell);
    if (rc == RC::SUCCESS) {
      return rc;
    }

    return right_->find_cell(field, cell);
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(cell_num())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    Tuple *tuple = index < left_->cell_num() ? left_ : right_;
    if (index >= left_->cell_num()) {
      index = index - left_->cell_num();
    }

    return tuple->cell_spec_at(index, spec);
  }

private:
  Tuple *left_;
  Tuple *right_;
};
