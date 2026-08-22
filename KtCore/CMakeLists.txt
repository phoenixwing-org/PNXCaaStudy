cmake_minimum_required(VERSION 3.25)

project(KtCore
    VERSION 1.0.0
    LANGUAGES CXX
)

option(KTCORE_BUILD_SHARED "Build KtCore as a shared library" ON)

add_subdirectory(KtCore)

enable_testing()
add_subdirectory(test_KtCore)
