cmake_minimum_required(VERSION 3.10)

# Project name
project(DeviceManagerApp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(DeviceManagerApp 
                solution.cpp 
                physical_device.h 
                solution.hpp
                custom_exceptions.cpp)

# Find Threads package
find_package(Threads REQUIRED)

# Link pthread
target_link_libraries(DeviceManagerApp PRIVATE Threads::Threads)
