cmake_minimum_required(VERSION 3.15)
project(boost_socket_server VERSION 0.1.0 LANGUAGES CXX)

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
add_executable(boost_socket_server
    main.cpp
    src/my_server.cpp
    src/conn_handler.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

# -------------------------------------------------------------
# Include directories
# -------------------------------------------------------------
target_include_directories(boost_socket_server PRIVATE
    inc
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}  # for generated headers
)

# -------------------------------------------------------------
# Linking
# -------------------------------------------------------------
target_link_libraries(boost_socket_server
    PRIVATE
        Boost::system
        Boost::thread
        Boost::serialization
        protobuf::libprotobuf
        pthread
)
