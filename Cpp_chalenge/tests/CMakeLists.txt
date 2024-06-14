cmake_minimum_required(VERSION 3.10)
project(ServerTest)

set(CMAKE_CXX_STANDARD 17)

# Find Google Test
find_package(GTest REQUIRED)

# Include directories
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../)

# Add source files
set(SOURCE_FILES
../solution.cpp 
../physical_device.h 
../solution.hpp
../custom_exceptions.hpp
../utils.cpp
../utils.hpp
)

# Add test source files
set(TEST_FILES
    server_test.cpp
)

# Add test executable
add_executable(ServerTest ${SOURCE_FILES} ${TEST_FILES})

# Link test executable against Google Test libraries
target_link_libraries(ServerTest ${GTEST_LIBRARIES} pthread)
