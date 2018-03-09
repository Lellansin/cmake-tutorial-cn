// 一个构建 sqrt 表的简单程序 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[])
{
  int i;
  double result;

  // 确保有足够参数
  if (argc < 2)
  {
    return 1;
  }

  // 打开输出的文件（文件名为参数2）
  FILE *fout = fopen(argv[1],"w");
  if (!fout)
  {
    return 1;
  }

  // 创建一个通过平方根的表源文件
  fprintf(fout, "double sqrtTable[] = {\n");
  for (i = 0; i < 10; ++i)
  {
    result = sqrt(static_cast<double>(i)); // 预先算一遍 i 的平方根
    fprintf(fout,"%g,\n",result); // 结果写入文件
  }

  // 以 0 结尾
  fprintf(fout,"0};\n");
  // 关闭文件
  fclose(fout);
  return 0;
}

