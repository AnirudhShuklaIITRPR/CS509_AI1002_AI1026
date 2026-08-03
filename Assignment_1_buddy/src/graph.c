#include <stdio.h>
#include <stdlib.h>

#include "C:\Users\Dell\Downloads\CS509\Assignment_1_buddy\include\graph.h"

// Create Graph
Graph createGraph(int vertices)
{
    Graph graph;

    graph.vertices = vertices;
    graph.edges = 0;

    graph.adjList = (Node **)malloc(vertices * sizeof(Node *));

    for (int i = 0; i < vertices; i++)
    {
        graph.adjList[i] = NULL;
    }

    return graph;
}

// Add Edge
void addEdge(Graph *graph, int source, int destination, int weight)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->destination = destination;
    newNode->weight = weight;
    newNode->next = graph->adjList[source];

    graph->adjList[source] = newNode;

    graph->edges++;
}

// Read Graph From File
void readGraph(Graph *graph, const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Unable to open input file.\n");
        exit(1);
    }

    int source;
    int destination;

    fscanf(fp, "%d %d", &graph->vertices, &graph->edges);

    graph->adjList = (Node **)malloc(graph->vertices * sizeof(Node *));

    for (int i = 0; i < graph->vertices; i++)
    {
        graph->adjList[i] = NULL;
    }

    graph->edges = 0;

    while (fscanf(fp, "%d %d", &source, &destination) == 2)
    {
        addEdge(graph, source, destination, 1);
    }

    fclose(fp);
}

// Print Graph
void printGraph(Graph graph)
{
    printf("\nAdjacency List\n\n");

    for (int i = 0; i < graph.vertices; i++)
    {
        printf("%d -> ", i);

        Node *temp = graph.adjList[i];

        while (temp != NULL)
        {
            printf("%d ", temp->destination);
            temp = temp->next;
        }

        printf("\n");
    }
}

// Free Memory 
void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        Node *current = graph->adjList[i];

        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(graph->adjList);
}