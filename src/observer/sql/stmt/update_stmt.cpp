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
// Created by Wangyunlai on 2022/5/22.
//

#include "common/log/log.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

UpdateStmt::UpdateStmt(
    Table *table, std::vector<Value> values, std::vector<const char *> attrs, FilterStmt *filter_stmt)
    : table_(table), values_(values), attrs_(attrs), filter_stmt_(filter_stmt)
{}

RC UpdateStmt::create(Db *db, const Updates &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name;
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  std::vector<const char *> attrs;
  std::vector<Value> values;
  for (size_t i = 0; i < update.attribute_num; i++) {
    const FieldMeta *field_meta = table->table_meta().field(update.attributes[i]);
    if (nullptr == field_meta) {
      LOG_WARN("no such field. db=%s, table_name=%s, attribute_name=%s", db->name(), table_name, update.attributes[i]);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    const Value &value = update.values[i];

    // 非空字段不允许为NULL、
    if (value.type == NULLS && !field_meta->nullable()) {
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    // 不支持隐式转换
    if (value.type != NULLS && value.type != field_meta->type()) {
      if (value.type == CHARS && field_meta->type() == TEXTS) {
      } else {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }

    values.push_back(value);
    attrs.push_back(field_meta->name());
  }

  std::unordered_map<std::string, Table *> table_map{{table_name, table}};
  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, update.conditions, update.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  stmt = new UpdateStmt(table, values, attrs, filter_stmt);
  return rc;
}
