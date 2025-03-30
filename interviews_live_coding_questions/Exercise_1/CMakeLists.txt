# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(GoogleTestsExample)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source files for the tested functions
set(SOURCE_FILES
    exercise_1.cpp
    exercise_2.cpp
    exercise_3.cpp
    exercise_6_string_hack.cpp
    exercise_maximize_revenue.cpp
)

# Add the test file
set(TEST_FILES
    tests.cpp
)

# Include Google Test
find_package(GTest REQUIRED)

# Add the executable for the tests
add_executable(runTests ${SOURCE_FILES} ${TEST_FILES})

# Link Google Test to the test executable
target_link_libraries(runTests GTest::GTest GTest::Main)

# Enable testing
enable_testing()
add_test(NAME AllTests COMMAND runTests)
