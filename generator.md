## 添加生成文件和生成器

在本节中，我们将展示如何将生成的源文件添加到应用程序的构建过程中。在这个例子中，我们将创建一个预先计算的平方根表作为构建过程的一部分，然后将该表编译到我们的应用程序中。为了实现这一点，我们首先需要一个能够生成表格的程序。在 MathFunctions 子目录中，一个名为 MakeTable.cxx 的新文件可以做到这一点。

```cpp
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

  // 打开输出的文件 (文件名为参数2)
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
```

注意，该表是通过有效的 C++ 代码生成的，并且输出文件名字是通过参数传入的。下一步是向 MathFunctions 的CMakeLists.txt 文件添加适当的命令以构建 MakeTable 可执行文件，然后将其作为构建过程的一部分运行。如下所示，需要一些命令来完成此操作。

```cmake
# 首先我们添加生成表的可执行文件
add_executable(MakeTable MakeTable.cxx)

# 添加命令以生成源代码
add_custom_command (
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
  )


# 将 binary tree directory 添加到搜索路径中
include_directories ($ {CMAKE_CURRENT_BINARY_DIR})

# 添加 main 库
add_library(MathFunctions mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h  )
```

首先添加 MakeTable 的可执行文件，因为将添加任何其他可执行文件。然后我们添加一个自定义命令，通过运行MakeTable 生成 `Table.h` 。

接下来我们必须让 CMake 知道 mysqrt.cxx 依赖于生成的文件 `Table.h`。办法是将生成的 `Table.h` 添加到库 MathFunctions 的源列表中。我们还必须将当前的二叉树目录添加到 include 目录列表中，以便可以通过 mysqrt.cxx 找到并包含 `Table.h`。

当这个项目被构建时，它将首先构建 MakeTable 可执行文件。然后它将运行 MakeTable 来生成 `Table.h`。最后，它将编译包含 `Table.h`的库。

添加了所有功能的根目录 CMakeLists.txt 文件如下所示：

```cmake
cmake_minimum_required (VERSION 2.6)
project (Tutorial)
include(CTest)

# 版本号
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# 判断系统是否供了 log 和 exp 函数?
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)

check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

# 是否要试用自实现的 math 函数
option(USE_MYMATH 
  "Use tutorial provided math implementation" ON)

# 配置一个头文件来传递一些 CMake 设置到源代码
configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )

# 将二叉树添加到包含文件的搜索路径以便我们找到 TutorialConfig.h
include_directories ("${PROJECT_BINARY_DIR}")

# add the MathFunctions library?
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# 添加可执行文件
add_executable (Tutorial tutorial.cxx)
target_link_libraries (Tutorial  ${EXTRA_LIBS})

# 添加 install 目标
install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"        
         DESTINATION include)

# 判断 25 的 sqrt
add_test (TutorialRuns Tutorial 25)

# 判断的 usage 消息是否正常
add_test (TutorialUsage Tutorial)
set_tests_properties (TutorialUsage
  PROPERTIES 
  PASS_REGULAR_EXPRESSION "Usage:.*number"
  )


# 定义一个宏来简化添加测试的过程
macro (do_test arg result)
  add_test (TutorialComp${arg} Tutorial ${arg})
  set_tests_properties (TutorialComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endmacro (do_test)

# 批量的根据 arg 和 result 来做测试
do_test (4 "4 is 2")
do_test (9 "9 is 3")
do_test (5 "5 is 2.236")
do_test (7 "7 is 2.645")
do_test (25 "25 is 5")
do_test (-25 "-25 is 0")
do_test (0.0001 "0.0001 is 0.01")
```

TutorialConfig.h.in 如下所示：

```c
// the configured options and settings for Tutorial
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
#cmakedefine USE_MYMATH

// 该平台是否提供 exp 和 log 函数?
#cmakedefine HAVE_LOG
#cmakedefine HAVE_EXP
```

MathFunctions 的 CMakeLists.txt 文件如下所示：

```cmake
# 首先我们添加生成表的可执行文件
add_executable(MakeTable MakeTable.cxx)
# 添加命令以生成源代码
add_custom_command (
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  )
# binary tree directory 添加到 include 搜索路径中
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

# 添加 main 库
add_library(MathFunctions mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)
```



