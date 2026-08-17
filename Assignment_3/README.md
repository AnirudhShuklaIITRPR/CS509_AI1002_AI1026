# CS509 - Assignment 3

## Buddy Task: Gradient Descent and Max Flow / Min Cut

**Course:** CS509  
**Assignment:** Assignment 3  
**Language:** C / C++  
**Compiler:** GCC / G++  
**C++ Standard:** C++17  
**Environment:** MSYS2 UCRT64  
**Editor:** Visual Studio Code

---

# 1. Assignment Overview

This project contains the implementations of two algorithms for the CS509 Assignment 3 Buddy Task:

1. **Gradient Descent**
2. **Max Flow / Min Cut**

The two parts are divided between the two team members:

- **Anirudh Shukla** — Gradient Descent
- **Kalki Dang** — Max Flow / Min Cut

Both algorithms are integrated into a single menu-driven Assignment 3 driver.

---

# 2. Main Menu

```text
CS509 ASSIGNMENT 3
=========================================
1. Gradient Descent
2. Max Flow / Min Cut
3. Exit
=========================================
Enter your choice:
```

Option 1 opens the Gradient Descent test-case menu.  
Option 2 opens the Max Flow / Min Cut test-case menu.  
Option 3 exits the program.

---

# 3. Gradient Descent

The Gradient Descent algorithm is implemented by **Anirudh Shukla**.

For

\[
f(x)=a_0+a_1x+a_2x^2+\cdots+a_nx^n
\]

the derivative is

\[
f'(x)=a_1+2a_2x+3a_3x^2+\cdots+na_nx^{n-1}
\]

and the update is

\[
x_{new}=x-lpha f'(x)
\]

where `x` is the current value, `α` is the learning rate and `f'(x)` is the gradient.

The algorithm stops when the specified convergence condition is reached or the maximum number of iterations is reached.

## 3.1 Input Format

```text
DEGREE <degree>
COEFFICIENTS <a0> <a1> ... <an>
INITIAL_X <initial value>
LEARNING_RATE <learning rate>
TOLERANCE <tolerance>
MAX_ITERATIONS <maximum iterations>
```

Example:

```text
DEGREE 2
COEFFICIENTS 9 -6 1
INITIAL_X 0
LEARNING_RATE 0.10
TOLERANCE 0.000001
MAX_ITERATIONS 5000
```

This represents:

\[
f(x)=9-6x+x^2=(x-3)^2
\]

so the minimum occurs at `x = 3`.

## 3.2 Test Cases

```text
tests/
└── gradientDescent/
    ├── test_case_1.txt
    ├── test_case_2.txt
    ├── test_case_3.txt
    ├── test_case_4.txt
    └── test_case_5.txt
```

The driver provides:

```text
GRADIENT DESCENT TEST CASES
=========================================
1. Test Case 1
2. Test Case 2
3. Test Case 3
4. Test Case 4
5. Test Case 5
6. Back to Main Menu
=========================================
```

## 3.3 Example Result

```text
Algorithm: Gradient Descent
Test Case: 1
Input File: tests/gradientDescent/test_case_1.txt

Polynomial Degree: 2
Initial X: 0.000000
Final X: 2.999996
Function Value: 0.000000
Iterations: 61
Execution Time: 0.000000 ms
```

## 3.4 Gradient Descent Results

| Test Case | Polynomial Degree | Initial X | Final X | Function Value | Iterations | Execution Time (ms) | Status |
|---|---:|---:|---:|---:|---:|---:|:---:|
| Test Case 1 | 2 | 0.000000 | 2.999996 | 0.000000 | 61 | 0.000000 | PASS |
| Test Case 2 | 4 | 2.000000 | 0.000011 | 0.000000 | 134 | 0.000000 | PASS |
| Test Case 3 | 6 | 2.000000 | 0.000023 | 0.000000 | 254 | 0.000000 | PASS |
| Test Case 4 | 8 | 2.000000 | 0.000000 | 0.000000 | 721 | 0.000000 | PASS |
| Test Case 5 | 10 | 2.000000 | 0.000000 | 0.000000 | 1838 | 0.000000 | PASS |

Results are stored in `output/gradientDescent/`.

---

# 4. Max Flow / Min Cut

The **Max Flow / Min Cut** part is implemented by **Kalki Dang**.

The implementation uses:

- **Dinic's Maximum Flow algorithm**
- **CSR (Compressed Sparse Row) graph representation**
- Residual-network construction
- BFS level graph construction
- DFS blocking-flow computation
- Minimum-cut extraction from the final residual graph

Dinic's algorithm is used because the larger required graphs can make slower maximum-flow implementations impractical.

---

# 5. Max Flow / Min Cut Requirements Implemented

The implementation provides:

- C++17 implementation
- Directed graph input
- Adjacency-list input format
- Conversion of adjacency list to CSR before the algorithm
- Positive integer capacities
- Original outgoing edges only in input
- Internal generation of residual reverse edges
- Source and sink validation
- Source and sink must be different
- Maximum-flow value reporting
- Minimum-cut capacity reporting
- Source-side and sink-side vertex reporting
- Cut-edge reporting
- Maximum-flow/minimum-cut equality verification
- Separate algorithm execution-time measurement
- Residual-network initialization included in the timed section
- Minimum-cut extraction included in the timed section

---

# 6. CSR Graph Representation

The Max Flow / Min Cut implementation uses CSR as the required input representation.

CSR uses:

```text
row_ptr
col_idx
values
```

For Max Flow / Min Cut:

- `row_ptr` stores the starting and ending positions of each vertex's outgoing edges.
- `col_idx` stores destination vertices.
- `values` stores edge capacities.

Adjacency-list-to-CSR conversion is performed before the algorithm starts, so CSR conversion time is **not included** in the reported algorithm execution time.

The CSR helper is kept in:

```text
include/csr.hpp
```

---

# 7. Max Flow Algorithm

The implementation uses **Dinic's algorithm**.

Steps:

1. Construct the residual network from the prepared CSR graph.
2. Build a level graph using BFS.
3. Use DFS to send blocking flow through the level graph.
4. Repeat until the sink is no longer reachable from the source.
5. The resulting flow is the maximum flow.

For every original edge:

```text
u -> v with capacity c
```

the residual network internally creates:

```text
u -> v with capacity c
v -> u with capacity 0
```

Reverse residual capacity is updated when flow is sent. Input files do not contain manually created residual edges.

---

# 8. Minimum Cut

After maximum flow is computed, the final residual graph is searched from the source.

Vertices still reachable from the source form:

```text
Source side
```

All remaining vertices form:

```text
Sink side
```

For an original edge `u -> v`, if `u` is reachable and `v` is not reachable, it is a cut edge.

The capacities of all cut edges are summed to obtain the minimum-cut capacity.

The implementation verifies:

```text
Maximum Flow == Minimum Cut Capacity
```

for every test.

---

# 9. Max Flow / Min Cut Input Format

```text
V E
u0 degree neighbor1 capacity1 neighbor2 capacity2 ...
u1 degree neighbor1 capacity1 neighbor2 capacity2 ...
...
u(V-1) degree neighbor1 capacity1 neighbor2 capacity2 ...
SOURCE s
SINK t
```

Where:

- `V` = number of vertices
- `E` = number of directed capacity edges
- `u` = vertex number
- `degree` = number of outgoing edges
- Each neighbor is followed by its capacity
- Capacities are positive integers
- Only outgoing original edges are listed
- Residual edges are generated internally
- `SOURCE s` specifies the source
- `SINK t` specifies the sink

Vertices are numbered `0` to `V-1`.

---

# 10. Assignment Example Test

```text
6 10
0 2 1 16 2 13
1 2 2 10 3 12
2 2 1 4 4 14
3 2 2 9 5 20
4 2 3 7 5 4
5 0
SOURCE 0
SINK 5
```

Expected maximum flow:

```text
23
```

Expected minimum-cut capacity:

```text
23
```

One valid minimum cut:

```text
Source side: 0 1 2 4
Sink side: 3 5
```

Cut edges:

```text
1 3 12
4 3 7
4 5 4
```

Therefore:

```text
12 + 7 + 4 = 23
```

Status:

```text
PASS
```

---

# 11. Required Max Flow / Min Cut Test Cases

The required graph sizes are:

```text
10
100
1000
10000
50000
```

The optional 100,000-vertex test is not included because it is optional.

| Test File | V | E | Source | Sink |
|---|---:|---:|---:|---:|
| `maxflow_10.txt` | 10 | 17 | 0 | 9 |
| `maxflow_100.txt` | 100 | 197 | 0 | 99 |
| `maxflow_1000.txt` | 1,000 | 1,997 | 0 | 999 |
| `maxflow_10000.txt` | 10,000 | 19,997 | 0 | 9,999 |
| `maxflow_50000.txt` | 50,000 | 99,997 | 0 | 49,999 |

All test graphs contain a valid source-to-sink path.

The Max Flow / Min Cut menu is:

```text
MAX FLOW / MIN CUT TEST CASES
=========================================
1. V = 10
2. V = 100
3. V = 1000
4. V = 10000
5. V = 50000
6. Back to Main Menu
=========================================
```

---

# 12. Timing Methodology

## Gradient Descent

The Gradient Descent routine is timed separately from input reading and output generation.

## Max Flow / Min Cut

Before the Max Flow timer starts, the following are performed:

- File opening
- File reading
- Input parsing
- Input validation
- Adjacency-list construction
- Adjacency-list-to-CSR conversion

The timer starts immediately before:

```cpp
dinicMaxflowMincut(...)
```

The timed region includes:

- Residual-network initialization
- Dinic BFS
- Dinic DFS/blocking flow
- Maximum-flow computation
- Final residual-graph traversal
- Minimum-cut extraction

The timer stops immediately after the algorithm returns.

Result printing occurs after the timer stops.

---

# 13. Implementation Complexity

## Gradient Descent

For polynomial degree `n`, one iteration requires work proportional to the degree. With `I` iterations, the computational work is approximately:

```text
O(nI)
```

## Max Flow / Min Cut

The residual graph uses:

```text
Adjacency lists
BFS level graph
DFS blocking flow
```

Memory usage for the sparse representation and residual network is:

```text
O(V + E)
```

---

# 14. Input Validation

The Max Flow / Min Cut driver rejects:

- Missing input file
- Invalid `V` or `E`
- Incorrect vertex numbering
- Invalid vertex IDs
- Negative degrees
- Non-positive capacities
- Invalid source vertex
- Invalid sink vertex
- Source equal to sink
- Mismatch between header `E` and the number of adjacency entries

---

# 15. Project Structure

```text
Assignment_3/
│
├── Makefile
├── README.md
│
├── driver/
│   └── main.cpp
│
├── include/
│   ├── gradientDescent.h
│   ├── csr.hpp
│   └── maxflow.hpp
│
├── src/
│   ├── gradientDescent.c
│   └── maxflow.cpp
│
├── output/
│   ├── gradientDescent/
│   │   ├── test_case_1.txt
│   │   ├── test_case_2.txt
│   │   ├── test_case_3.txt
│   │   ├── test_case_4.txt
│   │   └── test_case_5.txt
│   │
│   └── maxflow/
│       ├── maxflow_10_run.txt
│       ├── maxflow_100_run.txt
│       ├── maxflow_1000_run.txt
│       ├── maxflow_10000_run.txt
│       ├── maxflow_50000_run.txt
│       └── maxflow_example_run.txt
│
└── tests/
    ├── gradientDescent/
    │   ├── test_case_1.txt
    │   ├── test_case_2.txt
    │   ├── test_case_3.txt
    │   ├── test_case_4.txt
    │   └── test_case_5.txt
    │
    └── maxflow/
        ├── maxflow_example.txt
        ├── maxflow_10.txt
        ├── maxflow_100.txt
        ├── maxflow_1000.txt
        ├── maxflow_10000.txt
        └── maxflow_50000.txt
```

### File Responsibilities

| File / Directory | Purpose |
|---|---|
| `driver/main.cpp` | Common menu-driven driver for both algorithms |
| `include/gradientDescent.h` | Gradient Descent declaration |
| `include/csr.hpp` | Adjacency-list to CSR conversion |
| `include/maxflow.hpp` | Max Flow / Min Cut declarations |
| `src/gradientDescent.c` | Gradient Descent implementation |
| `src/maxflow.cpp` | Dinic's algorithm and minimum-cut extraction |
| `tests/gradientDescent/` | Gradient Descent test cases |
| `tests/maxflow/` | Max Flow / Min Cut test cases |
| `output/gradientDescent/` | Gradient Descent results |
| `output/maxflow/` | Max Flow / Min Cut results |
| `Makefile` | Build instructions |
| `README.md` | Assignment documentation and results |

---

# 16. Compilation

The project contains both C and C++ source files.

- `driver/main.cpp` is compiled using C++17.
- `src/maxflow.cpp` is compiled using C++17.
- `src/gradientDescent.c` is compiled using GCC as C.

Using the Makefile:

```bash
make
```

The executable is:

```text
Assignment_3.exe
```

### Manual compilation

```bash
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude     -c driver/main.cpp -o driver/main.o
```

```bash
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude     -c src/maxflow.cpp -o src/maxflow.o
```

```bash
gcc -O2 -Wall -Wextra -Iinclude     -c src/gradientDescent.c -o src/gradientDescent.o
```

Then link:

```bash
g++ driver/main.o src/maxflow.o src/gradientDescent.o     -o Assignment_3.exe
```

Because the C Gradient Descent implementation is called from the C++ driver, `gradientDescent.h` uses C linkage when included from C++.

---

# 17. Running the Program

Run:

```bash
./Assignment_3.exe
```

or:

```cmd
Assignment_3.exe
```

The main menu appears:

```text
CS509 ASSIGNMENT 3
=========================================
1. Gradient Descent
2. Max Flow / Min Cut
3. Exit
=========================================
Enter your choice:
```

---

# 18. Experimental Results

## 18.1 Gradient Descent

| Test Case | Polynomial Degree | Initial X | Final X | Function Value | Iterations | Execution Time (ms) | Status |
|---|---:|---:|---:|---:|---:|---:|:---:|
| Test Case 1 | 2 | 0.000000 | 2.999996 | 0.000000 | 61 | 0.000000 | PASS |
| Test Case 2 | 4 | 2.000000 | 0.000011 | 0.000000 | 134 | 0.000000 | PASS |
| Test Case 3 | 6 | 2.000000 | 0.000023 | 0.000000 | 254 | 0.000000 | PASS |
| Test Case 4 | 8 | 2.000000 | 0.000000 | 0.000000 | 721 | 0.000000 | PASS |
| Test Case 5 | 10 | 2.000000 | 0.000000 | 0.000000 | 1838 | 0.000000 | PASS |

All five Gradient Descent test cases pass.

## 18.2 Max Flow / Min Cut

| File | V | E | Source | Sink | Expected Flow | Actual Flow | Cut Capacity | Time (ms) | Status |
|---|---:|---:|---:|---:|---:|---:|---:|---:|:---:|
| `maxflow_10.txt` | 10 | 17 | 0 | 9 | 43 | 43 | 43 | 0.004527 | PASS |
| `maxflow_100.txt` | 100 | 197 | 0 | 99 | 43 | 43 | 43 | 0.027010 | PASS |
| `maxflow_1000.txt` | 1,000 | 1,997 | 0 | 999 | 43 | 43 | 43 | 0.191163 | PASS |
| `maxflow_10000.txt` | 10,000 | 19,997 | 0 | 9,999 | 43 | 43 | 43 | 1.992343 | PASS |
| `maxflow_50000.txt` | 50,000 | 99,997 | 0 | 49,999 | 43 | 43 | 43 | 10.314469 | PASS |

For every required Max Flow / Min Cut test:

```text
Maximum Flow = Minimum Cut Capacity = 43
```

Therefore, all five required tests pass the correctness check.

---

# 19. Official Assignment Example Result

For the official Max Flow / Min Cut example:

```text
Maximum flow: 23
Minimum cut capacity: 23
```

Source side:

```text
0 1 2 4
```

Sink side:

```text
3 5
```

Cut edges:

```text
1 3 12
4 3 7
4 5 4
```

Cut capacity:

```text
12 + 7 + 4 = 23
```

Status:

```text
PASS
```

---

# 20. Output Files

### Gradient Descent

```text
output/gradientDescent/
├── test_case_1.txt
├── test_case_2.txt
├── test_case_3.txt
├── test_case_4.txt
└── test_case_5.txt
```

### Max Flow / Min Cut

```text
output/maxflow/
├── maxflow_10_run.txt
├── maxflow_100_run.txt
├── maxflow_1000_run.txt
├── maxflow_10000_run.txt
├── maxflow_50000_run.txt
└── maxflow_example_run.txt
```

---

# 21. Team Contribution

## Anirudh Shukla

Implemented:

- Gradient Descent
- Polynomial evaluation
- Polynomial derivative
- Gradient Descent iteration logic
- Gradient Descent test-case handling
- Gradient Descent execution-time measurement
- Gradient Descent output generation
- Gradient Descent menu integration

## Kalki Dang

Implemented:

- Max Flow / Min Cut
- Dinic's Maximum Flow algorithm
- CSR-based input handling
- Residual-network construction
- Minimum-cut extraction
- Max Flow / Min Cut test cases
- Max Flow / Min Cut execution-time measurement
- Max Flow / Min Cut output generation
- Max Flow / Min Cut menu integration

---

# 22. Submission Checklist

- [x] Common menu-driven Assignment 3 driver included
- [x] Gradient Descent implementation included
- [x] Dinic's Maximum Flow algorithm implemented
- [x] Minimum-cut extraction implemented
- [x] CSR representation used
- [x] Directed adjacency-list input supported
- [x] Residual reverse edges generated internally
- [x] Source and sink validation implemented
- [x] Required Max Flow / Min Cut graph sizes tested
- [x] Gradient Descent test cases included
- [x] Algorithm execution timing implemented
- [x] Max Flow residual initialization included in timing
- [x] Max Flow minimum-cut extraction included in timing
- [x] Maximum-flow/minimum-cut equality checked
- [x] Output files included
- [x] Experimental results documented
- [x] Team contributions documented

---

# 23. Conclusion

This Assignment 3 Buddy Task combines:

```text
Gradient Descent
        +
Max Flow / Min Cut
```

in a single menu-driven program.

Gradient Descent successfully runs all five provided test cases.

The Max Flow / Min Cut implementation uses Dinic's algorithm with CSR input representation and successfully runs all five required graph sizes, including:

```text
V = 50,000
E = 99,997
```

For every required Max Flow / Min Cut test:

```text
Maximum Flow = Minimum Cut Capacity
```

The official assignment example produces:

```text
Maximum flow = 23
Minimum cut capacity = 23
```

Therefore, both algorithmic components are integrated into the common Assignment 3 driver and the provided test cases pass their corresponding correctness checks.
