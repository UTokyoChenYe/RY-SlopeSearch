cmake_minimum_required(VERSION 3.20)
project(RY-SlopeSearch)

# === 设置 C++ 标准 ===
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === OpenMP 选项开关 ===
option(USE_OPENMP "Enable OpenMP parallelization" ON)

# === 添加 SeqAn3 的路径 ===
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/seqan3/cmake")

# === 包含 range-v3（SeqAn3 的依赖） ===
include_directories(${CMAKE_SOURCE_DIR}/third_party/range-v3/include)

# === 添加 SeqAn3 ===
find_package(seqan3 3.0 REQUIRED)

# === 添加 yaml-cpp ===
add_subdirectory(third_party/yaml-cpp)

# === 可选启用 OpenMP ===
if(USE_OPENMP)
    find_package(OpenMP COMPONENTS CXX)  # 只查找 C++ 部分，避免 OpenMP_C 报错
    if(OpenMP_CXX_FOUND)
        message(STATUS "Found OpenMP for C++")
        add_compile_definitions(USE_OPENMP)  # 让代码里可以用 #ifdef USE_OPENMP
    else()
        message(WARNING "OpenMP not found. Compiling without parallelization.")
        set(USE_OPENMP OFF)
    endif()
endif()

# === 包含头文件路径 ===
include_directories(${CMAKE_SOURCE_DIR}/include)

# === 查找源文件 ===
file(GLOB_RECURSE SOURCES "src/*.cpp")

# === 添加可执行文件 ===
add_executable(RY-SlopeSearch ${SOURCES})

# === 链接依赖 ===
target_link_libraries(RY-SlopeSearch PRIVATE yaml-cpp seqan3::seqan3)

# === 链接 OpenMP（如果可用） ===
if(USE_OPENMP AND OpenMP_CXX_FOUND)
    target_link_libraries(RY-SlopeSearch PRIVATE OpenMP::OpenMP_CXX)
endif()
