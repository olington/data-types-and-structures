#include <stdio.h>
#include "menu.h"
#include "matr.h"
#include "input.h"
#include "multiplication.h"
#include "output.h"
#include "testing.h"

int main()
{
    int status = 0;
    
    int choice;
    int menu = 1;
    
    int **matr;
    int dim = 0;
    int not_zero = 0;
    
    while(menu)
    {
        printf("   Matrix multiplication by a column vector\n\n");
        printf("   Choose one of the following actions:\n");
        printf("1. Work with matrix and vector\n");
        printf("2. Comparison of the algorithms\n");
        printf("0. Exit\n");
        
        printf("\nOption: ");
        
        if (scanf("%i", &choice) == 0)
            choice = 3;
        
        switch(choice)
        {
            case 1:
                printf("\n");
                printf("   Select the matrix input method:\n");
                printf("1. Input manually\n");
                printf("2. Input from file\n");
                printf("0. Back to menu\n");
                
                printf("\nOption: ");
                
                if (scanf("%i", &choice) == 0)
                    choice = 3;
                
                switch(choice)
                {
                    case 1:
                        matr = manualInput(&dim, &not_zero);
                        if (matr == NULL)
                            status = -1;
                        break;
                    case 2:
                        matr = fileInput(&dim, &not_zero);
                        break;
                    case 0:
                        menu = 0;
                        system("clear");
                        break;
                    default:
                        break;
                }
                
                int *A = (int *)malloc(not_zero * sizeof(int));
                if (A == NULL)
                    status = -1;
                
                int *IA = (int *)malloc(not_zero * sizeof(int));
                if (IA == NULL)
                    status = -1;
                
                int *JA = (int *)malloc((not_zero + 1) * sizeof(int));
                if (JA == NULL)
                    status = -1;
                
                if (not_zero != 0)
                    convertIntoSparseMatrix(matr, dim, not_zero, A, IA, JA);
                
                while ((choice = menuWork()) != 0 && status == 0)
                {
                    switch(choice)
                    {
                        case 1:
                            if (not_zero ==  0)
                                printf("\nThere are no nonzero elements in the matrix\n");
                            else
                                status = multiplySparseMatrix(dim, not_zero, A, IA, JA);
                            break;
                        case 2:
                            if (not_zero ==  0)
                                printf("\nZero column\n");
                            else
                                status = multiplyMatrix(matr, dim, not_zero);
                            break;
                        case 3:
                            printMatrix(matr, dim);
                            break;
                        case 4:
                            if (not_zero ==  0)
                                printf("\nThere are no nonzero elements in the matrix\n");
                            else
                                printSparseMatrix(dim, not_zero, A, IA, JA);
                            break;
                        default:
                            break;
                    }
                }
                
                if (status == -1)
                    printf("\nMemory allocation error\n");
                freeMatrix(matr, dim);
                
                if (not_zero !=  0)
                {
                    if (!A)
                        free(A);
                    if (!IA)
                        free(IA);
                    if (!JA)
                        free(JA);
                }
                break;
            case 2:
                testing();
                //efficient();
                break;
            case 0:
                menu = 0;
                break;
            default:
                break;
        }
    }
    return status;
}
