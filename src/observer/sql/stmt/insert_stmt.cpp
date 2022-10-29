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

InsertStmt::InsertStmt(Table *table, const Value *values, int value_amount)
  : table_ (table), values_(values), value_amount_(value_amount)
{}

RC InsertStmt::create(Db *db, const Inserts &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name;
  if (nullptr == db || nullptr == table_name || inserts.value_num <= 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d", 
             db, table_name, inserts.value_num);
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
  if (field_num != value_num) {
    LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
    return RC::SCHEMA_FIELD_MISSING;
  }

  // check fields type
  const int sys_field_num = table_meta.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
    const AttrType field_type = field_meta->type();
    const AttrType value_type = values[i].type;

    if (values[i].type == DATES && *(int*)values[i].data == -1) {
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    if (field_type != value_type) { // TODO try to convert the value type to field type
      // LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d", 
      //          table_name, field_meta->name(), field_type, value_type);
      // return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      if (field_type == INTS && value_type == FLOATS) {
        *(int*)(values[i].data) = (*(float*)(values[i].data)*10 + 5) / 10;
      } else if (field_type == FLOATS && value_type == INTS) {
        *(float*)(values[i].data) = *(int*)values[i].data;
      } else if (field_type == CHARS && value_type == INTS) {
        /*截断，超过9999的数字直接进行截断，对于负数的话，要保留前面的负号*/
        int int_value = *((int*)(values[i].data));
        // values[i].data = malloc(8);
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
          for (;st < 4 && top_value; st++){
            temp_chars[st] = '0' + (int_value / top_value);
            int_value = int_value - (int_value / top_value) * top_value;
            top_value /= 10;
          }
          size_t copy_len = int_len;
          if (int_len > 4) {
            copy_len = 4;
          }
          memcpy(values[i].data, temp_chars, copy_len);
        } else {
          temp_chars[0] = '0';
          memcpy(values[i].data, temp_chars, 1);
        }
      } else if (field_type == INTS && value_type == CHARS) {
        int res = chars_to_ints((char*)(values[i].data));
        *(int*)(values[i].data) = res;
      } else if (field_type == CHARS && value_type == FLOATS) {
        double float_value = *(float*)(values[i].data);
        char *temp_chars = new char[4];
        if (float_value > -(1e-3) && float_value < 1e-3) {
          temp_chars[0] = '0';
          memcpy(values[i].data, temp_chars, 1);
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
              for (;st < 4 && top_value; st++){
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
              for(; st < 4 && decimal_value >= 0.001; st++) {
		            double xxx = decimal_value * 10;
		            int t = (10*xxx+5)/10;
                temp_chars[st] = '0' + t;
                decimal_value = (decimal_value * 10) - t;
              }
              if (st < 4){
                temp_chars[st] = '\0';
                st++;
              }
            } else {
              temp_chars[st] = '\0';
              st++;
            }
            memcpy(values[i].data, temp_chars, st);
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
            for (;st < 4 && top_value; st++){
              temp_chars[st] = '0' + (int_value / top_value);
              int_value = int_value - (int_value / top_value) * top_value;
              top_value /= 10;
            }
            size_t copy_len = int_len;
            if (int_len > 4) {
              copy_len = 4;
            }
            memcpy(values[i].data, temp_chars, copy_len);
          }
        }
      } else if (field_type == FLOATS && value_type == CHARS) {
        float res = chars_to_floats((char*)(values[i].data));
        *(float*)(values[i].data) = res;
      }
    }
  }

  // everything alright
  stmt = new InsertStmt(table, values, value_num);
  return RC::SUCCESS;
}
