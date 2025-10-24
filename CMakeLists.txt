cmake_minimum_required(VERSION 3.20)
project(RY-SlopeSearch)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加 SeqAn3 的路径
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/seqan3/cmake")

# 包含 range-v3（SeqAn3 的依赖）
include_directories(${CMAKE_SOURCE_DIR}/third_party/range-v3/include)

# 添加 SeqAn3
find_package(seqan3 3.0 REQUIRED)

# 添加 yaml-cpp 的子目录
add_subdirectory(third_party/yaml-cpp)

# 包含头文件路径
include_directories(${CMAKE_SOURCE_DIR}/include)

# 查找源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 添加可执行文件
add_executable(RY-SlopeSearch ${SOURCES})

# 链接 yaml-cpp 和 SeqAn3
target_link_libraries(RY-SlopeSearch PRIVATE yaml-cpp seqan3::seqan3)