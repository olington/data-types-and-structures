#include "output.h"

void printMatrix(int **matr, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
            printf("%3d ", matr[i][j]);
        printf("\n");
    }
}

void printSparseMatrix(int dim, int not_zero, int *A, int *IA, int *JA)
{
    printf(" A: ");
    for (int i = 0; i < not_zero; i++)
        printf("%d ",A[i]);
    printf("\n");
    
    printf("IA: ");
    for (int i = 0; i < not_zero; i++)
        printf("%d ",IA[i]);
    printf("\n");
    
    printf("JA: ");
    for (int i = 0; i < dim + 1; i++)
        printf("%d ",JA[i]);
    printf("\n");
}
