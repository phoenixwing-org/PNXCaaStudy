#used for several cmake file
cmake_minimum_required(VERSION 3.25)

# 设置C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

# main variable
if(EMSCRIPTEN)
    set(ROOT_DIR_CORE ${ROOT_DIR}/kt/wasm)
else()
    set(ROOT_DIR_CORE ${ROOT_DIR}/kt/core)
endif()

# set default for output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${ROOT_DIR_CORE}/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${ROOT_DIR_CORE}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ROOT_DIR_CORE}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ROOT_DIR_CORE}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${ROOT_DIR_CORE}/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${ROOT_DIR_CORE}/bin)

# 根据构建类型设置链接目录
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(MY_LINK_PATH ${ROOT_DIR_CORE}/debug)
else()
    set(MY_LINK_PATH ${ROOT_DIR_CORE}/bin)
    set(CMAKE_BUILD_TYPE Release)
endif()
