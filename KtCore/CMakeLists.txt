cmake_minimum_required(VERSION 3.25)
project(KtCore VERSION 1.0.0 LANGUAGES CXX)

include("$ENV{ROOT_DIR}/cmake/SdkCore.cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
sdk_enable_global_cxx_utf8()
sdk_set_global_config_output_dirs("${SDK_OUTPUT_ROOT}")

option(KTCORE_BUILD_SHARED "Build KtCore as a shared library" ON)
option(KTCORE_BUILD_TESTS "Build KtCore tests" ON)

add_subdirectory(KtCore)

if(KTCORE_BUILD_TESTS)
    sdk_enable_ctest()
    add_subdirectory(test_KtCore)
endif()
