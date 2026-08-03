#include <stdio.h>
#include <stdlib.h>

#include "C:\Users\Dell\Downloads\CS509\Assignment_1_buddy\include\csr.h"

// Create Empty CSR
CSR createCSR(int vertices, int edges)
{
    CSR csr;

    csr.vertices = vertices;
    csr.edges = edges;

    csr.rowPtr = (int *)malloc((vertices + 1) * sizeof(int));
    csr.colIndex = (int *)malloc(edges * sizeof(int));
    csr.weight = (int *)malloc(edges * sizeof(int));

    return csr;
}

// Convert Adjacency List to CSR

CSR convertToCSR(Graph graph)
{
    CSR csr = createCSR(graph.vertices, graph.edges);

    int edgeIndex = 0;

    for (int i = 0; i < graph.vertices; i++)
    {
        csr.rowPtr[i] = edgeIndex;

        Node *temp = graph.adjList[i];

        while (temp != NULL)
        {
            csr.colIndex[edgeIndex] = temp->destination;
            csr.weight[edgeIndex] = temp->weight;

            edgeIndex++;

            temp = temp->next;
        }
    }

    csr.rowPtr[graph.vertices] = edgeIndex;

    return csr;
}

// Print CSR

void printCSR(CSR csr)
{
    int i;
    printf("\nCSR Representation\n");
    printf("\nRow Pointer:\n");

    for (i = 0; i <= csr.vertices; i++)
        printf("%d ", csr.rowPtr[i]);

    printf("\n\nColumn Index:\n");

    for (i = 0; i < csr.edges; i++)
        printf("%d ", csr.colIndex[i]);

    printf("\n\nWeights:\n");

    for (i = 0; i < csr.edges; i++)
        printf("%d ", csr.weight[i]);

    printf("\n");
}

// Free Memory

void freeCSR(CSR *csr)
{
    free(csr->rowPtr);
    free(csr->colIndex);
    free(csr->weight);
}