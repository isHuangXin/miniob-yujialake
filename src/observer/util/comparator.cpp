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
// Created by wangyunlai on 2021/6/11.
//

#include <cctype>
#include <string.h>
#include <algorithm>

const double epsilon = 1E-6;

int compare_int(void *arg1, void *arg2)
{
  int v1 = *(int *)arg1;
  int v2 = *(int *)arg2;
  return v1 - v2;
}

int compare_float(void *arg1, void *arg2)
{
  float v1 = *(float *)arg1; 
  float v2 = *(float *)arg2; 
  float cmp = v1 - v2;
  if (cmp > epsilon) {
    return 1;
  }
  if (cmp < -epsilon) {
    return -1;
  }
  return 0;
}

int compare_string(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length)
{
  const char *s1 = (const char *)arg1;
  const char *s2 = (const char *)arg2;
  int maxlen = std::min(arg1_max_length, arg2_max_length);
  int result =  strncmp(s1, s2, maxlen);
  if (0 != result) {
    return result;
  }

  if (arg1_max_length > maxlen) {
    return s1[maxlen] - 0;
  }

  if (arg2_max_length > maxlen) {
    return 0 - s2[maxlen];
  }
  return 0;
}

bool match_string(const char *lhs, const char *rhs)
{
  int m = strlen(lhs), n = strlen(rhs);
  int dp[m + 1][n + 1];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = true;
  for (int i = 1; i <= n; ++i) {
    if (rhs[i - 1] == '%')
      dp[0][i] = true;
    else
      break;
  }
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (rhs[j - 1] == '%')
        dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
      else if (rhs[j - 1] == '_' || toupper(lhs[i - 1]) == toupper(rhs[j - 1]))
        dp[i][j] = dp[i - 1][j - 1];
    }
  }
  return dp[m][n];
}

int compare_date(void *arg1, void *arg2)
{
  int v1 = *(int *)arg1;
  int v2 = *(int *)arg2;
  return v1 - v2;
}
