#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "C:\\Users\\Dell\\Downloads\\CS509\\BUDDY\\Assignment_3\\include\\gradientDescent.h"

void runGradientDescent(){
    int choice;
    const char *testFiles[] = {
        "tests/gradientDescent/test_case_1.txt",
        "tests/gradientDescent/test_case_2.txt",
        "tests/gradientDescent/test_case_3.txt",
        "tests/gradientDescent/test_case_4.txt",
        "tests/gradientDescent/test_case_5.txt"
    };

    while (1){
        printf("\nGRADIENT DESCENT TEST CASES\n");
        printf("=========================================\n");
        printf("1. Test Case 1\n");
        printf("2. Test Case 2\n");
        printf("3. Test Case 3\n");
        printf("4. Test Case 4\n");
        printf("5. Test Case 5\n");
        printf("6. Back to Main Menu\n");

        printf("Enter test case: ");
        scanf("%d", &choice);

        if (choice == 6){
            break;
        }

        if (choice < 1 || choice > 5){
            printf("\nInvalid choice. Please try again.\n");
            continue;
        }

        const char *filename = testFiles[choice - 1];
        FILE *file = fopen(filename, "r");
        if (file == NULL){
            printf("\nUnable to open input file: %s\n", filename);
            continue;
        }

        int degree;
        double initialX;
        double learningRate;
        double tolerance;
        int maxIterations;

        char label[50];

        if (fscanf(file, "%s %d", label, &degree) != 2){
            printf("\nError reading degree.\n");
            fclose(file);
            continue;
        }

        double *coefficients = (double *)malloc((degree + 1) * sizeof(double));

        if (coefficients == NULL){
            printf("\nMemory allocation failed.\n");
            fclose(file);
            continue;
        }

        if (fscanf(file, "%s", label) != 1){
            printf("\nError reading coefficients.\n");
            free(coefficients);
            fclose(file);
            continue;
        }

        for (int i = 0; i <= degree; i++){
            if (fscanf(file, "%lf", &coefficients[i]) != 1){
                printf("\nError reading coefficient %d.\n", i);

                free(coefficients);
                fclose(file);
                continue;
            }
        }

        if (fscanf(file, "%s %lf", label, &initialX) != 2){
            printf("\nError reading INITIAL_X.\n");

            free(coefficients);
            fclose(file);
            continue;
        }

        if (fscanf(file, "%s %lf", label, &learningRate) != 2){
            printf("\nError reading LEARNING_RATE.\n");

            free(coefficients);
            fclose(file);
            continue;
        }

        if (fscanf(file, "%s %lf", label, &tolerance) != 2){
            printf("\nError reading TOLERANCE.\n");

            free(coefficients);
            fclose(file);
            continue;
        }

        if (fscanf(file, "%s %d", label, &maxIterations) != 2){
            printf("\nError reading MAX_ITERATIONS.\n");

            free(coefficients);
            fclose(file);
            continue;
        }

        fclose(file);

        int iterations = 0;
        double finalX;

        clock_t start = clock();
        finalX = gradientDescent(
            degree,
            coefficients,
            initialX,
            learningRate,
            tolerance,
            maxIterations,
            &iterations
        );
        clock_t end = clock();
        double executionTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
        double functionValue = 0.0;
        double power = 1.0;

        for (int i = 0; i <= degree; i++){
            functionValue += coefficients[i] * power;
            power *= finalX;
        }

        printf("\nAlgorithm: Gradient Descent\n");
        printf("Test Case: %d\n", choice);
        printf("Input File: %s\n\n", filename);

        printf("Polynomial Degree: %d\n", degree);
        printf("Initial X: %.6f\n", initialX);
        printf("Final X: %.6f\n", finalX);
        printf("Function Value: %.6f\n", functionValue);
        printf("Iterations: %d\n", iterations);
        printf("Execution Time: %.6f ms\n", executionTime);

        char outputFile[200];
        sprintf(outputFile, "output/gradientDescent/test_case_%d.txt", choice);
        FILE *output = fopen(outputFile, "w");

        if (output != NULL){
            fprintf(output, "Algorithm: Gradient Descent\n");
            fprintf(output, "Test Case: %d\n", choice);
            fprintf(output, "Input File: %s\n\n", filename);

            fprintf(output, "Polynomial Degree: %d\n", degree);
            fprintf(output, "Initial X: %.6f\n", initialX);
            fprintf(output, "Final X: %.6f\n", finalX);
            fprintf(output, "Function Value: %.6f\n", functionValue);
            fprintf(output, "Iterations: %d\n", iterations);
            fprintf(output, "Execution Time: %.6f ms\n", executionTime);

            fclose(output);

            printf("\nResult saved to: %s\n", outputFile);
        }
        else{
            printf("\nWarning: Could not create output file.\n");
        }

        free(coefficients);
    }
}

void runMaxFlowMinCut(){
    printf("\nMAX FLOW / MIN CUT\n");
    /*
     * Max Flow / Min Cut implementation is implemented by Kalki Dang.
     */
}


int main(){
    int choice;
    while (1){
        printf("\nCS509 ASSIGNMENT 3\n");
        printf("=========================================\n");
        printf("1. Gradient Descent\n");
        printf("2. Max Flow / Min Cut\n");
        printf("3. Exit\n");
        printf("=========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1){
            runGradientDescent();
        }
        else if (choice == 2){
            runMaxFlowMinCut();
        }
        else if (choice == 3){
            printf("\nExiting Assignment 3...\n");
            break;
        }
        else{
            printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}