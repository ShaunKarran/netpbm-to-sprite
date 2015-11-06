# Project name.
PROJECT = netpbm_to_sprite

# Compilers
CC  = gcc
CXX = g++

# Useful directories.
BIN_DIR   = bin
BUILD_DIR = build
SRC_DIR   = src

# List of directories to be searched for include files.
INC_DIRS = -Iinclude

# Flags for both C and C++.
CPPFLAGS = $(INC_DIRS)

# Flags for C only.
CFLAGS = -std=c99

# Flags for C++ only. Use second if first doesnt work.
CXXFLAGS = -std=c++11

# Sources files separated by language.
CFILES = $(wildcard $(SRC_DIR)/*.c)
CXXFILES = $(wildcard $(SRC_DIR)/*.cpp)

# List of object files for each source file.
OBJECTS = $(foreach src, $(CFILES:.c=.o) $(CXXFILES:.cpp=.o), $(BUILD_DIR)/$(notdir $(src)))

# Target to compile binary.
TARGET = $(BIN_DIR)/$(PROJECT)

# Command for removing files.
REMOVE = rm -f

#########################################################################

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking objects. Output to $@"
	@$(CXX) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Building $< into $@"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Building $< into $@"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	@$(REMOVE) $(OBJECTS)
	@$(REMOVE) $(TARGET)

	@echo "\n Object and binary files removed.\n"
