#ifndef output_h
#define output_h

#include <stdio.h>

void printMatrix(int **matr, int dim);
void printSparseMatrix(int dim, int not_zero, int *A, int *IA, int *JA);

#endif /* output_h */
