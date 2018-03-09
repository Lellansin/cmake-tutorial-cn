## 添加系统自检

接下来让我们考虑在我们的项目中添加一些代码，这些代码取决于目标平台可能没有的功能。

在这个例子中，我们将添加一些代码，取决于目标平台是否具有 log 和 exp 函数。当然，几乎每个平台都有这些功能，但本教程假定它们不太常用。如果平台有某函数，那么我们将在项目中使用它来。我们首先使用根目录 CMakeLists.txt 文件中的 CheckFunctionExists.cmake 这个宏来测试这些函数的可用性，如下所示：

```cmake
# 这个系统是否提供日志和 exp 函数？
include (CheckFunctionExists)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)
```

接下来，我们修改 TutorialConfig.h.in 的定义将这些检查的判断关联到项目中：

```cmake
// 该平台是否提供exp和日志功能？
#cmakedefine HAVE_LOG
#cmakedefine HAVE_EXP
```

在使用 TutorialConfig.h 的 configure\_file 命令之前完成 log 和 exp 的测试是很重要的。configure\_file 命令立即使用CMake中的当前设置来配置文件。最后，在 mysqrt 函数中，我们可以使用以下代码提供基于log和exp的备用实现：

```c
// 如果我们同时有内置的 log 和 exp，则使用它们
#if defined (HAVE_LOG) && defined (HAVE_EXP)
  result = exp(log(x)*0.5);
#else // 此外使用一个替代的办法
  . . .
```



