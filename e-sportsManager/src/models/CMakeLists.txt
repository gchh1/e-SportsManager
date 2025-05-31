cmake_minimum_required(VERSION 3.22)
project(models)

# 搜索源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)


# 添加库
add_library(models ${SRC})
