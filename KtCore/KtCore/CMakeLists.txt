project("KtCore" VERSION 1.0.0)

file(GLOB_RECURSE KTCORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(KTCORE_BUILD_SHARED)
    add_library(KtCore SHARED ${KTCORE_SOURCES})
    target_compile_definitions(KtCore PRIVATE KtCore_EXPORTS)
else()
    add_library(KtCore STATIC ${KTCORE_SOURCES})
    target_compile_definitions(KtCore PUBLIC KTCORE_STATIC_DEFINE)
endif()

add_library(Kt::Core ALIAS KtCore)

target_include_directories(KtCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
        $<INSTALL_INTERFACE:${SDK_INCLUDE_INSTALL_DIR}>
)

set_target_properties(KtCore PROPERTIES EXPORT_NAME Core)
sdk_configure_core_target(KtCore)

option(KTCORE_ENABLE_INSTALL "Enable KtCore installation rules" ON)
if(KTCORE_ENABLE_INSTALL)
    include("${CMAKE_CURRENT_LIST_DIR}/../cmake/install.cmake")
endif()
