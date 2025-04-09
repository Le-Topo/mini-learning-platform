# Makefile for mini-learning-platform

# === CONFIG ===
SRC_DIR = ./
BUILD_DIR = build
BIN_DIR = bin
INC_DIR = ./

# Final executable name
TARGET = $(BIN_DIR)/mini-learning-platform

# Lib & headers PDCurses
PDC_LIB_DIR = lib/pdcurses
PDC_INCLUDE_DIR = lib/pdcurses/include

# Find all source files in the source directory
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')

# Generate object files from source files and place them in the build directory
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Include all subdirs in root directory
INC_PATHS = $(shell find $(INC_DIR) -type d)
INCLUDES = $(addprefix -I, $(INC_PATHS))

# Compiler and flags
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
INC_PATHS = $(shell find $(INC_DIR) -type d)
INCLUDES = $(addprefix -I, $(INC_PATHS)) -I$(PDC_INCLUDE_DIR)
CFLAGS = -Wall -Wextra $(INCLUDES)
LDFLAGS = -L$(PDC_LIB_DIR) -l:pdcurses.a -lncurses -lSDL2 -lmysqlclient

#CC = gcc
#CFLAGS = -Wall -Wextra $(INCLUDES)
#LDFLAGS = -lncurses -lmysqlclient `mysql_config --cflags --libs`

# Main compilation command
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)
	@echo "✅ Compilation finished successfully. Executable: $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Check if pdcurses.a exists ===
check-pdc:
	@if [ ! -f $(PDC_LIB_DIR)/pdcurses.a ]; then \
		echo "🧩 PDCurses not found. Automatic installation..."; \
		$(MAKE) pdcurses-install; \
	fi

# === System dependencies + PDCurses ===
dependencies:
	@echo "📦 Installing system dependencies..."
	sudo apt update
	sudo apt install -y libmysqlclient-dev libncurses-dev libsdl2-dev git make gcc
	@echo "✅ System dependencies installed."
	$(MAKE) pdcurses-install

# === Install only PDCurses SDL2 ===
PDC_TMP_DIR := tmp/pdcurses
PDC_REPO := https://github.com/wmcbrine/PDCurses.git

pdcurses-install:
	@echo "🔧 Downloading and compiling PDCurses (SDL2)..."
	@if [ -d $(PDC_TMP_DIR) ]; then rm -rf $(PDC_TMP_DIR); fi
	git clone --depth=1 $(PDC_REPO) $(PDC_TMP_DIR)
	cd $(PDC_TMP_DIR)/sdl2 && make
	mkdir -p $(PDC_LIB_DIR) $(PDC_INCLUDE_DIR)
	cp $(PDC_TMP_DIR)/sdl2/pdcurses.a $(PDC_LIB_DIR)/
	cp $(PDC_TMP_DIR)/curses.h $(PDC_INCLUDE_DIR)/
	cp $(PDC_TMP_DIR)/panel.h $(PDC_INCLUDE_DIR)/
	#cp $(PDC_TMP_DIR)/pdcurses.h $(PDC_INCLUDE_DIR)/
	rm -rf $(PDC_TMP_DIR)
	@echo "✅ PDCurses (SDL2) has been installed successfully."

# === Clean up build artifacts ===
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Define phony targets
.PHONY: all clean dependencies pdcurses-install check-pdc
