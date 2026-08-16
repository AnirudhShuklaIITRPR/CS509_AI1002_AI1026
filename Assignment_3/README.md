# CS509 - Assignment 3

* **Language:** C
* **Compiler:** GCC
* **Environment:** MSYS2 UCRT64
* **Editor:** Visual Studio Code

---

## Assignment 3 - Buddy Task

This project contains the implementations of two algorithms:

1. **Gradient Descent**
2. **Max Flow / Min Cut**

The two parts are divided between the two team members.

---

# 1. Gradient Descent

The Gradient Descent algorithm is implemented by **Anirudh Shukla**.

The implementation performs gradient descent on a polynomial function.

For a polynomial

\[
f(x) = a_0 + a_1x + a_2x^2 + \cdots + a_nx^n
\]

the derivative is calculated as

\[
f'(x) = a_1 + 2a_2x + 3a_3x^2 + \cdots + na_nx^{n-1}
\]

The gradient descent update is:

\[
x_{new} = x - \alpha f'(x)
\]

where:

- `x` = current value of x
- `α` = learning rate
- `f'(x)` = gradient of the polynomial

The algorithm stops when the gradient or the change in `x` becomes smaller than the specified tolerance, or when the maximum number of iterations is reached.

---

## Gradient Descent Input Format

Each test case contains:

```text
DEGREE <degree>
COEFFICIENTS <a0> <a1> ... <an>
INITIAL_X <initial value>
LEARNING_RATE <learning rate>
TOLERANCE <tolerance>
MAX_ITERATIONS <maximum iterations>
````

### Example

```text
DEGREE 2
COEFFICIENTS 9 -6 1
INITIAL_X 0
LEARNING_RATE 0.10
TOLERANCE 0.000001
MAX_ITERATIONS 5000
```

This represents:

[
f(x)=9-6x+x^2
]

or

[
f(x)=(x-3)^2
]

Therefore, the minimum occurs at:

```text
x = 3
```
---

## Gradient Descent Test Cases

The project contains five Gradient Descent test cases.

```text
tests/
└── gradientDescent/
    ├── test_case_1.txt
    ├── test_case_2.txt
    ├── test_case_3.txt
    ├── test_case_4.txt
    └── test_case_5.txt
```

The driver provides a menu for selecting any of the five test cases.

---

# 2. Max Flow / Min Cut

The **Max Flow / Min Cut** part is implemented by **Kalki Dang**.

The implementation is integrated into the Assignment 3 menu.

The driver provides a separate option for running the Max Flow / Min Cut implementation.

---

# 3. Menu Driven Program

The main driver provides the following menu:

```text
=========================================
          CS509 ASSIGNMENT 3
=========================================
1. Gradient Descent
2. Max Flow / Min Cut
3. Exit
=========================================
Enter your choice:
```

### Option 1 - Gradient Descent

Selecting option `1` opens the Gradient Descent test-case menu:

```text
=========================================
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

### Option 2 - Max Flow / Min Cut

Selecting option `2` runs the implementation by:

**Kalki Dang**

### Option 3 - Exit

Selecting option `3` exits the program.

---

# 4. Project Structure

```text
Assignment_3/
│
├── Makefile
├── README.md
│
├── driver/
│   └── driver.c
│
├── include/
│   └── gradientDescent.h
│
├── src/
│   └── gradientDescent.c
│
├── output/
│
└── tests/
    └── gradientDescent/
        ├── test_case_1.txt
        ├── test_case_2.txt
        ├── test_case_3.txt
        ├── test_case_4.txt
        └── test_case_5.txt
```

The Max Flow / Min Cut files implemented by Kalki Dang can be added to the corresponding `include/` and `src/` directories.

---

# 5. Compilation

The project uses GCC with MSYS2 UCRT64.

From the Assignment 3 directory, run:

```bash
make
```

The executable will be created as:

```text
Assignment_3.exe
```

---

# 6. Running the Program

Run:

```bash
./Assignment_3.exe
```

or:

```cmd
Assignment_3.exe
```

---

# 7. Example Gradient Descent Result

For:

```text
DEGREE 2
COEFFICIENTS 9 -6 1
INITIAL_X 0
LEARNING_RATE 0.10
TOLERANCE 0.000001
MAX_ITERATIONS 5000
```

the program produces a result similar to:

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

The exact minimum is:

```text
x = 3
```

The calculated value `2.999996` is within the specified tolerance.

---

# 8. Output

Gradient Descent results are stored in the `output/` directory.

Example:

```text
output/
├── gradientDescent/test_case_1.txt
├── gradientDescent/test_case_2.txt
├── gradientDescent/test_case_3.txt
├── gradientDescent/test_case_4.txt
└── gradientDescent/test_case_5.txt
```
## Perfromance Evaluation

### Gradient Descent Results Table

| Test Case   | Polynomial Degree | Initial X |  Final X | Function Value | Iterations | Execution Time (ms) | Status |
| ----------- | ----------------: | --------: | -------: | -------------: | ---------: | ------------------: | :----: |
| Test Case 1 |                 2 |  0.000000 | 2.999996 |       0.000000 |         61 |            0.000000 |  PASS  |
| Test Case 2 |                 4 |  2.000000 | 0.000011 |       0.000000 |        134 |            0.000000 |  PASS  |
| Test Case 3 |                 6 |  2.000000 | 0.000023 |       0.000000 |        254 |            0.000000 |  PASS  |
| Test Case 4 |                 8 |  2.000000 | 0.000000 |       0.000000 |        721 |            0.000000 |  PASS  |
| Test Case 5 |                10 |  2.000000 | 0.000000 |       0.000000 |       1838 |            0.000000 |  PASS  |

---

# 13. Team Contribution

### Anirudh Shukla

Implemented:

* Gradient Descent
* Polynomial evaluation
* Polynomial derivative
* Gradient descent iteration logic
* Gradient Descent test-case handling
* Gradient Descent execution-time measurement
* Gradient Descent output generation
* Menu integration

### Kalki Dang

Implemented:

* Max Flow / Min Cut
* Max Flow / Min Cut test cases
* Max Flow / Min Cut integration

