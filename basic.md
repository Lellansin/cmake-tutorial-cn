## 一个简单的开始

最简单的项目构建是从源代码文件构建一个可执行文件。而对于简单的项目，cmake 只需要两行的 CMakeLists.txt 文件即可。如下所示：

```cmake
cmake_minimum_required (VERSION 2.6)
project (Tutorial)
add_executable(Tutorial tutorial.cxx)
```

注意，这个示例在中的命令使用的是小写字母。实际上 CMake 中的命令是支持大写、小写和混合大小写的。下方 tutorial.cxx 的代码将计算一个数字的平方根，并且它的第一个版本非常简单：

```c
//一个计算数字平方根的简单程序
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stdout,"Usage: %s number\n",argv[0]);
    return 1;
  }
  double inputValue = atof(argv[1]);
  double outputValue = sqrt(inputValue);
  fprintf(stdout,"The square root of %g is %g\n",
          inputValue, outputValue);
  return 0;
}
```

### 添加版本号和配置的头文件

我们将添加的第一个功能是为可执行文件和项目提供一个版本号。虽然您可以在源代码中完全执行此操作，但在 CMakeLists.txt 文件中执行此操作可提供更大的灵活性。要添加版本号，我们修改 CMakeLists.txt 文件，如下所示：

```cmake
cmake_minimum_required (VERSION 2.6)
project (Tutorial)
# 版本号。
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# 配置一个头文件来传递一些CMake设置到源代码
configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )

# 将二叉树添加到包含文件的搜索路径以便我们找到 TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# 添加可执行文件
add_executable(Tutorial tutorial.cxx)
```

由于配置的文件将被写入二叉树，我们必须将该目录添加到要搜索包含文件的路径列表中。然后，我们使用以下内容在项目中创建一个 TutorialConfig.h.in 文件：

```c
// C/C++ 中通过 Cmake 的变量定义配置、版本号
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
```

当CMake配置这个头文件时，`@Tutorial_VERSION_MAJOR@` 和 `@Tutorial_VERSION_MINOR@` 的值将被 CMakeLists.txt 文件中的值替换。接下来，我们修改 tutorial.cxx 以包含配置的头文件并使用版本号。产生的源代码如下所示。

```c
//一个计算数字平方根的简单程序
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TutorialConfig.h"

int main (int argc, char *argv[])
{
  if (argc < 2)
    {
    fprintf(stdout,"%s Version %d.%d\n",
            argv[0],
            Tutorial_VERSION_MAJOR,
            Tutorial_VERSION_MINOR);
    fprintf(stdout,"Usage: %s number\n",argv[0]);
    return 1;
    }
  double inputValue = atof(argv[1]);
  double outputValue = sqrt(inputValue);
  fprintf(stdout,"The square root of %g is %g\n",
          inputValue, outputValue);
  return 0;
}
```

主要变化是包含了 TutorialConfig.h 头文件，并在版本信息中打印出版本号。

## 当前代码

Github [Example 地址](https://github.com/Lellansin/cmake-tutorial-cn/tree/master/example/1.%20A%20Basic%20Starting%20Point)
