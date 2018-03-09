## 添加库

现在我们将为我们的项目添加一个库（library）。这个库将包含我们自己的实现的计算数字平方根的功能。然后可执行文件可以使用这个库来代替编译器提供的标准平方根函数。对于本教程，我们将把该库放入名为MathFunctions的子目录中。它将具有以下一行CMakeLists.txt文件：

```cmake
add_library（MathFunctions mysqrt.cxx）
```

源文件 mysqrt.cxx 有一个名为 mysqrt 的函数，它提供与编译器的 sqrt 函数类似的功能。为了使用新库，我们在顶层CMakeLists.txt 文件中添加一个 `add_subdirectory` 调用，以便库生成。我们还添加了另一个 include 目录，以便函数原型找到 MathFunctions/MathFunctions.h 头文件。最后一个更改是将新的库添加（link）到可执行文件。CMakeLists.txt 文件的最后几行如下所示：

```cmake
include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
add_subdirectory (MathFunctions) 

＃添加可执行文件
add_executable (Tutorial tutorial.cxx)
target_link_libraries (Tutorial MathFunctions)
```

现在让我们考虑让 MathFunctions 库变成一个可选项。实际上在本例中你可能没有任何理由这么做，但是你可能会在碰到较大的库或第三方代码库时需要。第一步是向根目录的 CMakeLists.txt 文件添加一个选项。

```cmake
# (扪心自问) 我们应该使用自实现的数学函数吗？
option (USE_MYMATH 
        "Use tutorial provided math implementation" ON) 
```

这个配置项将在 CMake GUI 中显示，默认值为 ON，用户可以根据需要在面板上进行更改。设置后选项将存在缓存中，所以用户不用每次运行 CMake 时都再选一次。接下来的变化是使 MathFunctions 库的构建和链接有条件。为此，我们将根目录的 CMakeLists.txt 的结尾做如下更改：

```
＃添加 MathFunctions 库吗？
＃
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

＃添加可执行文件
add_executable (Tutorial tutorial.cxx)
target_link_libraries (Tutorial  ${EXTRA_LIBS})
```

现在这里使用了 USE\_MYMATH 的设置来确定是否要应编译和使用 MathFunctions。请注意使用变量（本例为`EXTRA_LIBS`）来收集任何可选的库，以便以后将其链接到可执行文件中。这是一种常用的方法，用于保持包含许多可选组件的较大项目的清洁。源代码的相应更改则非常直截了当：

```c
//一个计算数字平方根的简单程序
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif
 
int main (int argc, char *argv[])
{
  if (argc < 2)
    {
    fprintf(stdout,"%s Version %d.%d\n", argv[0],
            Tutorial_VERSION_MAJOR,
            Tutorial_VERSION_MINOR);
    fprintf(stdout,"Usage: %s number\n",argv[0]);
    return 1;
    }
 
  double inputValue = atof(argv[1]);
 
#ifdef USE_MYMATH
  double outputValue = mysqrt(inputValue);
#else
  double outputValue = sqrt(inputValue);
#endif
 
  fprintf(stdout,"The square root of %g is %g\n",
          inputValue, outputValue);
  return 0;
}
```

在源代码中我们也使用了USE\_MYMATH。这是通过 TutorialConfig.h.in 配置的，你需要添加以下行：

```cmake
#cmakedefine USE_MYMATH
```

  


