## 构建安装程序

接下来假设我们要将我们的项目发（到如 github 等地方）给其他人，以便他们可以使用它。这时，我们希望能在各种平台上提供二进制和源代码发行版。

这与我们之前在 **安装和测试**（第3步）部分安装的内容有些不同，我们在这里还安装了源代码构建的二进制文件。在这个例子中，我们将实现一个在cygwin、debian、RPMs 等平台都能支持的二进制安装和包管理功能。为了达到这一点，我们将使用 **CPack** 创建特定于平台的安装程序，如使用 CPack 封装的章节中所述。具体而言，我们需要在根目录 CMakeLists.txt 文件的底部添加几行：

```
＃构建一个CPack驱动的安装程序包
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include (CPack)
```

这就是全部内容。我们从 `include InstallRequiredSystemLibraries` 开始。该模块将引入当前平台项目所需的任何运行时库。接下来，我们将一些 CPack 变量设置为存储此项目的许可证和版本信息的位置。版本信息使用了本教程前面设置的变量。最后，我们将 **include** CPack 模块，它将使用这些变量以及您所在系统的一些其他属性来设置安装程序。

下一步是以通常的方式构建项目，然后运行 CPack。要构建二进制分发版，可以运行：

```
cpack --config CPackConfig.cmake
```

要创建一个发行版，你可以输入

```
cpack --config CPackSourceConfig.cmake
```

## 当前代码

Github [Example 地址](https://github.com/Lellansin/cmake-tutorial-cn/tree/master/example)
