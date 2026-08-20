include(../common.cmake)

message("## Cmake Project test_KtCore")

# windows下不需要：link_directories(${MY_LINK_PATH})，见`README.md：# cmake连接lib的总结`
# linux下还是要加${MY_LINK_PATH}

link_directories(${MY_LINK_PATH})

include_directories(${ROOT_DIR_3rdParty}/Catch2_Single)

# ===test====
add_executable(test_KtString "test_KtString.cpp")
target_link_libraries(test_KtString PUBLIC KtCore)
add_test(NAME "test_KtString" COMMAND test_KtString)

message("- <<=========END test_KtCore")
