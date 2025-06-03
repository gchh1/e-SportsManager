cmake_minimum_required(VERSION 3.22)
project(dataHandlers)

# 搜索源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

# 链接库
link_libraries(models)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/heads
                    ${CMAKE_SOURCE_DIR}/src/models/heads
                    ${CMAKE_SOURCE_DIR}/src/include)


# 添加库
add_library(dataHandlers ${SRC})
