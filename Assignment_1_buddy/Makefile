# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -Iinclude

# Source Files
SRC = src/matrix.c
DRIVER = driver/test_drivers.c

# Output Executable
TARGET = gemm.exe

# Default Target
all: $(TARGET)

# Build Executable
$(TARGET): $(SRC) $(DRIVER)
	$(CC) $(CFLAGS) $(DRIVER) $(SRC) -o $(TARGET)

# Run Program
run: $(TARGET)
	./$(TARGET)

# Remove Executable
clean:
	del /Q $(TARGET)