# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

# Target executable
TARGET = DeviceManagerApp

# Source files
SRCS = main.cpp solution.cpp utils.cpp

# Header files
HEADERS = physical_device.h solution.hpp custom_exceptions.hpp utils.hpp

# Build directory
BUILD_DIR = build

# Object files
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Default rule to build the target
all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)

# Rule to create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to link the target executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove the generated files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
