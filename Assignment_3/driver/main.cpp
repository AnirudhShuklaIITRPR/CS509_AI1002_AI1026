#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "csr.hpp"
#include "maxflow.hpp"
#include "gradientDescent.h"

using namespace std;

/* ============================================================
   INPUT GRAPH STRUCTURE FOR MAXFLOW
   ============================================================ */

struct InputGraph {
    CSRGraph csr;
    int source = -1;
    int sink = -1;
};

/* ============================================================
   MAXFLOW INPUT READER
   ============================================================ */

static InputGraph readMaxflowInputFile(const string& path) {
    ifstream fin(path);

    if (!fin) {
        throw runtime_error("Cannot open input file: " + path);
    }

    int V, E;

    if (!(fin >> V >> E) || V <= 0 || E < 0) {
        throw runtime_error("Invalid V/E in input file.");
    }

    vector<vector<AdjEdge>> adj(V);

    for (int expected_u = 0; expected_u < V; ++expected_u) {

        int u, degree;

        if (!(fin >> u >> degree)) {
            throw runtime_error("Missing vertex adjacency line.");
        }

        if (u != expected_u) {
            throw runtime_error(
                "Vertex numbering must be 0..V-1 in order."
            );
        }

        if (degree < 0) {
            throw runtime_error("Negative degree is invalid.");
        }

        adj[u].reserve(degree);

        for (int j = 0; j < degree; ++j) {

            int v;
            long long cap;

            if (!(fin >> v >> cap)) {
                throw runtime_error("Incomplete adjacency entry.");
            }

            if (v < 0 || v >= V) {
                throw runtime_error(
                    "Edge endpoint is out of range."
                );
            }

            if (cap <= 0) {
                throw runtime_error(
                    "Maxflow capacities must be positive integers."
                );
            }

            adj[u].push_back({v, cap});
        }
    }

    string sourceLabel, sinkLabel;
    int source, sink;

    if (!(fin >> sourceLabel >> source) ||
        sourceLabel != "SOURCE") {

        throw runtime_error("Expected: SOURCE s");
    }

    if (!(fin >> sinkLabel >> sink) ||
        sinkLabel != "SINK") {

        throw runtime_error("Expected: SINK t");
    }

    if (source < 0 || source >= V ||
        sink < 0 || sink >= V ||
        source == sink) {

        throw runtime_error("Invalid source/sink.");
    }

    /*
     * CSR conversion is preprocessing and therefore happens
     * BEFORE the algorithm timer starts.
     */
    CSRGraph csr = adjacencyListToCSR(V, adj);

    if (csr.E != E) {
        throw runtime_error(
            "Header E does not match the number of "
            "directed adjacency entries."
        );
    }

    return {std::move(csr), source, sink};
}

/* ============================================================
   PRINT MAXFLOW RESULT
   ============================================================ */

static void printMaxflowResult(
    const MaxflowResult& result,
    int source,
    int sink,
    double elapsedMs
) {

    cout << "\n";
    cout << "Algorithm: Maxflow-Mincut\n";
    cout << "Source: " << source << "\n";
    cout << "Sink: " << sink << "\n";

    cout << "Maximum flow: "
         << result.max_flow << "\n";

    cout << "Minimum cut capacity: "
         << result.min_cut_capacity << "\n";

    cout << "Source side:";

    for (int v : result.source_side) {
        cout << " " << v;
    }

    cout << "\n";

    cout << "Sink side:";

    for (int v : result.sink_side) {
        cout << " " << v;
    }

    cout << "\n";

    cout << "Cut edges:\n";

    for (const auto& e : result.cut_edges) {

        cout << e.from << " "
             << e.to << " "
             << e.capacity << "\n";
    }

    cout << fixed << setprecision(6);

    cout << "Execution time: "
         << elapsedMs
         << " ms\n";

    if (result.max_flow != result.min_cut_capacity) {

        cout << "Status: FAIL "
             << "(max-flow != min-cut)\n";

    } else {

        cout << "Status: PASS\n";
    }
}

/* ============================================================
   GRADIENT DESCENT DRIVER
   ============================================================ */

void runGradientDescent() {

    int choice;

    const char* testFiles[] = {

        "tests/gradientDescent/test_case_1.txt",
        "tests/gradientDescent/test_case_2.txt",
        "tests/gradientDescent/test_case_3.txt",
        "tests/gradientDescent/test_case_4.txt",
        "tests/gradientDescent/test_case_5.txt"
    };

    while (true) {

        cout << "\n";
        cout << "GRADIENT DESCENT TEST CASES\n";
        cout << "=========================================\n";
        cout << "1. Test Case 1\n";
        cout << "2. Test Case 2\n";
        cout << "3. Test Case 3\n";
        cout << "4. Test Case 4\n";
        cout << "5. Test Case 5\n";
        cout << "6. Back to Main Menu\n";
        cout << "=========================================\n";

        cout << "Enter test case: ";
        cin >> choice;

        if (choice == 6) {
            break;
        }

        if (choice < 1 || choice > 5) {

            cout << "\nInvalid choice. Please try again.\n";
            continue;
        }

        const char* filename = testFiles[choice - 1];

        FILE* file = fopen(filename, "r");

        if (file == nullptr) {

            cout << "\nUnable to open input file: "
                 << filename << "\n";

            continue;
        }

        int degree;
        double initialX;
        double learningRate;
        double tolerance;
        int maxIterations;

        char label[50];

        /* Read degree */

        if (fscanf(
                file,
                "%49s %d",
                label,
                &degree
            ) != 2) {

            cout << "\nError reading degree.\n";

            fclose(file);
            continue;
        }

        if (degree < 0) {

            cout << "\nInvalid degree.\n";

            fclose(file);
            continue;
        }

        double* coefficients =
            (double*)malloc(
                (degree + 1) * sizeof(double)
            );

        if (coefficients == nullptr) {

            cout << "\nMemory allocation failed.\n";

            fclose(file);
            continue;
        }

        /* Read COEFFICIENTS label */

        if (fscanf(file, "%49s", label) != 1) {

            cout << "\nError reading coefficients.\n";

            free(coefficients);
            fclose(file);

            continue;
        }

        /* Read coefficients */

        bool coefficientError = false;

        for (int i = 0; i <= degree; i++) {

            if (fscanf(
                    file,
                    "%lf",
                    &coefficients[i]
                ) != 1) {

                cout << "\nError reading coefficient "
                     << i << ".\n";

                coefficientError = true;
                break;
            }
        }

        if (coefficientError) {

            free(coefficients);
            fclose(file);

            continue;
        }

        /* INITIAL_X */

        if (fscanf(
                file,
                "%49s %lf",
                label,
                &initialX
            ) != 2) {

            cout << "\nError reading INITIAL_X.\n";

            free(coefficients);
            fclose(file);

            continue;
        }

        /* LEARNING_RATE */

        if (fscanf(
                file,
                "%49s %lf",
                label,
                &learningRate
            ) != 2) {

            cout << "\nError reading LEARNING_RATE.\n";

            free(coefficients);
            fclose(file);

            continue;
        }

        /* TOLERANCE */

        if (fscanf(
                file,
                "%49s %lf",
                label,
                &tolerance
            ) != 2) {

            cout << "\nError reading TOLERANCE.\n";

            free(coefficients);
            fclose(file);

            continue;
        }

        /* MAX_ITERATIONS */

        if (fscanf(
                file,
                "%49s %d",
                label,
                &maxIterations
            ) != 2) {

            cout << "\nError reading MAX_ITERATIONS.\n";

            free(coefficients);
            fclose(file);

            continue;
        }

        fclose(file);

        /* Basic validation */

        if (learningRate <= 0 ||
            tolerance <= 0 ||
            maxIterations <= 0) {

            cout << "\nInvalid Gradient Descent parameters.\n";

            free(coefficients);

            continue;
        }

        int iterations = 0;
        double finalX;

        /*
         * Only Gradient Descent execution is timed.
         */
        auto start = chrono::steady_clock::now();

        finalX = gradientDescent(
            degree,
            coefficients,
            initialX,
            learningRate,
            tolerance,
            maxIterations,
            &iterations
        );

        auto end = chrono::steady_clock::now();

        double executionTime =
            chrono::duration<double, milli>(
                end - start
            ).count();

        /* Calculate final f(x) */

        double functionValue = 0.0;
        double power = 1.0;

        for (int i = 0; i <= degree; i++) {

            functionValue +=
                coefficients[i] * power;

            power *= finalX;
        }

        /* Print result */

        cout << "\n";
        cout << "Algorithm: Gradient Descent\n";
        cout << "Test Case: " << choice << "\n";
        cout << "Input File: " << filename << "\n\n";

        cout << fixed << setprecision(6);

        cout << "Polynomial Degree: "
             << degree << "\n";

        cout << "Initial X: "
             << initialX << "\n";

        cout << "Final X: "
             << finalX << "\n";

        cout << "Function Value: "
             << functionValue << "\n";

        cout << "Iterations: "
             << iterations << "\n";

        cout << "Execution Time: "
             << executionTime
             << " ms\n";

        /*
         * Save result
         */

        char outputFile[200];

        sprintf(
            outputFile,
            "output/gradientDescent/test_case_%d.txt",
            choice
        );

        FILE* output = fopen(
            outputFile,
            "w"
        );

        if (output != nullptr) {

            fprintf(
                output,
                "Algorithm: Gradient Descent\n"
            );

            fprintf(
                output,
                "Test Case: %d\n",
                choice
            );

            fprintf(
                output,
                "Input File: %s\n\n",
                filename
            );

            fprintf(
                output,
                "Polynomial Degree: %d\n",
                degree
            );

            fprintf(
                output,
                "Initial X: %.6f\n",
                initialX
            );

            fprintf(
                output,
                "Final X: %.6f\n",
                finalX
            );

            fprintf(
                output,
                "Function Value: %.6f\n",
                functionValue
            );

            fprintf(
                output,
                "Iterations: %d\n",
                iterations
            );

            fprintf(
                output,
                "Execution Time: %.6f ms\n",
                executionTime
            );

            fclose(output);

            cout << "\nResult saved to: "
                 << outputFile << "\n";

        } else {

            cout << "\nWarning: Could not create output file.\n";
        }

        free(coefficients);
    }
}

/* ============================================================
   MAXFLOW / MINCUT DRIVER
   ============================================================ */

void runMaxFlowMinCut() {

    int choice;

    const char* testFiles[] = {
        "tests/maxflow/maxflow_10.txt",
        "tests/maxflow/maxflow_100.txt",
        "tests/maxflow/maxflow_1000.txt",
        "tests/maxflow/maxflow_10000.txt",
        "tests/maxflow/maxflow_50000.txt"
    };

    while (true) {

        cout << "\n";
        cout << "MAX FLOW / MIN CUT TEST CASES\n";
        cout << "=========================================\n";
        cout << "1. V = 10\n";
        cout << "2. V = 100\n";
        cout << "3. V = 1000\n";
        cout << "4. V = 10000\n";
        cout << "5. V = 50000\n";
        cout << "6. Back to Main Menu\n";
        cout << "=========================================\n";

        cout << "Enter test case: ";
        cin >> choice;

        if (choice == 6) {
            break;
        }

        if (choice < 1 || choice > 5) {
            cout << "\nInvalid choice. Please try again.\n";
            continue;
        }

        const string filename = testFiles[choice - 1];

        try {

            // Input reading and CSR conversion are
            // performed before timing.
            InputGraph input = readMaxflowInputFile(filename);

            // Start timing only for algorithm execution.
            auto start = chrono::steady_clock::now();

            MaxflowResult result =
                dinicMaxflowMincut(
                    input.csr,
                    input.source,
                    input.sink
                );

            auto end = chrono::steady_clock::now();

            double elapsedMs =
                chrono::duration<double, milli>(
                    end - start
                ).count();

            printMaxflowResult(
                result,
                input.source,
                input.sink,
                elapsedMs
            );

            // Save output.
            string outputFile =
                "output/maxflow/maxflow_" +
                to_string(choice) +
                "_run.txt";

            ofstream fout(outputFile);

            if (fout) {

                fout << "Algorithm: Maxflow-Mincut\n";
                fout << "Source: "
                     << input.source << "\n";
                fout << "Sink: "
                     << input.sink << "\n";

                fout << "Maximum flow: "
                     << result.max_flow << "\n";

                fout << "Minimum cut capacity: "
                     << result.min_cut_capacity << "\n";

                fout << "Source side:";

                for (int v : result.source_side) {
                    fout << " " << v;
                }

                fout << "\n";

                fout << "Sink side:";

                for (int v : result.sink_side) {
                    fout << " " << v;
                }

                fout << "\n";

                fout << "Cut edges:\n";

                for (const auto& e : result.cut_edges) {
                    fout << e.from << " "
                         << e.to << " "
                         << e.capacity << "\n";
                }

                fout << fixed << setprecision(6);

                fout << "Execution time: "
                     << elapsedMs
                     << " ms\n";

                fout << "Status: "
                     << (result.max_flow ==
                         result.min_cut_capacity
                             ? "PASS"
                             : "FAIL")
                     << "\n";

                cout << "\nResult saved to: "
                     << outputFile << "\n";
            }

        } catch (const exception& ex) {

            cout << "\nError: "
                 << ex.what()
                 << "\n";
        }
    }
}
/* ============================================================
   MAIN MENU
   ============================================================ */

int main() {

    int choice;

    while (true) {

        cout << "\n";
        cout << "CS509 ASSIGNMENT 3\n";
        cout << "=========================================\n";
        cout << "1. Gradient Descent\n";
        cout << "2. Max Flow / Min Cut\n";
        cout << "3. Exit\n";
        cout << "=========================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {

            runGradientDescent();

        } else if (choice == 2) {

            runMaxFlowMinCut();

        } else if (choice == 3) {

            cout << "\nExiting Assignment 3...\n";
            break;

        } else {

            cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}