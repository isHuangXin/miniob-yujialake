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
// Created by Meiyi
//

#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name)
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
}

void relation_attr_destroy(RelAttr *relation_attr)
{
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
}

void relation_aggr_init(AggrAttr *aggr_attr, AggrType aggr_Type, int is_attr, const char *relation_name,
    const char *attribute_name, Value *value)
{
  aggr_attr->aggr_type = aggr_Type;
  aggr_attr->is_attr = is_attr;
  if (is_attr == 1) {
    if (relation_name != nullptr) {
      aggr_attr->attr.relation_name = strdup(relation_name);
    } else {
      aggr_attr->attr.relation_name = nullptr;
    }
    aggr_attr->attr.attribute_name = strdup(attribute_name);
  } else {
    if (value)
      aggr_attr->value = *value;
  }
}

void relation_aggr_destroy(AggrAttr *aggr_attr)
{
  if (aggr_attr->is_attr) {
    free(aggr_attr->attr.relation_name);
    free(aggr_attr->attr.attribute_name);
  }
  aggr_attr->attr.relation_name = nullptr;
  aggr_attr->attr.attribute_name = nullptr;
}

void value_init_integer(Value *value, int v)
{
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_float(Value *value, float v)
{
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v)
{
  value->type = CHARS;
  value->data = strdup(v);
}

bool is_leap(int y)
{
  return (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0));
}

bool check_date(int y, int m, int d)
{
  if (m < 1 || m > 12) {
    return false;
  }

  if (d < 1 || d > 31) {
    return false;
  }

  if (m == 2) {
    if (is_leap(y))
      return (d <= 29);
    else
      return (d <= 28);
  }

  if (m == 4 || m == 6 || m == 9 || m == 11) {
    return (d <= 30);
  }
  return true;
}

void value_init_date(Value *value, const char *v)
{
  value->type = DATES;
  int y, m, d;
  std::sscanf(v, "'%d-%d-%d'", &y, &m, &d);

  int dv = y * 10000 + m * 100 + d;
  value->data = std::malloc(sizeof(int));
  bool b = check_date(y, m, d);
  if (!b) {
    dv = -1;
  }
  memcpy(value->data, &dv, sizeof(int));
}

void value_init_null(Value *value)
{
  value->type = NULLS;
  value->data = nullptr;
}

void value_destroy(Value *value)
{
  value->type = UNDEFINED;
  if (value->data != nullptr) {
    free(value->data);
    value->data = nullptr;
  }
}

void condition_init(Condition *condition, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value,
    int right_is_attr, RelAttr *right_attr, Value *right_value)
{
  condition->comp = comp;
  condition->left_is_attr = left_is_attr;
  if (left_is_attr) {
    condition->left_attr = *left_attr;
  } else {
    condition->left_value = *left_value;
  }

  condition->right_is_attr = right_is_attr;
  if (right_is_attr) {
    condition->right_attr = *right_attr;
  } else {
    condition->right_value = *right_value;
  }
}

void condition_destroy(Condition *condition)
{
  if (condition->left_is_attr) {
    relation_attr_destroy(&condition->left_attr);
  } else {
    value_destroy(&condition->left_value);
  }
  if (condition->right_is_attr) {
    relation_attr_destroy(&condition->right_attr);
  } else {
    value_destroy(&condition->right_value);
  }
}

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int nullable)
{
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
  attr_info->nullable = nullable;
}

void attr_info_destroy(AttrInfo *attr_info)
{
  free(attr_info->name);
  attr_info->name = nullptr;
}

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr)
{
  selects->attributes[selects->attr_num++] = *rel_attr;
}

void selects_append_order_attr(Selects *selects, RelAttr *rel_attr, int is_desc)
{
  selects->order_attrs[selects->order_num].attr = *rel_attr;
  selects->order_attrs[selects->order_num++].is_desc = is_desc;
}

void selects_append_aggr(Selects *selects, AggrAttr *aggr_attr)
{
  selects->aggr_attributes[selects->aggr_num++] = *aggr_attr;
}

void selects_append_relation(Selects *selects, const char *relation_name)
{
  selects->relations[selects->relation_num++] = strdup(relation_name);
}

void reverse_relations(Selects *selects, const int start, const int end)
{
  for (int i = start, j = end - 1; i < j; i++, j--) {
    char *tmp = selects->relations[i];
    selects->relations[i] = selects->relations[j];
    selects->relations[j] = tmp;
  }
}

void selects_arrange_relation(Selects *selects, const int join_num)
{
  int start = selects->relation_num - join_num - 1;
  reverse_relations(selects, start, start + join_num);
  reverse_relations(selects, start, selects->relation_num);
}

void selects_append_join_relation(Selects *selects, const char *relation_name)
{
  selects->relations[selects->relation_num++] = strdup(relation_name);
  selects->join_num++;
}

void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(selects->conditions) / sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->conditions[i] = conditions[i];
  }
  selects->condition_num = condition_num;
}

void selects_append_join_conditions(Selects *selects, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(selects->join_conditions[selects->join_num - 1]) / sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->join_conditions[selects->join_num - 1][i] = conditions[i];
  }
  selects->join_condition_num[selects->join_num - 1] = condition_num;
}

void selects_destroy(Selects *selects)
{
  for (size_t i = 0; i < selects->attr_num; i++) {
    relation_attr_destroy(&selects->attributes[i]);
  }
  selects->attr_num = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    free(selects->relations[i]);
    selects->relations[i] = NULL;
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->condition_num = 0;

  for (size_t i = 0; i < selects->aggr_num; i++) {
    relation_aggr_destroy(&selects->aggr_attributes[i]);
  }
  selects->aggr_num = 0;

  for (size_t i = 0; i < selects->join_num; i++) {
    for (size_t j = 0; j < selects->join_condition_num[i]; j++) {
      condition_destroy(&selects->join_conditions[i][j]);
    }
    selects->join_condition_num[i] = 0;
  }
  selects->join_num = 0;
}

void inserts_init(Inserts *inserts, const char *relation_name)
{
  inserts->relation_name = strdup(relation_name);
}

void inserts_append_values(Inserts *inserts, size_t row_num, Value values[], size_t value_num)
{
  assert(row_num < sizeof(inserts->rows) / sizeof(inserts->rows[0]));
  assert(value_num < sizeof(inserts->rows[0].values) / sizeof(inserts->rows[0].values[0]));

  for (size_t i = 0; i < value_num; i++) {
    inserts->rows[row_num].values[i] = values[i];
  }

  inserts->rows[row_num].value_num = value_num;
  inserts->row_num++;
}

void inserts_destroy(Inserts *inserts)
{
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t i = 0; i < inserts->value_num; i++) {
    value_destroy(&inserts->values[i]);
  }
  inserts->value_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name)
{
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(deletes->conditions) / sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes)
{
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

// void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
//     Condition conditions[], size_t condition_num)
// {
//   updates->relation_name = strdup(relation_name);
//   updates->attribute_name = strdup(attribute_name);
//   updates->value = *value;

//   assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
//   for (size_t i = 0; i < condition_num; i++) {
//     updates->conditions[i] = conditions[i];
//   }
//   updates->condition_num = condition_num;
// }

void updates_init(Updates *updates, const char *relation_name, Condition conditions[], size_t condition_num)
{
  updates->relation_name = strdup(relation_name);

  assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_append(Updates *updates, const char *attribute_name, Value *value)
{
  updates->attributes[updates->attribute_num] = strdup(attribute_name);
  updates->values[updates->attribute_num++] = *value;
}

void updates_destroy(Updates *updates)
{
  free(updates->relation_name);
  // free(updates->attribute_name);
  for (int i = 0; i < updates->attribute_num; i++) {
    free(updates->attributes[i]);
    updates->attributes[i] = nullptr;
    value_destroy(&updates->values[i]);
  }
  updates->relation_name = nullptr;
  // updates->attribute_name = nullptr;

  // value_destroy(&updates->value);

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info)
{
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}

void create_table_init_name(CreateTable *create_table, const char *relation_name)
{
  create_table->relation_name = strdup(relation_name);
}

void create_table_destroy(CreateTable *create_table)
{
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name)
{
  drop_table->relation_name = strdup(relation_name);
}

void drop_table_destroy(DropTable *drop_table)
{
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_init(CreateIndex *create_index, const char *index_name, const char *relation_name, int is_unique)
{
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->is_unique = is_unique;
  // create_index->attribute_num = 0;
  // create_index->attribute_name = strdup(attr_name);
}

void create_index_add(CreateIndex *create_index, const char *attr_name)
{
  if (create_index->attribute_num == MAX_NUM) {
    return;
  }
  create_index->attribute_name[create_index->attribute_num++] = strdup(attr_name);
}

void create_index_destroy(CreateIndex *create_index)
{
  free(create_index->index_name);
  free(create_index->relation_name);
  for (int i = 0; i < create_index->attribute_num; i++) {
    free(create_index->attribute_name[i]);
    create_index->attribute_name[i] = nullptr;
  }
  // free(create_index->attribute_name);

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  // create_index->attribute_name = nullptr;
}

void drop_index_init(DropIndex *drop_index, const char *index_name)
{
  drop_index->index_name = strdup(index_name);
}

void drop_index_destroy(DropIndex *drop_index)
{
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void show_index_init(ShowIndex *show_index, const char *relation_name)
{
  show_index->relation_name = strdup(relation_name);
}

void show_index_destroy(ShowIndex *show_index)
{
  free(show_index->relation_name);
  show_index->relation_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name)
{
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table)
{
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name)
{
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data)
{
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query)
{
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create()
{
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query)
{
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    } break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    } break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    } break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    } break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    } break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    } break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    } break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    } break;
    case SCF_SYNC: {

    } break;
    case SCF_SHOW_TABLES:
      break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    } break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    } break;
    case SCF_CLOG_SYNC:
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
      break;
  }
}

void query_destroy(Query *query)
{
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query *sqls);

RC parse(const char *st, Query *sqln)
{
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}
