#ifndef CSR_H
#define CSR_H

#include "graph.h"

// CSR Structure

typedef struct
{
    int vertices;
    int edges;

    /* Row Pointer Array */
    int *rowPtr;

    /* Column Index Array */
    int *colIndex;

    /* Edge Weight Array */
    int *weight;

} CSR;

// Function Prototypes 

// Create an empty CSR structure
CSR createCSR(int vertices, int edges);

// Convert Adjacency List to CSR
CSR convertToCSR(Graph graph);

// Print CSR Arrays
void printCSR(CSR csr);

// Free CSR Memory 
void freeCSR(CSR *csr);

#endif