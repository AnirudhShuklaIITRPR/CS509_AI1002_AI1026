#ifndef SSSP_H
#define SSSP_H

typedef struct Node
{
    int vertex;
    int weight;
    struct Node *next;
} Node;

void readGraph(char filename[]);
void convertCSR();
void dijkstra();
void printShortestPath();
void freeMemory();

#endif