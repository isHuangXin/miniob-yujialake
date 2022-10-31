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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include <algorithm>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, const Selects &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // 不支持聚合函数和普通字段同时查询
  if (select_sql.attr_num > 0 && select_sql.aggr_num > 0) {
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (int i = 0; i < select_sql.relation_num; i++) {
    const char *table_name = select_sql.relations[i];
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  for (int i = select_sql.attr_num - 1; i >= 0; i--) {
    const RelAttr &relation_attr = select_sql.attributes[i];

    if (common::is_blank(relation_attr.relation_name) && 0 == strcmp(relation_attr.attribute_name, "*")) {
      for (Table *table : tables) {
        wildcard_fields(table, query_fields);
      }

    } else if (!common::is_blank(relation_attr.relation_name)) {
      const char *table_name = relation_attr.relation_name;
      const char *field_name = relation_attr.attribute_name;

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          wildcard_fields(table, query_fields);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta));
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
    }
  }

  // 收集聚合字段
  std::vector<Field> aggr_fields;
  for (size_t i = 0; i < select_sql.aggr_num; i++) {
    const AggrAttr &aggr_attr = select_sql.aggr_attributes[i];
    if (aggr_attr.aggr_type == INVALID) {
      return RC::INVALID_ARGUMENT;
    }

    Field f;
    f.set_aggr_type(aggr_attr.aggr_type);
    // COUNT(*)
    if (aggr_attr.aggr_type == COUNT && aggr_attr.is_attr && 0 == strcmp(aggr_attr.attr.attribute_name, "*")) {
      f.set_aggr_param("*");
    }
    // AGG_FUNC(id)
    else if (aggr_attr.is_attr) {
      const char *field_name = aggr_attr.attr.attribute_name;
      const char *table_name = aggr_attr.attr.relation_name;
      Table *table = nullptr;
      if (common::is_blank(table_name)) {
        table = tables[0];
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        table = iter->second;
      }

      const FieldMeta *field_meta = table->table_meta().field(field_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      f.set_table(table);
      f.set_field(field_meta);
      // COUNT(1)
    } else {
      switch (aggr_attr.value.type) {
        case INTS:
          f.set_aggr_param(std::to_string(*(int *)aggr_attr.value.data));
          break;
        case CHARS:
          f.set_aggr_param(std::string((const char *)aggr_attr.value.data));
          break;
        case FLOATS: {
          std::string s = std::to_string(*(float *)aggr_attr.value.data);
          while (s.back() == '0' || s.back() == '.') {
            s.pop_back();
          }
          f.set_aggr_param(std::move(s));
          break;
        }
        default:
          return RC::INTERNAL;
      }
    }

    aggr_fields.push_back(f);
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // 为每个inner join建立一个filter statement
  std::vector<FilterStmt *> join_filters;
  for (size_t i = 0; i < select_sql.join_num; i++) {
    FilterStmt *stmt = nullptr;
    RC rc = FilterStmt::create(
        db, default_table, &table_map, select_sql.join_conditions[i], select_sql.join_condition_num[i], stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
    join_filters.push_back(stmt);
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc =
      FilterStmt::create(db, default_table, &table_map, select_sql.conditions, select_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // 收集order by字段
  std::vector<Field> order_fields;
  for (size_t i = 0; i < select_sql.order_num; i++) {
    const OrderAttr &order_attr = select_sql.order_attrs[i];
    const auto attr = order_attr.attr;
    Field f;
    f.set_desc(order_attr.is_desc);
    if (!common::is_blank(attr.relation_name)) {
      const char *table_name = attr.relation_name;
      const char *field_name = attr.attribute_name;

      auto iter = table_map.find(table_name);
      if (iter == table_map.end()) {
        LOG_WARN("no such table in from list: %s", table_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = iter->second;
      const FieldMeta *field_meta = table->table_meta().field(field_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      f.set_table(table);
      f.set_field(field_meta);
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(attr.attribute_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      f.set_table(table);
      f.set_field(field_meta);
    }
    order_fields.push_back(f);
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->aggr_fields_.swap(aggr_fields);
  select_stmt->order_fields_.swap(order_fields);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->join_filters_.swap(join_filters);
  stmt = select_stmt;
  return RC::SUCCESS;
}
