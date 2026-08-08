#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "csr.h"
#include "connected_components.h"

int main()
{
    int choice;
    char filename[100];

    while (1)
    {
        printf("\n===== ASSIGNMENT 2 =====\n");
        printf("1. Connected Components\n");
        printf("2. Triangle Counting\n");
        printf("3. Betweenness Centrality\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Exiting program...\n");
            break;
        }

        printf("Enter input filename: ");
        scanf("%s", filename);

        switch (choice)
        {
        case 1:
        {
            // Connected Components

            readGraph(filename);

            convertCSR();

            int *component =
                (int *)malloc(vertices * sizeof(int));

            clock_t start = clock();

            int componentCount =
                connectedComponents(
                    vertices,
                    row_ptr,
                    col_idx,
                    component);

            clock_t end = clock();

            double executionTime =
                (double)(end - start) / CLOCKS_PER_SEC;

            printf("\nAlgorithm: Connected Components\n");
            printf("Number of components: %d\n",
                   componentCount);

            printf("Vertex Component\n");

            for (int i = 0; i < vertices; i++)
            {
                printf("%d %d\n",
                       i,
                       component[i]);
            }

            printf("Execution time: %.6f seconds\n",
                   executionTime);

            free(component);

            freeGraph();

            break;
        }

        case 2:
            // Triangle Counting
            // Buddy Anirudh will implement
            printf("Triangle Counting selected.\n");
            break;

        case 3:
            // Betweenness Centrality
            // Buddy Anirudh will implement
            printf("Betweenness Centrality selected.\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}