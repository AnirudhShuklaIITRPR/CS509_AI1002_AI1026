# CS509 - Assignment 1 (Buddy Task)

# Graph Algorithms using CSR

## Algorithms Implemented

- Breadth First Search (BFS)
- Depth First Search (DFS)
- Single Source Shortest Path (SSSP) using Dijkstra's Algorithm

---

## Programming Language

C

## Compiler

GCC (MSYS2 UCRT64)

---

# Student Details

### Anirudh Shukla
- Entry No.: 2026AIM1002
- Branch: Artificial Intelligence (AI)

### Kalki Dang
- Entry No.: 2026AIM1026
- Branch: Artificial Intelligence (AI)

---

# Objective

The objective of this assignment is to implement graph algorithms using the **Compressed Sparse Row (CSR)** graph representation.

The graph is first read as an adjacency list, converted into CSR format, and then the following algorithms are executed:

- Breadth First Search (BFS)
- Depth First Search (DFS)
- Single Source Shortest Path (SSSP) using Dijkstra's Algorithm

Only the algorithm execution time is measured.

---

# Project Structure

```text
Assignment_1_buddy/
│
├── driver/
│   └── driver.c
│
├── include/
│   ├── graph.h
│   ├── csr.h
│   ├── bfs.h
│   ├── dfs.h
│   └── sssp.h
│
├── src/
│   ├── graph.c
│   ├── csr.c
│   ├── bfs.c
│   ├── dfs.c
│   └── sssp.c
│
├── test/
│   ├── test_case_1.txt
│   ├── test_case_2.txt
│   ├── test_case_3.txt
│   ├── test_case_4.txt
│   └── test_case_5.txt
│
├── output/
│   ├── output1.txt
│   ├── output2.txt
│   ├── output3.txt
│   ├── output4.txt
│   ├── output5.txt
│   ├── output_sssp1.txt
│   ├── output_sssp2.txt
│   ├── output_sssp3.txt
│   ├── output_sssp4.txt
│   └── output_sssp5.txt
│
├── Makefile
└── README.md
```

---

# Input Format

The input graph is stored as an adjacency list with edge weights.

```text
Number_of_Vertices Number_of_Edges

Vertex Degree
Destination Weight
Destination Weight
...
```

---

# Workflow

```text
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
Run BFS / DFS / SSSP
      │
      ▼
Stop Timer
      │
      ▼
Display Output
```

---

# CSR Representation

The graph is stored using three arrays.

## Row Pointer

Stores the starting index of every vertex.

## Column Index

Stores the destination vertex of every edge.

## Values

Stores the corresponding edge weights.

---

# Algorithms

## 1. Breadth First Search (BFS): BFS explores the graph level by level using a queue.

### Time Complexity: O(V + E)

### Space Complexity: O(V)

---

## 2. Depth First Search (DFS): DFS explores vertices recursively before backtracking.

### Time Complexity: O(V + E)

### Space Complexity: O(V)

---

## 3. Single Source Shortest Path (SSSP): The shortest paths are computed using **Dijkstra's Algorithm** on the CSR representation.

### Time Complexity: O(V² + E)

### Space Complexity: O(V)


# Performance Measurement

Execution time is measured using the C Standard Library function:

```c
clock()
```

Only the execution of the algorithms is measured.

The following operations are **excluded**:

- File Reading
- Graph Construction
- CSR Conversion
- Output Printing
- Memory Deallocation

---

# BFS and DFS Performance Results

| Test Case | Source Vertex | BFS Execution Time (s) | DFS Execution Time (s) |
|-----------|---------------|-----------------------:|-----------------------:|
| Test Case 1 | 0 | 0.003000 | 0.002000 |
| Test Case 2 | 99 | 0.001000 | 0.001000 |
| Test Case 3 | 999 | 0.002000 | 0.001000 |
| Test Case 4 | 0 | 0.001000 | 0.001000 |
| Test Case 5 | 99999 | 0.004000 | 0.002000 |

# SSSP Performance Results

| Test Case | Execution Time |
|-----------|---------------:|
| sssp_10.txt | **0.000 ms** |
| sssp_100.txt | **0.000 ms** |
| sssp_10000.txt | **292.000 ms** |
| sssp_50000.txt | **12749.000 ms** |
| sssp_100000.txt | **35673.000 ms** |

---

# Compilation

Using Makefile

```bash
make
```

Using GCC

```bash
gcc driver/driver.c src/graph.c src/csr.c src/bfs.c src/dfs.c src/sssp.c -Iinclude -o graph.exe
```

---

# Execution

Windows

```bash
graph.exe
```

Linux / MSYS2

```bash
./graph.exe
```

---

# Output

The program provides:

- BFS Traversal
- DFS Traversal
- Shortest Path Distances (SSSP)
- CSR Representation
- Execution Time

---

# File Description

## driver.c

Provides the menu interface, reads the graph, converts it into CSR, invokes BFS, DFS, and SSSP, and records execution time.

---

## graph.c

Reads the graph from the input file and constructs the adjacency list.

---

## csr.c

Converts the adjacency list into CSR representation.

---

## bfs.c

Implements Breadth First Search using CSR.

---

## dfs.c

Implements Depth First Search using CSR.

---

## sssp.c

Implements Single Source Shortest Path using Dijkstra's Algorithm on the CSR representation.

---

# Conclusion

This project demonstrates the implementation of graph algorithms using the **Compressed Sparse Row (CSR)** representation. BFS, DFS, and SSSP are implemented efficiently, with execution time measured only for the algorithm execution. The CSR format provides a compact and efficient representation for sparse graphs.

---

# References

1. CS509 Assignment 1 Specification
2. GCC Documentation
3. Dijkstra, E. W. "A Note on Two Problems in Connexion with Graphs" (1959)

---

# Authors

### Anirudh Shukla
- BFS
- DFS
- CSR Representation

### Kalki Dang
- CSR Representation
- Single Source Shortest Path (SSSP)
- Performance Evaluation
