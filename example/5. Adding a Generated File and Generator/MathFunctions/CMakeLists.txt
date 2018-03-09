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

install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)

