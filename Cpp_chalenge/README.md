# Build Instructions
You can build the project using either the provided Makefile or CMake.

## Building with Make

To build the project using the Makefile, run:

```
make
```
The binary will be built in the build folder.

## Building with CMake

If CMake is installed on your system, you can build the project with the following commands:

```
mkdir build
cd build
cmake ..
make
```
## Running Tests

There are Google tests available in the tests folder. These tests are not part of the main solution but can be built and run for cross-checking the code.

First, install the Google Test framework (tested on Linux):
```
git clone https://github.com/google/googletest.git -b v1.14.0
cd googletest        # Main directory of the cloned repository.
mkdir build          # Create a directory to hold the build output.
cd build
cmake ..             # Generate native build scripts for GoogleTest.
make
sudo make install    # Install in /usr/local/ by default
```
After installing Google Test, you can build and run the test suite that has been developed.
