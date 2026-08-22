include(../common.cmake)

# find 3rd party Catch2
if(NOT ROOT_DIR_3rdParty)
    message(FATAL_ERROR
        "ROOT_DIR_3rdParty is required when KTCORE_BUILD_TESTS is enabled")
endif()

find_package(Catch2_Single CONFIG REQUIRED
    PATHS "${ROOT_DIR_3rdParty}/Catch2_Single/cmake"
    NO_DEFAULT_PATH
)

# 内部不要使用 find package Kt::Core, 防止头文件干扰开发

# test_KtCore
add_executable(test_KtString test_KtString.cpp)
target_link_libraries(test_KtString PRIVATE Catch2::Single KtCore)
add_test(NAME test_KtString COMMAND test_KtString)
phoenix_configure_target(test_KtString)
