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
// Created by Tanziyi on 2022/10/22.
//

#include "sql/operator/join_operator.h"
#include "sql/expr/tuple.h"
#include "storage/common/table.h"
#include "rc.h"

RC JoinOperator::open()
{
  if (left_ == nullptr || right_ == nullptr) {
    LOG_WARN("join operator must has 2 children");
    return RC::INTERNAL;
  }

  RC rc = RC::SUCCESS;
  if ((rc = left_->open()) != RC::SUCCESS) {
    return rc;
  }
  if ((rc = left_->next()) != RC::SUCCESS) {
    return rc;
  }
  return right_->open();
}

RC JoinOperator::next()
{
  RC rc = RC::SUCCESS;
  // 右表遍历结束，重新遍历
  if ((rc = right_->next()) != RC::SUCCESS && (right_->open() == RC::SUCCESS) && (right_->next() == RC::SUCCESS)) {
    return left_->next();
  }

  return rc;
}

RC JoinOperator::close()
{
  if (left_ == nullptr || right_ == nullptr) {
    LOG_WARN("join operator must has 2 children");
    return RC::INTERNAL;
  }

  RC rc = RC::SUCCESS;
  if ((rc = left_->close()) != RC::SUCCESS) {
    return rc;
  }

  return right_->close();
}

Tuple *JoinOperator::current_tuple()
{
  return new JoinTuple(left_->current_tuple(), right_->current_tuple());
}
