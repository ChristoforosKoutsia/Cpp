cmake_minimum_required(VERSION 3.10)
project(interval_map)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the main source file
add_executable(interval_map interval_map.cpp)

# Enable warnings
if (CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(interval_map PRIVATE -Wall -Wextra -pedantic)
endif()

# Add tests (if any)
enable_testing()

# Add a test executable (optional, if you have test files)
# add_executable(test_interval_map test_interval_map.cpp)
# add_test(NAME test_interval_map COMMAND test_interval_map)
