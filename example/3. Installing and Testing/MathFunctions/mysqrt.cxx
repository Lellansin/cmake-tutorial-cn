#include <stdio.h>
#include <math.h>

// Emm, 假设我们自己实现一个 sqrt
double mysqrt(double x)
{
  // printf("This is mysqrt~\n");
  if (x < 0) return 0;
  return sqrt(x);
}

