//
// Created by RuanBin on 2022/10/20
//
#include <string.h>
#include <cstdlib>
#include <math.h>
int chars_to_ints(const char* source)
{
  // int len = strlen(source);
  // int res = 0;
  // char *temp_chars = new char[len+1];
  // int i = 0, j = 0;
  // int dot_been = 0;
  // while (i < len && j < len) {
  //   if (source[i] >= '0' && source[i] <= '9') {
  //     temp_chars[j] = source[i];
  //     j++;
  //   } else if (source[i] == '.' && dot_been == 0) {
  //     temp_chars[j] = source[i];
  //     j++;
  //   } else {
  //     temp_chars[j] = '\0';
  //     break;
  //   }
    // return (atof(source)) * 10 + 5) / 10;
    return round(atof(source));
  // }
  // int ed = len;
  // int flag = source[0] == '-';
  // int st = flag;
  // // 暂时先用个int吧，如果溢出以后再改
  // int res = 0;
  // //判断正负
  // while (st < ed && source[st] >= '0' && source[st] <= '9') {
  //   res = (10 * res) + (source[st] - '0');
  //   st++;
  // }
  // return res * (1 - 2 * flag);
}

float chars_to_floats(const char* source)
{
  // int len = strlen(source);
  // int flag = source[0] == '-';
  // double ft = 0, lst = 0;
  // int st = flag;
  // while (st < len && source[st] >= '0' && source[st] <= '9') {
  //   ft = ft * 10 + (source[st] - '0');
  //   st++;
  // }
  // if (st < len && source[st] == '.')
  // {
  //   st++;
  //   float t = 0.1;
  //   while (st < len && source[st] >= '0' && source[st] <= '9') {
  //     lst += t * (source[st] - '0');
  //     t *= 0.1;
  //     st++;
  //   }
  // }
  // return (ft + lst) * (1 - 2 * flag);
  return atof(source);
}
