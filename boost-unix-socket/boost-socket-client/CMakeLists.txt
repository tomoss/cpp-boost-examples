cmake_minimum_required(VERSION 3.15)
project(boost_socket_client VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------------------
# Dependencies: Boost + Protobuf
# -------------------------------------------------------------
find_package(Boost 1.89.0 REQUIRED COMPONENTS system thread serialization)
find_package(Protobuf REQUIRED)

# -------------------------------------------------------------
# Proto generation
# -------------------------------------------------------------
file(GLOB PROTO_FILES proto/*.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# -------------------------------------------------------------
# Executable
# -------------------------------------------------------------
add_executable(boost_socket_client
    main.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

# -------------------------------------------------------------
# Include directories
# -------------------------------------------------------------
target_include_directories(boost_socket_client PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${Protobuf_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# -------------------------------------------------------------
# Link with Boost + Protobuf + pthread
# -------------------------------------------------------------
target_link_libraries(boost_socket_client
    PRIVATE
        ${Boost_LIBRARIES}
        ${Protobuf_LIBRARIES}
)

# -------------------------------------------------------------
# Testing + Packaging (optional)
# -------------------------------------------------------------
include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
