
# 内部不要使用 find package Kt::Core, 防止头文件干扰开发
sdk_find_catch2_single()

# test_KtString
sdk_add_catch2_test(test_KtString SOURCES test_KtString.cpp LIBRARIES KtCore)
