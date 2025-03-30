# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Bit_Manipulation)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source files for the tested functions
set(SOURCE_FILES
    exercise_1_insertion.cpp
    exercise_2_flip_to_win.cpp
    exercise_all_over.cpp
)

# Add the test file
set(TEST_FILES
test_exercise_1_insertion.cpp
test_exercise_2_flip_to_win.cpp
test_exercise_all_over.cpp
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