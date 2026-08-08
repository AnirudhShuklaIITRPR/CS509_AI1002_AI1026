#include <stdio.h>
#include <stdlib.h>

#include "csr.h"

Node **adj;

int vertices;
int edges;

int *row_ptr;
int *col_idx;


void readGraph(char filename[])
{
    char path[200];

    sprintf(path, "test/%s", filename);

    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        printf("Cannot open %s\n", path);
        exit(1);
    }

    // Read vertices and edges
    fscanf(fp, "%d %d", &vertices, &edges);

    // Allocate adjacency list
    adj = (Node **)malloc(vertices * sizeof(Node *));

    // Initialize adjacency list
    for (int i = 0; i < vertices; i++)
        adj[i] = NULL;

    // Read adjacency list
    for (int i = 0; i < vertices; i++)
    {
        int u, degree;

        fscanf(fp, "%d %d", &u, &degree);

        Node *tail = NULL;

        for (int j = 0; j < degree; j++)
        {
            int v;

            fscanf(fp, "%d", &v);

            Node *temp = (Node *)malloc(sizeof(Node));

            temp->vertex = v;
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

    fclose(fp);
}


void convertCSR()
{
    row_ptr = (int *)malloc((vertices + 1) * sizeof(int));

    // Total number of adjacency entries
    int totalEntries = 0;

    for (int i = 0; i < vertices; i++)
    {
        Node *curr = adj[i];

        while (curr != NULL)
        {
            totalEntries++;
            curr = curr->next;
        }
    }

    col_idx = (int *)malloc(totalEntries * sizeof(int));

    int index = 0;

    for (int i = 0; i < vertices; i++)
    {
        row_ptr[i] = index;

        Node *curr = adj[i];

        while (curr != NULL)
        {
            col_idx[index] = curr->vertex;

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

    for (int i = 0; i < row_ptr[vertices]; i++)
        printf("%d ", col_idx[i]);

    printf("\n");
}


void freeGraph()
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
}