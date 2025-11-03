# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Files
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/tictactoe.o
TARGET = $(BIN_DIR)/tictactoe

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the game
run: all
	./$(TARGET)


