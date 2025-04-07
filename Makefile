# Makefile for mini-learning-platform
SRC_DIR = ./
BUILD_DIR = build
BIN_DIR = bin
INC_DIR = ./

# Final executable name
TARGET = $(BIN_DIR)/mini-learning-platform

# Find all source files in the source directory
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')

# Generate object files from source files and place them in the build directory
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Include all subdirs in root directory
INC_PATHS = $(shell find $(INC_DIR) -type d)
INCLUDES = $(addprefix -I, $(INC_PATHS))

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra $(INCLUDES)
LDFLAGS = -lmysqlclient `mysql_config --cflags --libs`

# Main rule
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Compile every source file into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Define phony targets
.PHONY: all clean
