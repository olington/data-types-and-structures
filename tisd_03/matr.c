#include "matr.h"

void convertIntoSparseMatrix(int **matr, int dim, int not_zero, int *A, int *IA, int *JA)
{
    int s;
    int flag = 0;
    
    JA[dim] = not_zero;
    s = not_zero - 1;
    for (int i = dim - 1; i >= 0; i--)
    {
        flag = 0;
        for (int j = dim - 1; j >= 0; j--)
        {
            if (matr[j][i] != 0)
            {
                A[s] = matr[j][i];
                IA[s] = j;
                JA[i] = s;
                flag = 1;
                s--;
            }
        }
        if (flag == 0)
            JA[i] = JA[i + 1];
    }
}

void freeMatrix(int **matr, int dim)
{
    if (matr != NULL)
    {
        for (int i = 0; i < dim; i++)
        {
            if (matr[i] != NULL)
                free(matr[i]);
        }
        free(matr);
    }
}
