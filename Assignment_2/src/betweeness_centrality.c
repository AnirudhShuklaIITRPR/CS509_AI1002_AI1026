#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "C:\Users\Dell\Downloads\CS509\BUDDY\Assignment_2\include\betweeness_centrality.h"

#define INF DBL_MAX

void betweennessCentrality(int vertices, int *row_ptr, int *col_idx, double *centrality){
    double *distance;
    double *sigma;
    double *dependency;

    int *visited;
    int *stack;

    //  Predecessor lists. Each vertex stores predecessors that occur on shortest paths.
    int **predecessors;
    int *predCount;

    distance = malloc(vertices * sizeof(double));
    sigma = malloc(vertices * sizeof(double));
    dependency = malloc(vertices * sizeof(double));

    visited = malloc(vertices * sizeof(int));
    stack = malloc(vertices * sizeof(int));

    predecessors = malloc(vertices * sizeof(int *));
    predCount = malloc(vertices * sizeof(int));

    if (distance == NULL ||
        sigma == NULL ||
        dependency == NULL ||
        visited == NULL ||
        stack == NULL ||
        predecessors == NULL ||
        predCount == NULL)
    {
        printf("Memory allocation failed.\n");

        free(distance);
        free(sigma);
        free(dependency);
        free(visited);
        free(stack);
        free(predecessors);
        free(predCount);

        return;
    }

    // Allocate predecessor arrays. Maximum possible predecessors for a vertex is its degree.
    for (int i = 0; i < vertices; i++)
    {
        int degree = row_ptr[i + 1] - row_ptr[i];

        predecessors[i] =
            malloc(degree * sizeof(int));

        predCount[i] = 0;
    }

    // Initialize centrality.
    for (int i = 0; i < vertices; i++)
    {
        centrality[i] = 0.0;
    }

    // Run Brandes from every source.
    for (int source = 0; source < vertices; source++)
    {
        // Initialize.
        for (int i = 0; i < vertices; i++)
        {
            distance[i] = INF;
            sigma[i] = 0.0;
            dependency[i] = 0.0;
            visited[i] = 0;
            predCount[i] = 0;
        }

        distance[source] = 0.0;
        sigma[source] = 1.0;

        int stackSize = 0;

        // Dijkstra.
        for (int iteration = 0;
             iteration < vertices;
             iteration++)
        {
            int u = -1;

            double minimum = INF;

        
            for (int i = 0; i < vertices; i++)
            {
                if (!visited[i] &&
                    distance[i] < minimum)
                {
                    minimum = distance[i];
                    u = i;
                }
            }

            if (u == -1)
                break;

            visited[u] = 1;

            stack[stackSize++] = u;

            for (int i = row_ptr[u]; i < row_ptr[u + 1]; i++){
                int v = col_idx[i];

                // Your CSR currently stores weights, but this function only receives col_idx.
                // Therefore this version treats the graph as unweighted.
                double weight = 1.0;
                double newDistance = distance[u] + weight;

                if (newDistance < distance[v]){
                    distance[v] = newDistance;
                    sigma[v] = sigma[u];
                    predCount[v] = 0;
                    predecessors[v][predCount[v]++] = u;
                }

                else if (fabs(newDistance - distance[v]) < 1e-12){
                    sigma[v] += sigma[u];

                    predecessors[v][predCount[v]++] = u;
                }
            }
        }

        // Accumulation phase.
        while (stackSize > 0){
            int w = stack[--stackSize];

            for (int i = 0; i < predCount[w]; i++){
                int v = predecessors[w][i];

                if (sigma[w] != 0.0){
                    dependency[v] +=
                        (sigma[v] / sigma[w]) *
                        (1.0 + dependency[w]);
                }
            }

            if (w != source){
                centrality[w] += dependency[w];
            }
        }
    }

    for (int i = 0; i < vertices; i++){
        centrality[i] /= 2.0;
    }

    for (int i = 0; i < vertices; i++){
        free(predecessors[i]);
    }

    free(distance);
    free(sigma);
    free(dependency);
    free(visited);
    free(stack);
    free(predecessors);
    free(predCount);
}