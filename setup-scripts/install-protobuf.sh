#!/bin/bash
set -e

if [ -z "$VCPKG_ROOT" ]; then
    echo "ERROR: VCPKG_ROOT is not set."
    exit 1
fi

echo "=== Installing protobuf + abseil via vcpkg ==="

# Install protobuf AND abseil (required for linking protobuf 28+)
"$VCPKG_ROOT/vcpkg" install protobuf abseil --triplet x64-linux

echo "=== Done ==="
echo "protobuf + abseil installed successfully."
