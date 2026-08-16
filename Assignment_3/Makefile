CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = Assignment_3.exe

SRC = driver/driver.c \ src/gradientDescent.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm

clean:
	del /Q $(TARGET) 2>NUL