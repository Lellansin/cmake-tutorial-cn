## 安装和测试

接下来，我们将为我们的项目添加安装规则和测试支持。安装规则非常简单。对于 MathFunctions 库，我们通过将以下两行添加到 MathFunctions 的 CMakeLists.txt 文件来设置库和要安装的头文件：

```cmake
install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)
```

对于应用程序，将以下行添加到根目录 CMakeLists.txt 文件中以安装可执行文件和配置的头文件：

```cmake
＃添加安装目标
install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"        
         DESTINATION include)
```

此时，你应该能够构建一下本教程的内容，在根目录输入 `make install`（或从 IDE 构建 INSTALL 目标）。这个命令会安装相应的头文件、库和可执行文件。CMake 的变量 CMAKE\_INSTALL\_PREFIX 用于确定文件安装位置的根目录。

增加测试也是一个相当直接的过程。在根目录 CMakeLists.txt 文件的结尾，我们可以添加许多基本测试来验证应用程序是否正常工作。

```cmake
include(CTest)

# 判断应用是否运行
add_test (TutorialRuns Tutorial 25)

# 判断 25 的 sqrt
add_test (TutorialComp25 Tutorial 25)
set_tests_properties (TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

# 判断它能否处理负数
add_test (TutorialNegative Tutorial -25)
set_tests_properties (TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is 0")

# 判断它能否处理小数
add_test (TutorialSmall Tutorial 0.0001)
set_tests_properties (TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")

# 判断的 usage 消息是否正常
add_test (TutorialUsage Tutorial)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

```

建立完成后，可通过 “ctest” 命令来运行测试。第一个测试只是单纯的验证应用程序是否能运行，比如不会出现 segment fault 或以其他方式崩溃，并且返回值为零。这是 CTest 测试的基本形式。接下来的几个测试都使用 `PASS_REGULAR_EXPRESSION` 属性来验证程序的输出是否包含某些字符串。在这种情况下，验证所计算的平方根是否正确，以及提供的 usage 参数时打印消息是否正常等。如果你想添加大量的测试来测试不同的输入值，你可以考虑创建一个像下面这样的宏：

```cmake
# 定义一个宏来简化添加测试的过程
macro (do_test arg result)
  add_test (TutorialComp${arg} Tutorial ${arg})
  set_tests_properties (TutorialComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)
 
# 批量的根据 arg 和 result 来做测试
do_test (25 "25 is 5")
do_test (-25 "-25 is 0")
```

对于 do\_test 的每次调用，都会根据传递的参数将名称，输入和结果添加到项目中。

  


