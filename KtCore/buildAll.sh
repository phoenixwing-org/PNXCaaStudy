#!/bin/sh

set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
WORKSPACE_NAME=$(basename "$SCRIPT_DIR")
PARENT_DIR=$(dirname "$SCRIPT_DIR")
BUILD_ROOT="$PARENT_DIR/../build/$WORKSPACE_NAME"

if [ -z "${ROOT_DIR:-}" ]; then
    printf '%s\n' "Error: ROOT_DIR must be set before running buildAll.sh" >&2
    exit 1
fi
: "${ROOT_DIR_CORE:=$ROOT_DIR/kt/core}"
: "${ROOT_DIR_INCLUDE:=$ROOT_DIR_CORE/include}"
export ROOT_DIR ROOT_DIR_CORE ROOT_DIR_INCLUDE

"$SCRIPT_DIR/export.sh"

for BUILD_TYPE in Debug Release; do
    BUILD_DIR="${BUILD_ROOT}${BUILD_TYPE}"

    printf '%s\n' "===== CMake configure $BUILD_TYPE ====="
    cmake \
        "-DCMAKE_BUILD_TYPE=$BUILD_TYPE" \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE \
        --no-warn-unused-cli \
        -S "$SCRIPT_DIR" \
        -B "$BUILD_DIR"

    printf '%s\n' "===== CMake build $BUILD_TYPE ====="
    cmake --build "$BUILD_DIR" --config "$BUILD_TYPE"
done

printf '%s\n' "===== CMake install Release ====="
cmake --install "${BUILD_ROOT}Release" --config Release

printf '%s\n' "Header export, Debug build and Release build completed."
