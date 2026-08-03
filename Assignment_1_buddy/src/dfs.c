#include <stdio.h>
#include <stdlib.h>

#include "C:\Users\Dell\Downloads\CS509\Assignment_1_buddy\include\dfs.h"

// Recursive DFS Function
void DFSUtil(CSR csr, int vertex, int visited[])
{
    visited[vertex] = 1;
    printf("%d ", vertex);

    // Visit all adjacent vertices
    for (int i = csr.rowPtr[vertex] ; i < csr.rowPtr[vertex + 1] ; i++)
    {
        int neighbour = csr.colIndex[i];
        if (!visited[neighbour])
        {
            DFSUtil(csr, neighbour, visited);
        }
    }
}

// Driver Function 
void DFS(CSR csr, int source)
{
    int *visited;
    visited = (int *)calloc(csr.vertices, sizeof(int));
    printf("\nDFS Traversal\n\n");
    DFSUtil(csr, source, visited);
    printf("\n");
    free(visited);
}