cmake_minimum_required(VERSION 3.22)
project(e-sportsManager)

# 设置c++17
set(CMAKE_CXX_STANDARD 17)

# 设置源文件目录
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 设置头文件目录
set(HEAD_DIR ${SRC_DIR}/include
             ${SRC_DIR}/dataHandlers/heads
             ${SRC_DIR}/controllers/heads
             ${SRC_DIR}/models/heads
             ${SRC_DIR}/views/heads)

# 指定头文件
include_directories(${HEAD_DIR})

# 添加子目录
add_subdirectory(${SRC_DIR}/models)
add_subdirectory(${SRC_DIR}/controllers)
add_subdirectory(${SRC_DIR}/dataHandlers)
add_subdirectory(${SRC_DIR}/views)

# 设置可执行文件目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 链接库（静态库）
link_libraries(models controllers dataHandlers views)

# 添加可执行文件
add_executable(e-sportsManager ${SRC_DIR}/test1.cpp)
