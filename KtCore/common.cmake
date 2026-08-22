cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/utf-8)
endif()

if(NOT DEFINED ENV{ROOT_DIR} OR "$ENV{ROOT_DIR}" STREQUAL "")
    message(FATAL_ERROR "ROOT_DIR environment variable is required")
endif()

if(NOT DEFINED ENV{ROOT_DIR_CORE} OR "$ENV{ROOT_DIR_CORE}" STREQUAL "")
    message(FATAL_ERROR "ROOT_DIR_CORE environment variable is required")
endif()

set(KTCORE_SDK_ROOT "$ENV{ROOT_DIR}" CACHE PATH "KtRoot SDK root directory" FORCE)
set(KTCORE_ROOT_CORE "$ENV{ROOT_DIR_CORE}" CACHE PATH "KtRoot core directory" FORCE)

if(DEFINED ENV{SDK_PREFIX} AND NOT "$ENV{SDK_PREFIX}" STREQUAL "")
    set(KTCORE_SDK_PREFIX "$ENV{SDK_PREFIX}" CACHE STRING "SDK directory prefix" FORCE)
else()
    set(KTCORE_SDK_PREFIX "kt" CACHE STRING "SDK directory prefix" FORCE)
endif()

if(NOT ROOT_DIR_3rdParty AND DEFINED ENV{ROOT_DIR_3rdParty})
    set(ROOT_DIR_3rdParty "$ENV{ROOT_DIR_3rdParty}" CACHE PATH
        "Third-party dependency directory")
endif()

if(NOT KTCORE_OUTPUT_ROOT)
    if(WIN32)
        set(KTCORE_OUTPUT_ROOT "${KTCORE_SDK_ROOT}/${KTCORE_SDK_PREFIX}/core" CACHE PATH "SDK output and install directory" FORCE)
    elseif(APPLE)
        set(KTCORE_OUTPUT_ROOT "${KTCORE_SDK_ROOT}/${KTCORE_SDK_PREFIX}/macos/core" CACHE PATH "SDK output and install directory" FORCE)
    elseif(UNIX)
        set(KTCORE_OUTPUT_ROOT "${KTCORE_SDK_ROOT}/${KTCORE_SDK_PREFIX}/linux/core" CACHE PATH "SDK output and install directory" FORCE)
    else()
        set(KTCORE_OUTPUT_ROOT "${CMAKE_BINARY_DIR}/sdk/kt/core" CACHE PATH "SDK output and install directory" FORCE)
    endif()
endif()

set(KTCORE_DEBUG_OUTPUT_ROOT "${KTCORE_OUTPUT_ROOT}/debug")
set(KTCORE_RELEASE_OUTPUT_ROOT "${KTCORE_OUTPUT_ROOT}/bin")
set(KTCORE_DEBUG_ARCHIVE_ROOT "${KTCORE_OUTPUT_ROOT}/lib/debug")
set(KTCORE_RELEASE_ARCHIVE_ROOT "${KTCORE_OUTPUT_ROOT}/lib/bin")

# Use a shared header directory when explicitly configured; otherwise keep
# headers beside the selected platform SDK.
if(ROOT_DIR_INCLUDE)
    set(KTCORE_INCLUDE_ROOT "${ROOT_DIR_INCLUDE}" CACHE PATH "SDK public header directory" FORCE)
elseif(DEFINED ENV{ROOT_DIR_INCLUDE} AND NOT "$ENV{ROOT_DIR_INCLUDE}" STREQUAL "")
    set(KTCORE_INCLUDE_ROOT "$ENV{ROOT_DIR_INCLUDE}" CACHE PATH "SDK public header directory" FORCE)
else()
    set(KTCORE_INCLUDE_ROOT "${KTCORE_ROOT_CORE}/include" CACHE PATH
        "SDK public header directory" FORCE)
endif()

get_filename_component(KTCORE_INSTALL_PREFIX_ABS
    "${KTCORE_OUTPUT_ROOT}" ABSOLUTE)
get_filename_component(KTCORE_INCLUDE_ROOT_ABS
    "${KTCORE_INCLUDE_ROOT}" ABSOLUTE)
file(RELATIVE_PATH KTCORE_INCLUDE_INSTALL_DIR
    "${KTCORE_INSTALL_PREFIX_ABS}"
    "${KTCORE_INCLUDE_ROOT_ABS}"
)

set(CMAKE_INSTALL_PREFIX "${KTCORE_OUTPUT_ROOT}" CACHE PATH
    "SDK install directory" FORCE)

function(phoenix_configure_target target)

    set_target_properties(${target} PROPERTIES
        OUTPUT_NAME "${target}"
        RUNTIME_OUTPUT_DIRECTORY "${KTCORE_RELEASE_OUTPUT_ROOT}"
        LIBRARY_OUTPUT_DIRECTORY "${KTCORE_RELEASE_OUTPUT_ROOT}"
        ARCHIVE_OUTPUT_DIRECTORY "${KTCORE_RELEASE_ARCHIVE_ROOT}"
    )

    foreach(config DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
        if(config STREQUAL "DEBUG")
            set(output_dir "${KTCORE_DEBUG_OUTPUT_ROOT}")
            set(archive_dir "${KTCORE_DEBUG_ARCHIVE_ROOT}")
        else()
            set(output_dir "${KTCORE_RELEASE_OUTPUT_ROOT}")
            set(archive_dir "${KTCORE_RELEASE_ARCHIVE_ROOT}")
        endif()

        set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${config} "${output_dir}"
            LIBRARY_OUTPUT_DIRECTORY_${config} "${output_dir}"
            ARCHIVE_OUTPUT_DIRECTORY_${config} "${archive_dir}"
        )
    endforeach()
endfunction()
