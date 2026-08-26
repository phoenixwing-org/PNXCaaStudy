project("KtCore" VERSION 1.0.0)

# 源文件
file(GLOB_RECURSE KTCORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# 是否编译为动态库
if(KTCORE_BUILD_SHARED)
    add_library(KtCore SHARED ${KTCORE_SOURCES})
    target_compile_definitions(KtCore PRIVATE KtCore_EXPORTS)
else()
    add_library(KtCore STATIC ${KTCORE_SOURCES})
    target_compile_definitions(KtCore PUBLIC KTCORE_STATIC_DEFINE)
endif()

# 作用：设置编译选项
add_library(Kt::Core ALIAS KtCore)

# include 目录
target_include_directories(KtCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
        $<INSTALL_INTERFACE:${SDK_INCLUDE_INSTALL_DIR}>
)
# target_link_libraries(KtCore PRIVATE xxxx) # 如果需要

# 作用：设置编译选项
set_target_properties(KtCore PROPERTIES EXPORT_NAME Core)

include(CMakePackageConfigHelpers)

install(TARGETS KtCore
    EXPORT KtCoreTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib/bin
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/public/"
    DESTINATION "${SDK_INCLUDE_INSTALL_DIR}"
)

install(EXPORT KtCoreTargets
    FILE KtCoreTargets.cmake
    NAMESPACE Kt::
    DESTINATION lib/cmake/KtCore
)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/../cmake/KtCoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KtCoreConfig.cmake"
    INSTALL_DESTINATION lib/cmake/KtCore
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/KtCoreConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KtCoreConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KtCoreConfigVersion.cmake"
    DESTINATION lib/cmake/KtCore
)
