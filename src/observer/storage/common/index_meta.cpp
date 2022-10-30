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
// Created by Meiyi & Wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

// const static Json::StaticString FIELD_NAME("name");
// const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString INDEX_NAME("index_name");
const static Json::StaticString FIELDS_NAME("fields_name"); 
const static Json::StaticString FIELD_NAME("field_name");

// RC IndexMeta::init(const char *name, const FieldMeta &field)
RC IndexMeta::init(const char *name, std::vector<const FieldMeta *> fields)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  field_num = fields.size();
  for (int i = 0; i < field_num; i++) {
    fields_[i] = fields[i]->name();
  }
  // field_ = field.name();
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[INDEX_NAME] = name_;
  Json::Value fields_val;
  for (const std::string &field : fields_) {
    Json::Value field_val;
    field_val[FIELD_NAME] = field;
    fields_val.append(std::move(field_val));
  }
  json_value[FIELDS_NAME] = std::move(fields_val);
  // json_value[FIELD_FIELD_NAME] = field_;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[INDEX_NAME];
  const Json::Value &fields_values = json_value[FIELDS_NAME];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!fields_values.isArray()) {
    // LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
    //     name_value.asCString(),
    //     field_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  // const FieldMeta *field = table.field(field_value.asCString());
  // if (nullptr == field) {
  //   LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
  //   return RC::SCHEMA_FIELD_MISSING;
  // }

  int field_num = fields_values.size();
  std::vector<const FieldMeta *> fields(field_num);
  for (int i = 0; i < field_num; i++) {
    const Json::Value &field_name_value = fields_values[i];
    if (!field_name_value[FIELD_NAME].isString()) {
      return RC::GENERIC_ERROR;
    }
    const FieldMeta *field_meta = table.field(field_name_value[FIELD_NAME].asCString());
    if (field_meta == nullptr) {
      return RC::GENERIC_ERROR;
    }
    fields[i] = field_meta;
  }


  return index.init(name_value.asCString(), fields);
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

const char *IndexMeta::field() const
{
  return fields_[0].c_str();
}

const char *IndexMeta::field(int i) const
{
  return fields_[i].c_str();
}

const int IndexMeta::fields_num() const
{
  return field_num;
}
void IndexMeta::desc(std::ostream &os) const
{
  // os << "index name=" << name_ << ", field=" << field_;
  os << "index name=" << name_ << ", field=" << fields_[0];
  for (int i = 1; i < field_num; i++) {
    os << ", " + fields_[i];
  }
}