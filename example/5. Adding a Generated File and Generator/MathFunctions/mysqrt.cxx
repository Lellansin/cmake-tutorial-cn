#include <stdio.h>
#include <math.h>

#include "Table.h"

// Emm, 假设我们自己实现一个 sqrt
double mysqrt(double x)
{
  // printf("This is mysqrt~\n");
  if (x < 0) return 0;
  // 如果 x 小于 10 且是整数
  if (x <= 10 && ceilf(x) == x) {
    // printf("This is mysqrt table x is %f, cache is %f ~\n", x, sqrtTable[(int)x]);
    return sqrtTable[(int)x];
  }
  return sqrt(x);
}

