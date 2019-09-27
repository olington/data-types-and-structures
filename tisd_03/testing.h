#ifndef testing_h
#define testing_h

#define n1 100
#define n2 500
#define n3 1000

#define raz1 47
#define raz2 48
#define raz3 49

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

typedef struct IA
{
    int index;
    int string;
    int column;
    struct IA *next;
} mas_struct;

mas_struct* create_elem(int index, int string, int column);
mas_struct* add_end(mas_struct *head, mas_struct *elem);
double** create_matrix(int n, int m);
void read_num(int *num, char message[]);
void read_char(char *num, char message[]);
void matrix_from_normal_to_raz(int **JA, double **A, mas_struct **head, double **p, int n, int m, int not_0_el);
double** matrix_from_raz_to_normal(int **JA, double **A, mas_struct **head, int n, int m, int not_0_el);
void null_array(double *a, int n);
void copy_vector(double * v_values, int * v_index, double * v_res_values, int n, int n_res);
void multiple_sparse_matrix(double *A1, double *A2, mas_struct *I1, int num, int *J1, int *J2, int num2, double **ARES, int n, int m, int m1, int **JRES, mas_struct **IRES);
double** mult_matrix(double **matrix1, int num1, int m1, double **matrix2, int num2, int m2);
double **create_test_matrix(int n, int raz);
double **create_test_vector(int n);

void testing(void);

#endif /* testing_h */
