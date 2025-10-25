cmake_minimum_required(VERSION 3.10)
project(demo)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

find_package(fmt REQUIRED)

# 收集 src 下的实现文件
file(GLOB_RECURSE LIB_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# main.cpp 在 src/main.cpp，且其它实现文件也是在 src 下。
# 我们把实现文件分为 library_sources（排除 main.cpp）
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*/main.cpp$")

add_library(core_lib STATIC ${LIB_SOURCES})
target_include_directories(core_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(lyn src/main.cpp)
target_link_libraries(lyn PRIVATE core_lib fmt::fmt)

set(CMAKE_BUILD_TYPE Debug)
