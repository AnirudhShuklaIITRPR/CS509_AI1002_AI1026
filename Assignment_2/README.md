# CS509 – Assignment 2 (Buddy Task)

## Algorithms
1. Connected Components
2. Triangle Counting
3. Betweenness Centrality

## Language
C

## Compiler
GCC (MSYS2 UCRT64)

---

## Project Structure

```text
Assignment_2/
├── driver/
│   └── driver.c
├── include/
│   ├── csr.h
│   ├── connected_components.h
│   ├── triangle_counting.h
│   └── betweenness_centrality.h
├── src/
│   ├── csr.c
│   ├── connected_components.c
│   ├── triangle_counting.c
│   └── betweenness_centrality.c
├── test/test/
│   ├── test_case_10.txt
│   ├── test_case_100.txt
│   ├── test_case_1000.txt
│   ├── test_case_5000.txt
│   └── test_case_10000.txt
├── output/
├── Makefile
└── graph2.exe
└── README.md
```
---

## Features

* Menu-driven execution
* CSR graph representation
* Execution time measurement
* Output stored in files
* Same graph input format used by all three algorithms

---

## Build

```bash
make
```

## Run

```bash
./graph2.exe
```

### Menu

```text
1. Connected Components
2. Triangle Counting
3. Betweenness Centrality
4. Exit
```
----

## Test Cases

| Test Case            | Vertices |
| -------------------- | -------- |
| test_case_10.txt     |       10 |
| test_case_100.txt    |      100 |
| test_case_1000.txt   |    1,000 |
| test_case_10000.txt  |   10,000 |
| test_case_50000.txt  |   50,000 |
| test_case_100000.txt |  100,000 |

---

## Output

Results are stored in the `output/` directory.

## Performance Evaluation
| Algorithm            | Test Case   | Vertices | Execution Time (seconds) | Status |
| -------------------- | ----------- | -------: | -----------------------: | ------ |
| Connected Components | `cc_10`     |       10 |           0.000000000000 | Pass   |
| Connected Components | `cc_100`    |      100 |           0.000000000000 | Pass   |
| Connected Components | `cc_10000`  |   10,000 |           0.000000000000 | Pass   |
| Connected Components | `cc_50000`  |   50,000 |           0.001000000000 | Pass   |
| Connected Components | `cc_100000` |  100,000 |           0.002000000000 | Pass   |
| Test Case   | Vertices |       Time (s) |
| ----------- | -------: | -------------: |
| `cc_10`     |       10 | 0.000000000000 |
| `cc_100`    |      100 | 0.000000000000 |
| `cc_10000`  |   10,000 | 0.000000000000 |
| `cc_50000`  |   50,000 | 0.001000000000 |
| `cc_100000` |  100,000 | 0.002000000000 |

---

## Contribution

1. Triangle Counting & Betweeness Centrality - Anirudh Shukla 
2. Connected Components - Kalki Dang
