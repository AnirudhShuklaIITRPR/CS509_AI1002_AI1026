#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "C:\Users\Dell\Downloads\CS509\Assignment_1_buddy\include\graph.h"
#include "C:\Users\Dell\Downloads\CS509\Assignment_1_buddy\include\csr.h"
#include "C:\Users\Dell\Downloads\CS509\Assignment_1_buddy\include\bfs.h"
#include "C:\Users\Dell\Downloads\CS509\Assignment_1_buddy\include\dfs.h"
#include "C:\Users\Dell\Downloads\CS509\Assignment_1_buddy\include\sssp.h"
int main()
{
    Graph graph;
    CSR csr;

    int choice;
    int source;

    clock_t start, end;
    double executionTime;

    // Read Graph
    readGraph(&graph, "test/test_case_4.txt");

    // Convert Adjacency List to CSR

    csr = convertToCSR(graph);
    FILE *fo = fopen("output/output5.txt", "w");

    if (fo == NULL)
    {
        printf("Unable to create output file.\n");
        return 1;
    }

    do
    {
        printf("\n=====================================\n");
        printf("      GRAPH ALGORITHMS MENU\n");
        printf("=====================================\n");
        printf("1. Breadth First Search (BFS)\n");
        printf("2. Depth First Search (DFS)\n");
        

        printf("3. Print CSR Representation\n");
        printf("4. Single Source Shortest Path(SSSP)")
        printf("5. Exit\n");
        printf("=====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:

                printf("Enter Source Vertex: ");
                scanf("%d", &source);

                start = clock();

                BFS(csr, source);

                end = clock();

                executionTime = (double)(end-start)/CLOCKS_PER_SEC;

                printf("\nExecution Time : %.6f seconds\n",executionTime);
                fprintf(fo,"\nBFS Source : %d\n",source);
                fprintf(fo,"Execution Time : %.6f seconds\n",executionTime);

                break;

            case 2:

                printf("Enter Source Vertex: ");
                scanf("%d",&source);

                start = clock();

                DFS(csr,source);

                end = clock();

                executionTime = (double)(end-start)/CLOCKS_PER_SEC;

                printf("\nExecution Time : %.6f seconds\n", executionTime);

                fprintf(fo,"\nDFS Source : %d\n",source);
                fprintf(fo,"Execution Time : %.6f seconds\n", executionTime);

                break;

            case 3:

                printCSR(csr);

                break;
            case 4:
case 4:

    start = clock();

    readGraph("sssp_100.txt");   // or whichever test file you want
    convertCSR();
    dijkstra();
    printShortestPath();
    freeMemory();

    end = clock();

    executionTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nExecution Time : %.6f seconds\n", executionTime);

    fprintf(fo, "\nSSSP Execution Time : %.6f seconds\n", executionTime);

    break;
            case 5:

                printf("\nProgram Terminated.\n");

                break;

            default:

                printf("\nInvalid Choice.\n");
        }

    }while(choice != 5);
    fclose(fo);
    freeCSR(&csr);
    freeGraph(&graph);
    return 0;
}
