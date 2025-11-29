cmake_minimum_required(VERSION 3.15)
project(boost_timers VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------------------
# Dependencies: Boost + Protobuf
# -------------------------------------------------------------
find_package(Boost 1.89.0 REQUIRED COMPONENTS system chrono thread date_time)

# -------------------------------------------------------------
# Executable
# -------------------------------------------------------------
add_executable(boost_timers
    main.cpp
    src/timer.cpp
    src/timer_manager.cpp
)

# -------------------------------------------------------------
# Include directories
# -------------------------------------------------------------
target_include_directories(boost_timers PRIVATE
    inc
)

# -------------------------------------------------------------
# Linking
# -------------------------------------------------------------
target_link_libraries(boost_timers
    PRIVATE
        Boost::system
        Boost::thread
        Boost::chrono
        Boost::date_time
)

# -------------------------------------------------------------
# Testing + Packaging (optional)
# -------------------------------------------------------------
include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)