#!/bin/bash
set -e

GREEN="\033[0;32m"
YELLOW="\033[1;33m"
RESET="\033[0m"

if [ -z "$VCPKG_ROOT" ]; then
    echo -e "${YELLOW}ERROR: VCPKG_ROOT is not set. Run the vcpkg installation script first.${RESET}"
    exit 1
fi

VCPKG="$VCPKG_ROOT/vcpkg"

echo -e "${GREEN}=== 1. Updating vcpkg baseline ===${RESET}"
$VCPKG update

echo -e "${GREEN}=== 2. Installing Boost components ===${RESET}"

$VCPKG install boost-system
$VCPKG install boost-thread
$VCPKG install boost-serialization

echo -e "${GREEN}=== 3. Verifying installation ===${RESET}"
$VCPKG list | grep boost || true

echo -e "${GREEN}Boost (system, thread, serialization) installed successfully.${RESET}"
