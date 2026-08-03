#include <stdio.h>
#include <stdlib.h>

#include "C:\Users\Dell\Downloads\CS509\Assignment_1_buddy\include\bfs.h"

// Breadth First Search 
void BFS(CSR csr, int source)
{
    int *visited;
    int *queue;

    int front = 0;
    int rear = 0;

    visited = (int *)calloc(csr.vertices, sizeof(int));
    queue = (int *)malloc(csr.vertices * sizeof(int));

    // Start BFS
    visited[source] = 1;
    queue[rear++] = source;

    printf("\nBFS Traversal\n\n");

    while (front < rear)
    {
        int current = queue[front++];

        printf("%d ", current);

        // Traverse all neighbours of current vertex
        for (int i = csr.rowPtr[current] ; i < csr.rowPtr[current + 1] ; i++)
        {
            int neighbour = csr.colIndex[i];

            if (!visited[neighbour])
            {
                visited[neighbour] = 1;
                queue[rear++] = neighbour;
            }
        }
    }

    printf("\n");

    free(queue);
    free(visited);
}