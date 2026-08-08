#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "csr.h"
#include "connected_components.h"

int main()
{
    // Read graph
    readGraph("cc_10.txt");

    // Convert adjacency list to CSR
    convertCSR();

    // Allocate component array
    int *component = (int *)malloc(vertices * sizeof(int));

    // Start timing
    clock_t start = clock();

    // Find connected components
    int componentCount =
        connectedComponents(vertices, row_ptr, col_idx, component);

    // Stop timing
    clock_t end = clock();

    double executionTime =
        (double)(end - start) / CLOCKS_PER_SEC;

    // Print result
    printf("Algorithm: Connected Components\n");
    printf("Number of components: %d\n", componentCount);

    printf("Vertex Component\n");

    for (int i = 0; i < vertices; i++)
    {
        printf("%d %d\n", i, component[i]);
    }

    printf("Execution time: %.6f seconds\n",
           executionTime);

    // Free memory
    free(component);

    freeGraph();

    return 0;
}