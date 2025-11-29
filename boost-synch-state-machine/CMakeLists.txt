cmake_minimum_required(VERSION 3.15)
project(boost_state_machine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------------------
# Dependencies: Boost + Protobuf
# -------------------------------------------------------------
find_package(Boost 1.89.0 REQUIRED COMPONENTS system msm)

# -------------------------------------------------------------
# Executable
# -------------------------------------------------------------
add_executable(boost_state_machine
    main.cpp
    src/controller.cpp
)

# -------------------------------------------------------------
# Include directories
# -------------------------------------------------------------
target_include_directories(boost_state_machine PRIVATE
    inc
)

# -------------------------------------------------------------
# Linking
# -------------------------------------------------------------
target_link_libraries(boost_state_machine
    PRIVATE
        Boost::system
        Boost::msm
)

# -------------------------------------------------------------
# Testing + Packaging (optional)
# -------------------------------------------------------------
include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)