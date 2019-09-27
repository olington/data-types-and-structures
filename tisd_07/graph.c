#include "graph.h"

void free_matrix_rows(float **data, int n)
{
    for (int i = 0; i < n; i++)
        free(data[i]);
    
    free(data);
}

float **allocate_matrix_rows(int n)
{
    int m = n;
    float **data = calloc(n, sizeof(float*));
    if (!data)
    {
        return NULL;
    }
    
    for (int i = 0; i < n; i++)
    {
        data[i] = calloc(m, sizeof(float));
        if (!data[i])
        {
            free_matrix_rows(data, n);
            return NULL;
        }
    }
    
    return data;
}

matr *create_matr(unsigned int n)
{
    matr *res = malloc(sizeof(matr));
    if (!res)
    {
        return NULL;
    }
    res->data = allocate_matrix_rows(n);
    if (!res->data)
    {
        free(res);
        return NULL;
    }
    res->n = n;
    return res;
}

matr *read_matr(FILE *f)
{
    rewind(f);
    unsigned int n;
    if (fscanf(f, "%u", &n) != 1)
    {
        return NULL;
    }
    matr *res = create_matr(n);
    float tmp = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(f, "%f", &tmp) != 1)
            {
                return NULL;
            }
            res->data[i][j] = tmp;
        }
    }
    return res;
}

void print_matr(FILE *f, const matr *m)
{
    if (m != NULL)
    {
        for (int i = 0; i < m->n; i++)
        {
            for (int j = 0; j < m->n; j++)
            {
                fprintf(f, "%5.2f ", m->data[i][j]);
            }
            putc('\n', f);
        }
    }
    else
        fprintf(f, "It's empty!\n");
}

void free_matr(matr *matrix)
{
    if (matrix != NULL)
    {
        free_matrix_rows(matrix->data, matrix->n);
        free(matrix);
    }
}

matr *copy_matr(const matr *A)
{
    if (A != NULL)
    {
        matr *C = create_matr(A->n);
        
        C->n = A->n;
        C->n = A->n;
        for (int i = 0; i < A->n; ++i)
            for (int j = 0; j < A->n; ++j)
                C->data[i][j] = A->data[i][j];
        return C;
    }
    else
    {
        return NULL;
    }
}

matr *floyd_warshall(const matr *A)
{
    matr *res = copy_matr(A);
    for (int k = 0; k < A->n; k++)
    {
        for (int i = 0; i < A->n; i++)
        {
            for (int j = 0; j < A->n; j++)
                if (i != j)
                {
                    res->data[i][j] = fmin(res->data[i][j], res->data[i][k]+res->data[k][j]);
                }
                else
                    res->data[i][j] = 0.0;
        }
    }
    return res;
}

void show_matr_gv(const matr *a)
{
    if (a == NULL)
        return;
    FILE *f = fopen("/Users/olga/Documents/tisd/tisd_07/tisd_07/output.gv", "w");
    fprintf(f, "digraph My_graph {\n");
    for (int i = 0; i < a->n; i++)
        for (int j = 0; j < a->n; j++)
        {
            if (a->data[i][j] < INFINIT && a->data[i][j] != 0)
                fprintf(f, "%d -> %d [label=\"%.2f km\"];\n", i, j, a->data[i][j]);
        }
    fprintf(f, "}\n");
    fclose(f);
}

void show_best_gv(const matr *a, const matr *b)
{
    float T;
    printf("Введите минимальное расстояние: ");
    scanf("%f", &T);
    if (T < 0)
        printf("Некорректный ввод: отрицательная длина пути\n");
    if (a == NULL)
        return;
    FILE *f = fopen("/Users/olga/Documents/tisd/tisd_07/tisd_07/output_b.gv", "w");
    fprintf(f, "digraph My_graph {\n");
    for (int i = 0; i < a->n; i++)
    {
        for (int j = 0; j < a->n; j++)
        {
            if ((i == 0 || j == 0) && b->data[i][j] > T)
                fprintf(f, "%d -> %d [label=\"%.2f km\"];\n", i, j, b->data[i][j]);
        }
    }
    fprintf(f, "}\n");
    fclose(f);
}
