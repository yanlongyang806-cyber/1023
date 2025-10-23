cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(VehPatchSmart)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# 包含源代码目录
include_directories(${CMAKE_SOURCE_DIR}/src)

# 手动指定源文件
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Logger.cpp
    ${CMAKE_SOURCE_DIR}/src/SmartVehHandler.cpp
)

# 创建共享库（DLL）
add_library(veh_patch_smart SHARED ${SOURCES})

# 设置输出文件名
set_target_properties(veh_patch_smart PROPERTIES OUTPUT_NAME "veh_patch_smart")
