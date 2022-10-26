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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/operator/project_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"

RC ProjectOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("project operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectOperator::next()
{
  return children_[0]->next();
}

RC ProjectOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}
Tuple *ProjectOperator::current_tuple()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}

const char *get_func_name(AggrType type)
{
  switch (type) {
    case MAX:
      return "max";
    case MIN:
      return "min";
    case AVG:
      return "avg";
    case SUM:
      return "sum";
    case COUNT:
      return "count";
    default:
      return "unknown";
  }
}

void ProjectOperator::add_projection(const Field &field, bool is_multi_mode = false)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  const Table *table = field.table();
  const FieldMeta *field_meta = field.meta();
  bool is_aggr = field.aggr_type() != INVALID;
  const char *func_name = is_aggr ? get_func_name(field.aggr_type()) : "";
  TupleCellSpec *spec = new TupleCellSpec(new FieldExpr(table, field_meta));
  const char *field_name = field.aggr_param().empty() ? field_meta->name() : field.aggr_param().c_str();
  if (is_multi_mode) {
    const char *table_name = table->name();
    char *alias;
    if (is_aggr) {
      alias = (char *)malloc(strlen(func_name) + 2 + strlen(table_name) + strlen(field_name) + 1);
      sprintf(alias, "%s(%s.%s)", func_name, table_name, field_name);
    } else {
      alias = (char *)malloc(strlen(table_name) + strlen(field_name) + 1);
      sprintf(alias, "%s.%s", table_name, field_name);
    }
    spec->set_alias(alias);
  } else {
    char *alias;
    if (is_aggr) {
      alias = (char *)malloc(strlen(func_name) + 2 + strlen(field_name) + 1);
      sprintf(alias, "%s(%s)", func_name, field_name);
    } else {
      alias = const_cast<char *>(field_name);
    }
    spec->set_alias(alias);
  }
  tuple_.add_cell_spec(spec);
}

RC ProjectOperator::tuple_cell_spec_at(int index, const TupleCellSpec *&spec) const
{
  return tuple_.cell_spec_at(index, spec);
}
