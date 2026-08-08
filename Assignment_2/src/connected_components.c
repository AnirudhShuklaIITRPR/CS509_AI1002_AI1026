#include <stdio.h>
#include <stdlib.h>

#include "connected_components.h"


int connectedComponents(int vertices,
                        int *row_ptr,
                        int *col_idx,
                        int *component)
{
    int *visited = (int *)calloc(vertices, sizeof(int));

    int *queue = (int *)malloc(vertices * sizeof(int));

    int componentCount = 0;

    for (int start = 0; start < vertices; start++)
    {
        if (visited[start])
            continue;

        int front = 0;
        int rear = 0;

        queue[rear++] = start;

        visited[start] = 1;

        component[start] = componentCount;

        while (front < rear)
        {
            int u = queue[front++];

            // CSR neighbours of u
            for (int i = row_ptr[u];
                 i < row_ptr[u + 1];
                 i++)
            {
                int v = col_idx[i];

                if (!visited[v])
                {
                    visited[v] = 1;

                    component[v] = componentCount;

                    queue[rear++] = v;
                }
            }
        }

        componentCount++;
    }

    free(visited);
    free(queue);

    return componentCount;
}