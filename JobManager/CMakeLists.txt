cmake_minimum_required(VERSION 3.10)

# Set the project name
project(JobManagerProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(JobManager main.cpp JobManager.cpp Logger.hpp)

# Include directories
target_include_directories(JobManager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link libraries (if any)
# target_link_libraries(JobManager <library_name>)