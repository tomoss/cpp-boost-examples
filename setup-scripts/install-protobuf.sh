#!/bin/bash
set -e

if [ -z "$VCPKG_ROOT" ]; then
    echo "ERROR: VCPKG_ROOT is not set."
    exit 1
fi

"$VCPKG_ROOT/vcpkg" install protobuf --triplet x64-linux

echo "protobuf installed successfully."
