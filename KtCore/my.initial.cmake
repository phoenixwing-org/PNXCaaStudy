# 检查 my.cmake 是否存在，如果不存在,会根据系统等情况，自动生成my.cmake

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/my.cmake") 
    include(my.cmake)
    return()
endif() 

# 组织一个字符串内容，然后写入my.cmake
set(my_cmake_content "# my.cmake\n")

# 1. find ROOT_DIR
# 临时变量line
set(value $ENV{ROOT_DIR_CORE})  # 在当前作用域设置变量 
if(NOT value)
    if(WIN32)
        string(APPEND my_cmake_content "set(ROOT_DIR \"E:/KtRoot\")\n")
        string(APPEND my_cmake_content "set(ROOT_DIR_CORE \"E:/KtRoot/kt/core\")\n")
        string(APPEND my_cmake_content "set(ROOT_DIR_3rdParty \"E:/3rdParty\")\n")
    else() 
        string(APPEND my_cmake_content "set(ROOT_DIR \"~/KtRoot\")\n")
        string(APPEND my_cmake_content "set(ROOT_DIR_CORE \"~/KtRoot/kt/core\")\n")
        string(APPEND my_cmake_content "set(ROOT_DIR_3rdParty \"~/3rdParty\")\n")
    endif()
else()
    # 已经存在环境变量，就都要存在：不存在报错：
    if(NOT EXISTS $ENV{ROOT_DIR})
        message(FATAL_ERROR "ROOT_DIR is not set")
    endif()
    if(NOT EXISTS $ENV{ROOT_DIR_3rdParty})
        message(FATAL_ERROR "ROOT_DIR_3rdParty is not set")
    endif()

    string(APPEND my_cmake_content "set(ROOT_DIR \"\$ENV{ROOT_DIR}\")\n")
    string(APPEND my_cmake_content "set(ROOT_DIR_CORE \"\$ENV{ROOT_DIR_CORE}\")\n")
    string(APPEND my_cmake_content "set(ROOT_DIR_3rdParty \"\$ENV{ROOT_DIR_3rdParty}\")\n")
endif()

# 写入文件
file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/my.cmake" "${my_cmake_content}")
message("- write my.cmake success")
 # 在当前作用域结束时清除变量
unset(value)
unset(my_cmake_content)
include(my.cmake)
