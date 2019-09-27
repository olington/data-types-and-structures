#ifndef graph_h
#define graph_h

#include "interface.h"
#define INFINIT 40075

typedef struct matrix_t
{
    unsigned int n;
    float **data;
} matr;

void free_matrix_rows(float **data, int n);
float **allocate_matrix_rows(int n);
matr *create_matr(unsigned int n);
void free_matr(matr *matrix);
matr *read_matr(FILE *f);
void print_matr(FILE *f, const matr *m);
matr *floyd_warshall(const matr *a);
void show_matr_gv(const matr *a);
void show_best_gv(const matr *a, const matr *best);

#endif /* graph_h */
