#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "C:\Users\Dell\Downloads\CS509\BUDDY\Assignment_2\include\csr.h"
#include "C:\Users\Dell\Downloads\CS509\BUDDY\Assignment_2\include\connected_components.h"
#include "C:\Users\Dell\Downloads\CS509\BUDDY\Assignment_2\include\triangle_counting.h"
#include "C:\Users\Dell\Downloads\CS509\BUDDY\Assignment_2\include\betweeness_centrality.h"

int main()
{
    int choice;
    int testCase;

    char filename[150];
    char outputFile[200];

    while (1){
        
        printf("\nCS509 ASSIGNMENT 2\n");
        printf("1. Connected Components\n");
        printf("2. Triangle Counting\n");
        printf("3. Betweenness Centrality\n");
        printf("4. Exit\n");
        printf("-------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4){
            printf("\nProgram terminated.\n");
            break;
        }

        if (choice < 1 || choice > 4){
            printf("\nInvalid choice.\n");
            continue;
        }


        printf("\nAvailable Test Cases:\n");
        printf("10\n");
        printf("100\n");
        printf("1000\n");
        printf("10000\n");   // Large ones are not for Betweeness Centrality
        printf("50000\n");
        printf("100000\n");

        printf("\nEnter test case: ");
        scanf("%d", &testCase);

        sprintf(filename, "test/test_case_%d.txt", testCase);

        if (choice == 1)
        {
            sprintf(outputFile, "output/connectedcomponents/output_%d.txt", testCase);
        }
        else if (choice == 2)
        {
            sprintf(outputFile, "output/trianglecounting/output_%d.txt", testCase);
        }
        else
        {
            sprintf(outputFile, "output/betweennesscentrality/output_%d.txt", testCase);
        }

        FILE *fo = fopen(outputFile, "w");

        if (fo == NULL)
        {
            printf("\nUnable to create output file:\n");
            printf("%s\n", outputFile);
            printf("Make sure the output folders exist.\n");
            continue;
        }

        if (choice == 1)
        {
            printf("\nCONNECTED COMPONENTS\n");

            readGraph(filename);
            convertCSR();

            int *component = (int *)malloc(vertices * sizeof(int));

            if (component == NULL)            {
                printf("Unable to allocate memory.\n");

                fclose(fo);
                freeGraph();

                continue;
            }

            clock_t start = clock();
            int componentCount = connectedComponents(vertices, row_ptr, col_idx, component);
            clock_t end = clock();
            double executionTime = (double)(end - start) / CLOCKS_PER_SEC;

            printf("\nAlgorithm: Connected Components\n");
            printf("Test Case: %d\n", testCase);
            printf("Number of components: %d\n", componentCount);

            printf("\nVertex Component\n");

            for (int i = 0; i < vertices; i++)
            {
                printf("%d %d\n",
                       i,
                       component[i]);
            }

            printf("\nExecution Time: %.12f seconds\n", executionTime);
            
            fprintf(fo, "CONNECTED COMPONENTS RESULT\n");
            fprintf(fo, "Test Case: %d\n", testCase);
            fprintf(fo, "Input File: %s\n\n", filename);
            fprintf(fo, "Number of components: %d\n\n", componentCount);
            fprintf(fo, "Vertex Component\n");
            for (int i = 0; i < vertices; i++){
                fprintf(fo, "%d %d\n", i, component[i]);
            }

            fprintf(fo, "\nExecution Time: %.12f seconds\n", executionTime);

            free(component);
            freeGraph();
        }

        else if (choice == 2)
        {
            printf("\nTRIANGLE COUNTING\n");

            readGraph(filename);
            convertCSR();

            clock_t start = clock();
            int triangleCount = triangleCounting(vertices, row_ptr, col_idx);
            clock_t end = clock();
            double executionTime = (double)(end - start) / CLOCKS_PER_SEC; 

            printf("\nAlgorithm: Triangle Counting\n");
            printf("Test Case: %d\n", testCase);
            printf("Number of triangles: %d\n", triangleCount);
            printf("Execution Time: %.12f seconds\n", executionTime);

            fprintf(fo, "TRIANGLE COUNTING RESULT\n");
            fprintf(fo, "Test Case: %d\n", testCase);
            fprintf(fo, "Input File: %s\n\n", filename);
            fprintf(fo, "Number of triangles: %d\n", triangleCount);
            fprintf(fo, "Execution Time: %.12f seconds\n", executionTime);

            freeGraph();
        }

        else if (choice == 3)
        {
            printf("\nBETWEENNESS CENTRALITY\n");
            
            readGraph(filename);
            convertCSR();
            
            double *centrality = (double *)malloc(vertices * sizeof(double));
            
            if (centrality == NULL){
                printf("Unable to allocate memory.\n");
                
                fclose(fo);
                freeGraph();
                
                continue;
            }
            
            clock_t start = clock();
            betweennessCentrality(vertices, row_ptr, col_idx, centrality);
            clock_t end = clock();
            double executionTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
            
            printf("\nAlgorithm: Betweenness Centrality\n");
            printf("Test Case: %d\n\n", testCase);
            printf("Vertex Centrality\n");
            
            for (int i = 0; i < vertices; i++){
                printf("%d %.2f\n", i, centrality[i]);
            }
            
            printf("\nExecution Time: %.12f ms\n", executionTime);
            
            fprintf(fo, "Algorithm: Betweenness Centrality\n");
            fprintf(fo, "Test Case: %d\n\n", testCase);
            fprintf(fo, "Vertex Centrality\n");
            for (int i = 0; i < vertices; i++){
                fprintf(fo, "%d %.2f\n", i, centrality[i]);
            }
            
            fprintf(fo, "\nExecution Time: %.6f ms\n", executionTime);
            
            free(centrality);
            freeGraph();

            break;
        }
        fclose(fo);
    }

    return 0;
}
