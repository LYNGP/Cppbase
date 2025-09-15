cmake_minimum_required(VERSION 3.10)
project(demo)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 找到 pthread 库、 fmt 库
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)     

# 编译可执行文件
# add_executable(1_base src/1_base.cpp)
# add_executable(2_namespace src/2_namespace.cc)
add_executable(3_const src/3_const.cc)


# 链接 pthread
# target_link_libraries(pc Threads::Threads)

# 链接 fmt
# target_link_libraries(1_base fmt::fmt) 
# target_link_libraries(2_namespace fmt::fmt) 
target_link_libraries(3_const fmt::fmt) 

# 调试信息
set(CMAKE_BUILD_TYPE Debug)