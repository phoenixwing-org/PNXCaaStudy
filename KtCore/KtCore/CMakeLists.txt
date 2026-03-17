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

# 构建后将公开头文件导出到 ${ROOT_DIR_CORE}/include
file(GLOB KTCORE_PUBLIC_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/public/*.h")
add_custom_command(TARGET KtCore POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${ROOT_DIR_CORE}/include"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${KTCORE_PUBLIC_HEADERS} "${ROOT_DIR_CORE}/include"
)

message("- <<=========END KtCore")
