#!/bin/bash
set -e

# Colors for readability
GREEN="\033[0;32m"
YELLOW="\033[1;33m"
RESET="\033[0m"

VCPKG_DIR="$HOME/vcpkg"
PROFILE_FILE="$HOME/.bashrc"
EXPORT_LINE='export VCPKG_ROOT="$HOME/vcpkg"'

echo -e "${GREEN}=== 1. Installing prerequisites ===${RESET}"
apt update
apt install -y git cmake build-essential curl zip unzip tar pkg-config

echo -e "${GREEN}=== 2. Cloning vcpkg if missing ===${RESET}"
if [ -d "$VCPKG_DIR" ]; then
    echo -e "${YELLOW}vcpkg directory already exists at $VCPKG_DIR, skipping clone${RESET}"
else
    git clone https://github.com/Microsoft/vcpkg.git "$VCPKG_DIR"
fi

echo -e "${GREEN}=== 3. Bootstrapping vcpkg ===${RESET}"
"$VCPKG_DIR/bootstrap-vcpkg.sh"

echo -e "${GREEN}=== 4. Adding VCPKG_ROOT to $PROFILE_FILE ===${RESET}"
if ! grep -Fxq "$EXPORT_LINE" "$PROFILE_FILE"; then
    echo "$EXPORT_LINE" >> "$PROFILE_FILE"
    echo -e "${GREEN}Added VCPKG_ROOT to $PROFILE_FILE${RESET}"
else
    echo -e "${YELLOW}VCPKG_ROOT already exists in $PROFILE_FILE${RESET}"
fi

echo -e "${GREEN}=== 5. Adding vcpkg to PATH ===${RESET}"
PATH_LINE='export PATH="$HOME/vcpkg:$PATH"'

if ! grep -Fxq "$PATH_LINE" "$PROFILE_FILE"; then
    echo "$PATH_LINE" >> "$PROFILE_FILE"
    echo -e "${GREEN}Added vcpkg to PATH in $PROFILE_FILE${RESET}"
else
    echo -e "${YELLOW}PATH already contains vcpkg${RESET}"
fi

echo -e "${GREEN}=== 6. Running vcpkg integrate install (optional but useful) ===${RESET}"
"$VCPKG_DIR/vcpkg" integrate install || true

echo -e "${GREEN}=== 7. Reloading shell ===${RESET}"
source "$PROFILE_FILE"

echo -e "${GREEN}vcpkg installation complete.${RESET}"
echo -e "Location: $VCPKG_DIR"
echo -e "To verify: run ${YELLOW}vcpkg version${RESET}"
