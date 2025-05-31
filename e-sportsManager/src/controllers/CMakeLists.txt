cmake_minimum_required(VERSION 3.22)
project(controllers)

# 搜索源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

# 链接库
link_libraries(models dataHandlers)


# 添加库
add_library(controllers ${SRC})

