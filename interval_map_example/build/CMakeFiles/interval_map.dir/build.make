# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/Documents/ckoutsianoudis/cpp_example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Documents/ckoutsianoudis/cpp_example/build

# Include any dependencies generated for this target.
include CMakeFiles/interval_map.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/interval_map.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/interval_map.dir/flags.make

CMakeFiles/interval_map.dir/interval_map.cpp.o: CMakeFiles/interval_map.dir/flags.make
CMakeFiles/interval_map.dir/interval_map.cpp.o: ../interval_map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Documents/ckoutsianoudis/cpp_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/interval_map.dir/interval_map.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interval_map.dir/interval_map.cpp.o -c /home/user/Documents/ckoutsianoudis/cpp_example/interval_map.cpp

CMakeFiles/interval_map.dir/interval_map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interval_map.dir/interval_map.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Documents/ckoutsianoudis/cpp_example/interval_map.cpp > CMakeFiles/interval_map.dir/interval_map.cpp.i

CMakeFiles/interval_map.dir/interval_map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interval_map.dir/interval_map.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Documents/ckoutsianoudis/cpp_example/interval_map.cpp -o CMakeFiles/interval_map.dir/interval_map.cpp.s

# Object files for target interval_map
interval_map_OBJECTS = \
"CMakeFiles/interval_map.dir/interval_map.cpp.o"

# External object files for target interval_map
interval_map_EXTERNAL_OBJECTS =

interval_map: CMakeFiles/interval_map.dir/interval_map.cpp.o
interval_map: CMakeFiles/interval_map.dir/build.make
interval_map: CMakeFiles/interval_map.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/Documents/ckoutsianoudis/cpp_example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable interval_map"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interval_map.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/interval_map.dir/build: interval_map

.PHONY : CMakeFiles/interval_map.dir/build

CMakeFiles/interval_map.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/interval_map.dir/cmake_clean.cmake
.PHONY : CMakeFiles/interval_map.dir/clean

CMakeFiles/interval_map.dir/depend:
	cd /home/user/Documents/ckoutsianoudis/cpp_example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Documents/ckoutsianoudis/cpp_example /home/user/Documents/ckoutsianoudis/cpp_example /home/user/Documents/ckoutsianoudis/cpp_example/build /home/user/Documents/ckoutsianoudis/cpp_example/build /home/user/Documents/ckoutsianoudis/cpp_example/build/CMakeFiles/interval_map.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/interval_map.dir/depend

