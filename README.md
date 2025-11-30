# cpp-boost-examples

C++ examples with **Boost v1.89.0**. 

This repository is structured as a **CMake Monorepo**. It uses **vcpkg** (Manifest Mode) for dependency management and **CMake Presets** for a unified build workflow on **Linux**.

## Prerequisites

Before building, ensure you have the following installed:

* **C++ Compiler** (GCC or Clang)
* **CMake** (v3.20 or newer required for Presets)
* **Ninja** (Recommended for build speed) or Make
* **vcpkg**

### Environment Setup
You must define the `VCPKG_ROOT` environment variable pointing to your vcpkg installation.

```bash
# Example (add to ~/.bashrc to make permanent)
export VCPKG_ROOT="$HOME/vcpkg"
