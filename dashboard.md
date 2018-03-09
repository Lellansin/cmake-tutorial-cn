## 添加仪表板支持

添加对将测试结果提交到仪表板的支持非常简单。在本教程的前几个步骤中，我们已经为我们的项目定义了许多测试。我们只需运行这些测试并将它们提交到仪表板。为了引入对仪表板的支持，我们将 CTest 模块包含在我们的顶层 CMakeLists.txt 文件中。

```
# 启用仪表板脚本
include (CTest)
```

我们也创建一个 CTestConfig.cmake 文件，可以在其中为仪表板指定该项目的名称。

```
set (CTEST_PROJECT_NAME "Tutorial")
```

运行时，CTest 将在此文件中读取。要创建一个简单的仪表板，您可以在您的项目上运行 CMake，将目录更改为二叉树，然后运行 `ctest -D Experimental`。仪表板的结果将上传到在 Kitware 的公用仪表板（[地址](http://www.cdash.org/CDash/index.php?project=PublicDashboard)）。

## 当前代码

Github [Example 地址](https://github.com/Lellansin/cmake-tutorial-cn/tree/master/example)
