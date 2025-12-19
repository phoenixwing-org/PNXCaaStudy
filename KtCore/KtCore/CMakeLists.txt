include(../common.cmake)
project("KtCore" VERSION 1.0.0)
message("## Cmake Project KtCore")

# 添加头文件
include_directories(
  ./public
)

# 将项目中的源文件添加到列表中
file(GLOB_RECURSE SRC_DIR_LIST "*.cpp")

# define micro KtCore_EXPORTS

add_definitions(-DKtCore_EXPORTS)
add_library(KtCore SHARED ${SRC_DIR_LIST}) #改为动态库

target_include_directories(KtCore PUBLIC ./public)
target_link_directories(KtCore PUBLIC ${MY_LINK_PATH})

message("- <<=========END KtCore")
