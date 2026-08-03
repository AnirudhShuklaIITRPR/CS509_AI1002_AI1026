# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Iinclude

# Executable Name
TARGET = graph.exe

# Source Files
SRC = driver/driver.c \
      src/graph.c \
      src/csr.c \
      src/bfs.c \
      src/dfs.c \
	  Src/sssp.c

# Default Target
all: $(TARGET)

# Build Executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Run Program
run: $(TARGET)
	./$(TARGET)

# Clean Generated Files
clean:
	del /Q $(TARGET) 2>nul || rm -f $(TARGET)

# Rebuild Project
rebuild: clean all
