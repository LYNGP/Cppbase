cmake_minimum_required(VERSION 3.10)
project(demo)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

find_package(fmt REQUIRED)     

# 编译可执行文件
add_executable(lyn src/main.cpp)

# 链接 fmt
target_link_libraries(lyn fmt::fmt) 

# 调试信息
set(CMAKE_BUILD_TYPE Debug)