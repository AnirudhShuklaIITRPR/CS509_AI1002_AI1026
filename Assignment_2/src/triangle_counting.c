#include <stdio.h>
#include "C:\Users\Dell\Downloads\CS509\BUDDY\Assignment_2\include\triangle_counting.h"

int triangleCounting(int vertices, int *row_ptr, int *col_idx){
    int triangleCount = 0;
    for (int u = 0; u < vertices; u++){
        for (int i = row_ptr[u]; i < row_ptr[u + 1]; i++){
            int v = col_idx[i];
            
            // Only consider u < v. This ensures each edge is considered once.
            if (u < v){
                int p = row_ptr[u];
                int q = row_ptr[v];

                while (p < row_ptr[u + 1] && q < row_ptr[v + 1]){
                    if (col_idx[p] == col_idx[q]){
                        int w = col_idx[p];
                        // Require v < w.Therefore only triangles satisfying u < v < w are counted.
                        if (v < w){
                            triangleCount++;
                        }
                        p++;
                        q++;
                    }
                    else if (col_idx[p] < col_idx[q]){
                        p++;
                    }
                    else{
                        q++;
                    }
                }
            }
        }
    }

    return triangleCount;
}
