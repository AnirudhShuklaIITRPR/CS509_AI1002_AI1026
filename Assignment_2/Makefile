CC = gcc

CFLAGS = -Iinclude

TARGET = assignment2.exe

SRC = driver/driver.c \ src/csr.c \ src/connected_components.c \ src/triangle_counting.c \ src/betweenness_centrality.c

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	del $(TARGET)
