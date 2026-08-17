CXX = g++
CC = gcc

CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Iinclude
CFLAGS = -O2 -Wall -Wextra -Iinclude

TARGET = Assignment_3.exe

CPP_SRC = driver/main.cpp src/maxflow.cpp
C_SRC = src/gradientDescent.c

CPP_OBJ = $(CPP_SRC:.cpp=.o)
C_OBJ = $(C_SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(CPP_OBJ) $(C_OBJ)
	$(CXX) $(CPP_OBJ) $(C_OBJ) -o $(TARGET)

driver/main.o: driver/main.cpp
	$(CXX) $(CXXFLAGS) -c driver/main.cpp -o driver/main.o

src/maxflow.o: src/maxflow.cpp
	$(CXX) $(CXXFLAGS) -c src/maxflow.cpp -o src/maxflow.o

src/gradientDescent.o: src/gradientDescent.c
	$(CC) $(CFLAGS) -c src/gradientDescent.c -o src/gradientDescent.o

clean:
	del /Q driver\main.o src\maxflow.o src\gradientDescent.o Assignment_3.exe 2>NUL