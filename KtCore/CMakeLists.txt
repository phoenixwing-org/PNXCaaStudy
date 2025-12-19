message("# Cmake Project KtCore")
cmake_minimum_required(VERSION 3.25)
project("KtCore" VERSION 1.0.0)

# 加载或者生成my.cmake文件
include(my.initial.cmake)
# 统一配置
include(common.cmake)

if(1)
  message("- CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
  message("- ROOT_DIR_3rdParty= `${ROOT_DIR_3rdParty}`")
  message("- ROOT_DIR         = `${ROOT_DIR}`")
  message("- ROOT_DIR_CORE    = `${ROOT_DIR_CORE}`")
endif()

# 包含的目录
include_directories(
  ${ROOT_DIR_3rdParty}
)
 
# source 
add_subdirectory(KtCore)  

enable_testing()

# test
add_subdirectory(test_KtCore)
 
message("- <=========END KtCore")
