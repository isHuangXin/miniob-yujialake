//
// Created by RuanBin on 2022/10/20
//
#include <string.h>
int chars_to_ints(char* source)
{
  int len = strlen(source);
  int ed = len;
  int flag = source[0] == '-';
  int st = flag;
  // 暂时先用个int吧，如果溢出以后再改
  int res = 0;
  //判断正负
  while (st < ed && source[st] >= '0' && source[st] <= '9') {
    res = (10 * res) + (source[st] - '0');
    st++;
  }
  return res * (1 - 2 * flag);
}

float chars_to_floats(char* source)
{
  int len = strlen(source);
  int flag = source[0] == '-';
  double ft = 0, lst = 0;
  int st = flag;
  while (st < len && source[st] >= '0' && source[st] <= '9') {
    ft = ft * 10 + (source[st] - '0');
    st++;
  }
  if (st < len && source[st] == '.')
  {
    st++;
    float t = 0.1;
    while (st < len && source[st] >= '0' && source[st] <= '9') {
      lst += t * (source[st] - '0');
      t *= 0.1;
      st++;
    }
  }
  return (ft + lst) * (1 - 2 * flag);
}