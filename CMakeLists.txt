cmake_minimum_required(VERSION 3.16)
project(b64cpp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Create the library
add_library(b64cpp src/b64cpp.cpp)

# Set include directories for the library
target_include_directories(b64cpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Create test executable
add_executable(test_b64cpp tests/test_b64cpp.cpp)
target_link_libraries(test_b64cpp b64cpp)

# Enable testing
enable_testing()
add_test(NAME b64cpp_tests COMMAND test_b64cpp)

# Installation
install(TARGETS b64cpp
    EXPORT b64cppTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install headers
install(DIRECTORY include/b64cpp
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)

# Export targets
install(EXPORT b64cppTargets
    FILE b64cppTargets.cmake
    NAMESPACE b64cpp::
    DESTINATION lib/cmake/b64cpp
)
