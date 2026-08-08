#ifndef CSR_H
#define CSR_H

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

extern int vertices;
extern int edges;

extern Node **adj;

extern int *row_ptr;
extern int *col_idx;

void readGraph(char filename[]);
void convertCSR();
void printCSR();
void freeGraph();

#endif