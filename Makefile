# Compiler
CC = gcc

# Flags
CXXFLAGS = -std=c++17 -I$(INC_DIR)
LDFLAGS = -lstdc++

# Directories
SRC_DIR = source
INC_DIR = include
BUILD_DIR = build

# Collect source files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o)))

# Executable name
EXECUTABLE = $(BUILD_DIR)/DataStructures

# Set default target
all: $(EXECUTABLE)

# Make rule for object files into executable
$(EXECUTABLE): $(OBJS) $(BUILD_DIR)/main.o
	@mkdir -p $(BUILD_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

# Make objects from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

# Special rule for main.cpp
$(BUILD_DIR)/main.o: main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run
