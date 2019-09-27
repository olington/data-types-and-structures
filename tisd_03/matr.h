#ifndef matr_h
#define matr_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

typedef struct
{
    int val;
    int column;
    struct JA *next;
} JA;

void convertIntoSparseMatrix(int **matr, int dim, int not_zero, int *A, int *IA, int *JA);
void freeMatrix(int **matr, int dim);

#endif /* matr_h */
