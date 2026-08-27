include(CMakePackageConfigHelpers)

install(TARGETS KtCore
    EXPORT KtCoreTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
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
    "${CMAKE_CURRENT_LIST_DIR}/KtCoreConfig.cmake.in"
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
