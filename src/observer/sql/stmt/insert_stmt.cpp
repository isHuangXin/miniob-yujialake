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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "util/typecast.h"
#include <vector>

InsertStmt::InsertStmt(Table *table, const Value *values, int value_amount)
    : table_(table), values_(values), value_amount_(value_amount)
{}

RC InsertStmt::create(Db *db, const Inserts &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name;
  if (nullptr == db || nullptr == table_name || inserts.row_num == 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d", db, table_name, inserts.row_num);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  const Value *values = inserts.values;
  const int value_num = inserts.value_num;
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.sys_field_num();
  // 每一行插入的值的数量校验
  for (size_t i = 0; i < inserts.row_num; i++) {
    const auto &row = inserts.rows[i];
    if (field_num != row.value_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", row.value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  std::vector<Row> rows(&inserts.rows[0], &inserts.rows[inserts.row_num]);
  // check fields type
  const int sys_field_num = table_meta.sys_field_num();
  // 插入的每一行数据都做数据匹配
  for (size_t i = 0; i < rows.size(); i++) {
    const Row &row = rows[i];
    for (size_t j = 0; j < row.value_num; j++) {
      const FieldMeta *field_meta = table_meta.field(j + sys_field_num);
      const AttrType field_type = field_meta->type();
      const AttrType value_type = row.values[j].type;
      const Value &value = row.values[j];
      // DATE 类型的日期不符合要求
      if (value.type == DATES && *(int*)value.data == -1) {
      return RC::INVALID_ARGUMENT;
      }
      // 按照test case，第二行数据若不匹配则插入失败
      if (i > 0 && field_type != value_type) {
        return SCHEMA_FIELD_TYPE_MISMATCH;
      }
      // try to convert the value type to field type
      if (field_type != value_type) {
        if (field_type == INTS && value_type == FLOATS) {
          *(int *)(value.data) = (*(float *)(value.data) * 10 + 5) / 10;
        } else if (field_type == FLOATS && value_type == INTS) {
          *(float *)(value.data) = *(int *)value.data;
        } else if (field_type == CHARS && value_type == INTS) {
          /*截断，超过9999的数字直接进行截断，对于负数的话，要保留前面的负号*/
          int int_value = *((int *)(value.data));
          // value.data = malloc(8);
          char *temp_chars = new char[4];
          if (int_value != 0) {
            int is_negative = int_value < 0;
            int temp_int = int_value;
            int st = 0;
            if (is_negative) {
              temp_chars[0] = '-';
              temp_int *= -1;
              int_value *= -1;
              st = 1;
            }
            int int_len = 0;
            while (temp_int) {
              int_len++;
              temp_int /= 10;
            }
            int top_value = 1;
            int temp_len = int_len;
            while (--temp_len) {
              top_value *= 10;
            }
            for (; st < 4 && top_value; st++) {
              temp_chars[st] = '0' + (int_value / top_value);
              int_value = int_value - (int_value / top_value) * top_value;
              top_value /= 10;
            }
            size_t copy_len = int_len;
            if (int_len > 4) {
              copy_len = 4;
            }
            memcpy(value.data, temp_chars, copy_len);
          } else {
            temp_chars[0] = '0';
            memcpy(value.data, temp_chars, 1);
          }
        } else if (field_type == INTS && value_type == CHARS) {
          int res = chars_to_ints((char *)(value.data));
          *(int *)(value.data) = res;
        } else if (field_type == CHARS && value_type == FLOATS) {
          double float_value = *(float *)(value.data);
          char *temp_chars = new char[4];
          if (float_value > -(1e-3) && float_value < 1e-3) {
            temp_chars[0] = '0';
            memcpy(value.data, temp_chars, 1);
          } else {
            if (float_value <= 999 && float_value >= -99) {
              int is_negative = float_value < 0;
              int st = 0;
              if (is_negative) {
                temp_chars[0] = '-';
                float_value *= -1;
                st = 1;
              }
              int int_value = float_value;
              double decimal_value = float_value - int_value;
              int int_len = 0;
              int temp_int = int_value;
              if (int_value != 0) {
                while (temp_int) {
                  int_len++;
                  temp_int /= 10;
                }
                int top_value = 1;
                int temp_len = int_len;
                while (--temp_len) {
                  top_value *= 10;
                }
                for (; st < 4 && top_value; st++) {
                  temp_chars[st] = '0' + (int_value / top_value);
                  int_value = int_value - (int_value / top_value) * top_value;
                  top_value /= 10;
                }
              } else {
                temp_chars[st] = '0';
                st++;
              }

              if (st <= 2 && decimal_value > 1e-3) {
                temp_chars[st] = '.';
                st++;
                for (; st < 4 && decimal_value >= 0.001; st++) {
                  double xxx = decimal_value * 10;
                  int t = (10 * xxx + 5) / 10;
                  temp_chars[st] = '0' + t;
                  decimal_value = (decimal_value * 10) - t;
                }
                if (st < 4) {
                  temp_chars[st] = '\0';
                  st++;
                }
              } else {
                temp_chars[st] = '\0';
                st++;
              }
              memcpy(value.data, temp_chars, st);
            } else {
              int int_value = float_value;
              int is_negative = int_value < 0;
              int temp_int = int_value;
              int st = 0;
              if (is_negative) {
                temp_chars[0] = '-';
                temp_int *= -1;
                int_value *= -1;
                st = 1;
              }
              int int_len = 0;
              while (temp_int) {
                int_len++;
                temp_int /= 10;
              }
              int top_value = 1;
              int temp_len = int_len;
              while (--temp_len) {
                top_value *= 10;
              }
              for (; st < 4 && top_value; st++) {
                temp_chars[st] = '0' + (int_value / top_value);
                int_value = int_value - (int_value / top_value) * top_value;
                top_value /= 10;
              }
              size_t copy_len = int_len;
              if (int_len > 4) {
                copy_len = 4;
              }
              memcpy(value.data, temp_chars, copy_len);
            }
          }
        } else if (field_type == FLOATS && value_type == CHARS) {
          float res = chars_to_floats((char *)(value.data));
          *(float *)(value.data) = res;
        }
      }
    }
  }

  // everything alright
  InsertStmt *insert_stmt = new InsertStmt(table, values, value_num);
  insert_stmt->set_rows(rows);
  stmt = insert_stmt;
  return RC::SUCCESS;
}
