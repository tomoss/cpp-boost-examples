# cpp-boost-examples

C++ examples with **Boost v1.89.0**. 

This repository is structured as a **CMake Monorepo**. It uses **vcpkg** (Manifest Mode) for dependency management and **CMake Presets** for a unified build workflow on **Linux**.

## Prerequisites

Before building, ensure you have the following installed:

* **C++ Compiler** (GCC or Clang)
* **CMake** (v3.20 or newer required for Presets)
* **Ninja** (Recommended for build speed) or Make
* **vcpkg**

## Environment Setup
You must define the `VCPKG_ROOT` environment variable pointing to your vcpkg installation.

```bash
# Example (add to ~/.bashrc to make permanent)
export VCPKG_ROOT="$HOME/vcpkg"
```

## 🏗️ Build Instructions (Monorepo Workflow)

The commands below are executed from the root of the repository.

### 1. Configure Workspace (Run Once)

This step reads `vcpkg.json`, downloads and compiles dependencies (Boost, Protobuf, etc.), and generates the build files.

```bash
cmake --preset vcpkg-debug
```

### 2. Build Commands

#### Build All

```bash
cmake --build --preset vcpkg-debug
```

#### Build Specific Project

```bash
cmake --build --preset vcpkg-debug --target <target_name>
```

#### Build Release

```bash
cmake --build --preset vcpkg-release
```
