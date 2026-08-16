#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

int main()
{
    int choice;

    while (1)
    {
        printf("\n=====================================\n");
        printf("CS509 BUDDY COMMON WRAPPER\n");
        printf("=====================================\n");
        printf("1. Run Assignment 1 \n");
        printf("2. Run Assignment 2 \n");
        printf("3. Run Assignment 3 \n");
        printf("0. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                if (_chdir("..\\Assignment_1_buddy") != 0)
                {
                    printf("Unable to open GEMM directory.\n");
                    break;
                }

                // Run GEMM
                system("graph.exe");

                // Return to Common_wrapper directory
                _chdir("..\\..\\Common_wrapper");

                break;
            }

            case 2:
            {
                if (_chdir("..\\Assignment_2") != 0)
                {
                    printf("Unable to open GEMM directory.\n");
                    break;
                }

                // Run graph
                system("graph2.exe");

                // Return to Common_wrapper directory
                _chdir("..\\..\\Common_wrapper");

                break;
            }

            case 3:
            {
                if (_chdir("..\\Assignment_3") != 0)
                {
                    printf("Unable to open GEMM directory.\n");
                    break;
                }

                // Run graph
                system("Assignment_3.exe");

                // Return to Common_wrapper directory
                _chdir("..\\..\\Common_wrapper");

                break;
            }

            case 0:
                printf("\nExiting...\n");
                return 0;

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
