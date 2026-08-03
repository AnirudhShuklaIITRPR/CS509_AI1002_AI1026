#ifndef GRAPH_H
#define GRAPH_H

// Node of Adjacency List 
typedef struct Node
{
    int destination;
    int weight;

    struct Node *next;

} Node;

// Graph Structure
typedef struct
{
    int vertices;
    int edges;

    Node **adjList;

} Graph;

// Function Prototypes
Graph createGraph(int vertices);

void addEdge(Graph *graph, int source, int destination, int weight);
void readGraph(Graph *graph, const char *filename);
void printGraph(Graph graph);
void freeGraph(Graph *graph);

#endif