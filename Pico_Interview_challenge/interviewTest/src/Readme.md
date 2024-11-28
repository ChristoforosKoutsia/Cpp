# Build Instructions for Windows

In the `bin` folder, you'll find the prebuilt binary, ready for execution, along with the required DLL for the FFT algorithm.

**Important**:
- The host machine must be **64-bit**.
- All input CSV files should be placed **just outside the `src` folder**. 
- Make sure to run `WaveGen` **just outside the `src` folder**.

If you want to build the project from scratch, you can use either **MinGW** or **MSVC**. Follow these steps:

## 1. Create a build directory and run CMake

```sh
mkdir build
cd build
cmake ..
