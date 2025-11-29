cmake_minimum_required(VERSION 3.15)
project(boost_socket_server VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------------------
# Dependencies: Boost + Protobuf + Abseil
# -------------------------------------------------------------
find_package(Boost 1.89.0 REQUIRED COMPONENTS system thread serialization)
find_package(Protobuf REQUIRED)
find_package(absl CONFIG REQUIRED)

# -------------------------------------------------------------
# Proto generation
# -------------------------------------------------------------
file(GLOB PROTO_FILES proto/*.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# -------------------------------------------------------------
# Executable
# -------------------------------------------------------------
add_executable(boost_socket_server
    main.cpp
    src/my_server.cpp
    src/session.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

# -------------------------------------------------------------
# Include directories
# -------------------------------------------------------------
target_include_directories(boost_socket_server PRIVATE
    inc
    ${CMAKE_CURRENT_BINARY_DIR}   # for generated *.pb.h
)

# -------------------------------------------------------------
# Linking
# -------------------------------------------------------------
target_link_libraries(boost_socket_server
    PRIVATE
        Boost::system
        Boost::thread
        Boost::serialization
        protobuf::libprotobuf         # correct vcpkg protobuf target

        # Required for protobuf >= 27.x / 28.x / 29.x
        absl::log
        absl::log_internal_check_op
        absl::log_internal_message
        absl::base
        absl::strings
)

# -------------------------------------------------------------
# Testing + Packaging (optional)
# -------------------------------------------------------------
include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
