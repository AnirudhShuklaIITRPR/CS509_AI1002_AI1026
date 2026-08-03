#ifndef DFS_H
#define DFS_H

#include "csr.h"

// Recursive DFS Function 
void DFSUtil(CSR csr, int vertex, int visited[]);

// Driver Function
void DFS(CSR csr, int source);

#endif