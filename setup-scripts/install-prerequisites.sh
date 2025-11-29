#!/bin/bash
set -e

echo "=== Installing prerequisite packages ==="

sudo apt-get update
sudo apt-get install -y \
    git \
    cmake \
    build-essential \
    curl \
    zip unzip \
    tar \
    pkg-config

echo "=== Prerequisites installed successfully ==="
