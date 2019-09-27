#ifndef multiplication_h
#define multiplication_h

#include <stdio.h>

int* getColumn(int dim, int not_zero);
int multiplyMatrix(int **matr, int dim, int not_zero);
int multiplySparseMatrix(int dim, int not_zero, int *A, int *IA, int *JA);

#endif /* multiplication_h */
