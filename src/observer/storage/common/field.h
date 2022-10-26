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

#include "storage/common/table.h"
#include "storage/common/field_meta.h"

class Field {
public:
  Field() = default;
  Field(const Table *table, const FieldMeta *field) : table_(table), field_(field), aggr_type_(INVALID)
  {}

  const Table *table() const
  {
    return table_;
  }
  const FieldMeta *meta() const
  {
    return field_;
  }

  AttrType attr_type() const
  {
    return field_->type();
  }

  AggrType aggr_type() const
  {
    return aggr_type_;
  }

  void set_aggr_type(AggrType type)
  {
    this->aggr_type_ = type;
  }

  const std::string &aggr_param() const
  {
    return aggr_param_;
  }

  void set_aggr_param(std::string param)
  {
    this->aggr_param_ = param;
  }

  const char *table_name() const
  {
    return table_->name();
  }
  const char *field_name() const
  {
    return field_->name();
  }

  void set_table(const Table *table)
  {
    this->table_ = table;
  }
  void set_field(const FieldMeta *field)
  {
    this->field_ = field;
  }

private:
  const Table *table_ = nullptr;
  const FieldMeta *field_ = nullptr;
  AggrType aggr_type_;
  std::string aggr_param_;
};
