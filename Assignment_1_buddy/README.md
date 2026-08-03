# CS509 - Assignment 1 (Buddy Task)
## Graph Traversal using CSR

### Algorithms Implemented

- Breadth First Search (BFS)
- Depth First Search (DFS)

### Programming Language

C

### Compiler

GCC (MSYS2 UCRT64)

---

### Student Details:

- Name: Anirudh Shukla
- Entry no.: 2026aim1002
- branch: Artificial Intelligence(AI)

- Name: Kalki Dang
- Entry no.: 2026aim1026
- branch: Artificial Intelligence(AI)

# Objective

The objective of this assignment is to implement graph traversal algorithms using the **Compressed Sparse Row (CSR)** graph representation.

The graph is first read as an adjacency list, converted into CSR format, and then BFS or DFS is executed.

Only the algorithm execution time is measured.

---

# Project Structure

```
Buddy_Task/
│
├── driver/
│   └── driver.c
│
├── include/
│   ├── graph.h
│   ├── csr.h
│   ├── bfs.h
│   └── dfs.h
│
├── src/
│   ├── graph.c
│   ├── csr.c
│   ├── bfs.c
│   └── dfs.c
│
├── tests/
│   ├── test_case_1.txt
│   ├── test_case_2.txt
│   └── test_case_3.txt
|   └── test_case_3.txt
|   └── test_case_3.txt
│
├── output/
│   └── output1.txt
│   └── output2.txt
│   └── output3.txt
|   └── output4.txt
|   └── output5.txt
│   
├── Makefile
│
└── README.md
```

---

# Input Format

The input graph is stored as an edge list.

```
Number_of_Vertices Number_of_Edges

Source Destination

Source Destination
...
```

Example

```
5 6

0 1
0 2
1 3
2 3
2 4
3 4
```

---

# Workflow

```
Input File
      │
      ▼
Read Adjacency List
      │
      ▼
Convert to CSR
      │
      ▼
Start Timer
      │
      ▼
Run BFS / DFS
      │
      ▼
Stop Timer
      │
      ▼
Display Traversal
```

---

# CSR Representation

The graph is stored using three arrays.

## Row Pointer

Stores the starting index of every vertex.

## Column Index

Stores destination vertices.

## Weight

Stores edge weights.

For BFS and DFS, every edge is assigned a weight of **1**.

---

# Algorithms

## Breadth First Search (BFS)

BFS explores the graph level by level using a queue.

### Time Complexity

```
O(V + E)
```

### Space Complexity

```
O(V)
```

---

## Depth First Search (DFS)

DFS explores as deep as possible before backtracking using recursion.

### Time Complexity

```
O(V + E)
```

### Space Complexity

```
O(V)
```

---

# Performance Measurement

Execution time is measured using the C Standard Library function:

```
clock()
```

Only the following is timed:

- BFS execution
- DFS execution

The following operations are **not included** in the execution time:

- File Reading
- Input Parsing
- Adjacency List Creation
- CSR Conversion
- Output Printing
- Memory Deallocation

---

# Compilation

Using Makefile

```
make
```

Or using GCC

```
gcc driver/driver.c src/graph.c src/csr.c src/bfs.c src/dfs.c -Iinclude -o graph.exe
```

---

# Execution

Windows

```
graph.exe
```

Linux / MSYS2

```
./graph.exe
```

---

# Output

The program provides:

- BFS Traversal
- DFS Traversal
- Execution Time
- CSR Representation (optional)

---

# Files Description

## driver.c

Reads the input graph, converts it to CSR, provides a menu for BFS and DFS, and measures execution time.

---

## graph.c

Creates the adjacency list, reads the graph from the input file, and frees allocated memory.

---

## csr.c

Converts the adjacency list into CSR format and prints the CSR representation.

---

## bfs.c

Implements Breadth First Search using CSR.

---

## dfs.c

Implements Depth First Search using CSR.

---

# Conclusion

This project implements BFS and DFS using the CSR graph representation. The graph is first read as an adjacency list and converted to CSR before execution. Execution time is measured only for the traversal algorithms, ensuring compliance with the assignment requirements.

---

# References

1. CS509 Assignment 1 Specification
2. GCC Documentation

# Authors

1. BFS & DFS - Anirudh Shukla 
2. SSSP - Kalki Dang