#!/bin/sh

# Export public KtCore headers to the KtRoot SDK.
# Usage: ./export.sh [target-core-directory] [header-directory]

set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
SOURCE_DIR="$SCRIPT_DIR/KtCore/public/KtCore"

if [ -z "${ROOT_DIR:-}" ]; then
    printf '%s\n' "Error: ROOT_DIR must be set before running export.sh" >&2
    exit 1
fi
: "${ROOT_DIR_CORE:=$ROOT_DIR/kt/core}"
: "${ROOT_DIR_INCLUDE:=$ROOT_DIR_CORE/include}"
export ROOT_DIR ROOT_DIR_CORE ROOT_DIR_INCLUDE

if [ "$#" -gt 0 ]; then
    TARGET_DIR=$1
elif [ -n "${ROOT_DIR:-}" ]; then
    case "$(uname -s)" in
        Darwin) TARGET_DIR="$ROOT_DIR/kt/macos/core" ;;
        Linux) TARGET_DIR="$ROOT_DIR/kt/linux/core" ;;
        *) TARGET_DIR="$ROOT_DIR/kt/core" ;;
    esac
else
    TARGET_DIR="$ROOT_DIR_CORE"
fi

if [ "$#" -gt 1 ]; then
    TARGET_INCLUDE_ROOT=$2
elif [ -n "${ROOT_DIR_INCLUDE:-}" ]; then
    TARGET_INCLUDE_ROOT=$ROOT_DIR_INCLUDE
else
    TARGET_INCLUDE_ROOT="$TARGET_DIR/include"
fi

TARGET_INCLUDE_DIR="$TARGET_INCLUDE_ROOT/KtCore"

if [ ! -d "$SOURCE_DIR" ]; then
    printf '%s\n' "Error: public header directory not found: $SOURCE_DIR" >&2
    exit 1
fi

mkdir -p "$TARGET_INCLUDE_DIR"

printf '%s\n' "Exporting headers:"
printf '%s\n' "  From: $SOURCE_DIR"
printf '%s\n' "  To:   $TARGET_INCLUDE_DIR"

cp -R "$SOURCE_DIR"/. "$TARGET_INCLUDE_DIR"/

printf '%s\n' "Header export completed successfully."
