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
// Created by wangyunlai on 2022/9/28
//

#include <string.h>
#include "util/util.h"

std::string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
      
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return std::string(buf, len);
}

std::string date_to_string(int date)
{
  std::string y = std::to_string(date / 10000);
  std::string m = std::to_string((date % 10000) / 100);
  std::string d = std::to_string(date % 100);
  for (size_t i = 0; i < 4-y.size(); i++) {
    y = '0'+y;
  }
  for (size_t i = 0; i < 2-m.size(); i++) {
    m = '0'+m;
  }
  for (size_t i = 0; i < 2-d.size(); i++) {
    d = '0'+d;
  }
  return y + '-' + m + '-' +d;
}
