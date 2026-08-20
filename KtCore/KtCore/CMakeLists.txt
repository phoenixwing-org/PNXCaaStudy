include(../common.cmake)
project("KtCore" VERSION 1.0.0)
message("## Cmake Project KtCore")

set(KTCORE_PUBLIC_INCLUDE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/public")
set(KTCORE_PACKAGE_INCLUDE_DIR "${KTCORE_PUBLIC_INCLUDE_ROOT}/KtCore")

# 将项目中的源文件添加到列表中
file(GLOB_RECURSE SRC_DIR_LIST "*.cpp")

# define micro KtCore_EXPORTS

add_definitions(-DKtCore_EXPORTS)
add_library(KtCore SHARED ${SRC_DIR_LIST}) #改为动态库

target_include_directories(KtCore
  PUBLIC
    $<BUILD_INTERFACE:${KTCORE_PUBLIC_INCLUDE_ROOT}>
    $<INSTALL_INTERFACE:include>
)
target_link_directories(KtCore PUBLIC ${MY_LINK_PATH})

# 构建后按 CMake Package 结构导出：include/KtCore/*.h。
# 仅清理 KtCore 同名的旧平铺副本，不影响其他 package。
file(GLOB_RECURSE KTCORE_PUBLIC_HEADERS CONFIGURE_DEPENDS
  "${KTCORE_PACKAGE_INCLUDE_DIR}/*.h"
  "${KTCORE_PACKAGE_INCLUDE_DIR}/*.hpp"
)
set(KTCORE_LEGACY_FLAT_HEADERS)
foreach(KTCORE_PUBLIC_HEADER IN LISTS KTCORE_PUBLIC_HEADERS)
  get_filename_component(KTCORE_PUBLIC_HEADER_NAME "${KTCORE_PUBLIC_HEADER}" NAME)
  list(APPEND KTCORE_LEGACY_FLAT_HEADERS "${ROOT_DIR_CORE}/include/${KTCORE_PUBLIC_HEADER_NAME}")
endforeach()
add_custom_command(TARGET KtCore POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${ROOT_DIR_CORE}/include/KtCore"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${KTCORE_PACKAGE_INCLUDE_DIR}" "${ROOT_DIR_CORE}/include/KtCore"
  COMMAND ${CMAKE_COMMAND} -E rm -f ${KTCORE_LEGACY_FLAT_HEADERS}
)

message("- <<=========END KtCore")
