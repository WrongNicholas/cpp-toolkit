CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = cpp-toolkit
BUILD_DIR = build

SRCS = main.cpp LinkedList/LinkedList.cpp
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/LinkedList

# Build the final executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	@echo "Build $(TARGET)"

# Compile source files to object files in the build directory
$(BUILD_DIR)/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: all
	@./$(BUILD_DIR)/$(TARGET)

# Clean up build directory
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Clean build directory"

.PHONY: all clean run
