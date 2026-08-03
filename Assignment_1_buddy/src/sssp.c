#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "sssp.h"
Node **adj;

int vertices;
int edges;

int source;

int *row_ptr;
int *col_idx;
int *values;

int *distance;
int *visited;
void readGraph(char filename[])
{
    char path[200];

    sprintf(path, "Test_Case/%s", filename);

    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        printf("Cannot open %s\n", path);
        exit(0);
    }

    fscanf(fp, "%d %d", &vertices, &edges);

    adj = (Node **)malloc(vertices * sizeof(Node *));

    for (int i = 0; i < vertices; i++)
        adj[i] = NULL;

    for (int i = 0; i < vertices; i++)
    {
        int u, degree;

        fscanf(fp, "%d %d", &u, &degree);

        Node *tail = NULL;

        for (int j = 0; j < degree; j++)
        {
            int v, w;

            fscanf(fp, "%d %d", &v, &w);

            Node *temp = (Node *)malloc(sizeof(Node));

            temp->vertex = v;
            temp->weight = w;
            temp->next = NULL;

            if (adj[u] == NULL)
            {
                adj[u] = temp;
                tail = temp;
            }
            else
            {
                tail->next = temp;
                tail = temp;
            }
        }
    }

    char str[20];
    fscanf(fp, "%s %d", str, &source);

    fclose(fp);
}
void convertCSR()
{
    row_ptr = (int *)malloc((vertices + 1) * sizeof(int));

    col_idx = (int *)malloc(edges * sizeof(int));

    values = (int *)malloc(edges * sizeof(int));

    int index = 0;

    for (int i = 0; i < vertices; i++)
    {
        row_ptr[i] = index;

        Node *curr = adj[i];

        while (curr != NULL)
        {
            col_idx[index] = curr->vertex;

            values[index] = curr->weight;

            index++;

            curr = curr->next;
        }
    }

    row_ptr[vertices] = index;
}
void printCSR()
{
    printf("\nrow_ptr\n");

    for (int i = 0; i <= vertices; i++)
        printf("%d ", row_ptr[i]);

    printf("\n\n");

    printf("col_idx\n");

    for (int i = 0; i < edges; i++)
        printf("%d ", col_idx[i]);

    printf("\n\n");

    printf("values\n");

    for (int i = 0; i < edges; i++)
        printf("%d ", values[i]);

    printf("\n");
}
void dijkstra()
{
    distance = (int *)malloc(vertices * sizeof(int));
    visited = (int *)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[source] = 0;

    for (int count = 0; count < vertices - 1; count++)
    {
        int u = -1;
        int minDist = INT_MAX;

        for (int i = 0; i < vertices; i++)
        {
            if (!visited[i] && distance[i] < minDist)
            {
                minDist = distance[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int i = row_ptr[u]; i < row_ptr[u + 1]; i++)
        {
            int v = col_idx[i];
            int w = values[i];

            if (!visited[v] &&
                distance[u] != INT_MAX &&
                distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
            }
        }
    }
}
void printShortestPath()
{
    printf("\nAlgorithm : SSSP\n");
    printf("Source : %d\n\n", source);

    printf("Vertex\tDistance\n");

    for (int i = 0; i < vertices; i++)
    {
        if (distance[i] == INT_MAX)
            printf("%d\tINF\n", i);
        else
            printf("%d\t%d\n", i, distance[i]);
    }
}
void freeMemory()
{
    for (int i = 0; i < vertices; i++)
    {
        Node *curr = adj[i];

        while (curr != NULL)
        {
            Node *next = curr->next;
            free(curr);
            curr = next;
        }
    }

    free(adj);
    free(row_ptr);
    free(col_idx);
    free(values);
    free(distance);
    free(visited);
}