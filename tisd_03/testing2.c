#include "testing.h"

void testing()
{
    float t_0, t_1;
    srand((unsigned int)time(NULL));
    
    double **matrix11 = create_test_matrix(n1, raz1);
    double **matrix12 = create_test_matrix(n1, raz2);
    double **matrix13 = create_test_matrix(n1, raz3);
    double **matrix21 = create_test_matrix(n2, raz1);
    double **matrix22 = create_test_matrix(n2, raz2);
    double **matrix23 = create_test_matrix(n2, raz3);
    double **matrix31 = create_test_matrix(n3, raz1);
    double **matrix32 = create_test_matrix(n3, raz2);
    double **matrix33 = create_test_matrix(n3, raz3);
    
    double **vector1 = create_test_vector(n1);
    double **vector2 = create_test_vector(n2);
    double **vector3 = create_test_vector(n3);
    
    t_0 = (float)clock();
    mult_matrix(vector1, 1, n1, matrix11, n1, n1);
    t_1 = (float)clock();
    float time_matrix11 = (t_1-t_0)/CLOCKS_PER_SEC;
    t_0 = (float)clock();
    mult_matrix(vector1, 1, n1, matrix12, n1, n1);
    t_1 = (float)clock();
    float time_matrix12 = (t_1-t_0)/CLOCKS_PER_SEC;
    t_0 = (float)clock();
    mult_matrix(vector1, 1, n1, matrix13, n1, n1);
    t_1 = (float)clock();
    float time_matrix13 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    mult_matrix(vector2, 1, n2, matrix21, n2, n2);
    t_1 = (float)clock();
    float time_matrix21 = (t_1-t_0)/CLOCKS_PER_SEC;
    t_0 = (float)clock();
    mult_matrix(vector2, 1, n2, matrix22, n2, n2);
    t_1 = (float)clock();
    float time_matrix22 = (t_1-t_0)/CLOCKS_PER_SEC;
    t_0 = (float)clock();
    mult_matrix(vector2, 1, n2, matrix23, n2, n2);
    t_1 = (float)clock();
    float time_matrix23 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    mult_matrix(vector3, 1, n3, matrix31, n3, n3);
    t_1 = (float)clock();
    float time_matrix31 = (t_1-t_0)/CLOCKS_PER_SEC;
    t_0 = (float)clock();
    mult_matrix(vector3, 1, n3, matrix32, n3, n3);
    t_1 = (float)clock();
    float time_matrix32 = (t_1-t_0)/CLOCKS_PER_SEC;
    t_0 = (float)clock();
    mult_matrix(vector3, 1, n3, matrix33, n3, n3);
    t_1 = (float)clock();
    float time_matrix33 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    long int size_matrix1 = 0;
    for (int i = 0; i < n1; i++)
    {
        size_matrix1 += sizeof(matrix11[i]);
        for (int j = 0; j < n1; j++)
            size_matrix1 += sizeof(matrix11[i][j]);
    }
    
    long int size_matrix2 = 0;
    for (int i = 0; i < n2; i++)
    {
        size_matrix2 += sizeof(matrix21[i]);
        for (int j = 0; j < n2; j++)
            size_matrix2 += sizeof(matrix21[i][j]);
    }
    
    long int size_matrix3 = 0;
    for (int i = 0; i < n3; i++)
    {
        size_matrix3 += sizeof(matrix31[i]);
        for (int j = 0; j < n3; j++)
            size_matrix3 += sizeof(matrix31[i][j]);
    }
    
    double *Amatrix11 = NULL, *Amatrix12 = NULL, *Amatrix13 = NULL, *Amatrix21 = NULL, *Amatrix22 = NULL, *Amatrix23 = NULL,\
    *Amatrix31 = NULL, *Amatrix32 = NULL, *Amatrix33 = NULL;
    int *Jmatrix11 = NULL, *Jmatrix12 = NULL, *Jmatrix13 = NULL, *Jmatrix21 = NULL, *Jmatrix22 = NULL, *Jmatrix23 = NULL, \
    *Jmatrix31 = NULL, *Jmatrix32 = NULL, *Jmatrix33 = NULL;
    mas_struct *head11 = NULL, *head12 = NULL, *head13 = NULL, *head21 = NULL, *head22 = NULL, *head23 = NULL, \
    *head31 = NULL, *head32 = NULL, *head33 = NULL;
    matrix_from_normal_to_raz(&Jmatrix11, &Amatrix11, &head11, matrix11, n1, n1, (n1*raz1/100)*(n1*raz1/100));
    matrix_from_normal_to_raz(&Jmatrix12, &Amatrix12, &head12, matrix12, n1, n1, (n1*raz2/100)*(n1*raz2/100));
    matrix_from_normal_to_raz(&Jmatrix13, &Amatrix13, &head13, matrix13, n1, n1, (n1*raz3/100)*(n1*raz3/100));
    
    matrix_from_normal_to_raz(&Jmatrix21, &Amatrix21, &head21, matrix21, n2, n2, (n2*raz1/100)*(n2*raz1/100));
    matrix_from_normal_to_raz(&Jmatrix22, &Amatrix22, &head22, matrix22, n2, n2, (n2*raz2/100)*(n2*raz2/100));
    matrix_from_normal_to_raz(&Jmatrix23, &Amatrix23, &head23, matrix23, n2, n2, (n2*raz3/100)*(n2*raz3/100));
    
    matrix_from_normal_to_raz(&Jmatrix31, &Amatrix31, &head31, matrix31, n3, n3, (n3*raz1/100)*(n3*raz1/100));
    matrix_from_normal_to_raz(&Jmatrix32, &Amatrix32, &head32, matrix32, n3, n3, (n3*raz2/100)*(n3*raz2/100));
    matrix_from_normal_to_raz(&Jmatrix33, &Amatrix33, &head33, matrix33, n3, n3, (n3*raz3/100)*(n3*raz3/100));
    
    double *Avector1 = NULL, *Avector2 = NULL, *Avector3 = NULL;
    int *Jvector1 = NULL, *Jvector2 = NULL, *Jvector3 = NULL;
    mas_struct *head1 = NULL, *head2 = NULL, *head3 = NULL;
    matrix_from_normal_to_raz(&Jvector1, &Avector1, &head1, vector1, 1, n1, n1);
    matrix_from_normal_to_raz(&Jvector2, &Avector2, &head2, vector2, 1, n2, n2);
    matrix_from_normal_to_raz(&Jvector3, &Avector3, &head3, vector3, 1, n3, n3);
    
    double *ARES = NULL;
    int *JRES = NULL;
    mas_struct *head_res = NULL;
    t_0 = (float)clock();
    multiple_sparse_matrix(Amatrix11, Avector1, head11, (n1*raz1/100)*(n1*raz1/100), Jmatrix11, Jvector1, n1, &ARES, n1, n1, n1, &JRES, &head_res);
    t_1 = (float)clock();
    float time_matrix_raz_11 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiple_sparse_matrix(Amatrix12, Avector1, head12, (n1*raz2/100)*(n1*raz2/100), Jmatrix12, Jvector1, n1, &ARES, n1, n1, n1, &JRES, &head_res);
    t_1 = (float)clock();
    float time_matrix_raz_12 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiple_sparse_matrix(Amatrix13, Avector1, head13, (n1*raz3/100)*(n1*raz3/100), Jmatrix13, Jvector1, n1, &ARES, n1, n1, n1, &JRES, &head_res);
    t_1 = (float)clock();
    float time_matrix_raz_13 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiple_sparse_matrix(Amatrix21, Avector2, head21, (n2*raz1/100)*(n2*raz1/100), Jmatrix21, Jvector2, n2, &ARES, n2, n2, n2, &JRES, &head_res);
    t_1 = (float)clock();
    float time_matrix_raz_21 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiple_sparse_matrix(Amatrix22, Avector2, head22, (n2*raz2/100)*(n2*raz2/100), Jmatrix22, Jvector2, n2, &ARES, n2, n2, n2, &JRES, &head_res);
    t_1 = (float)clock();
    float time_matrix_raz_22 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiple_sparse_matrix(Amatrix23, Avector2, head23, (n2*raz3/100)*(n2*raz3/100), Jmatrix23, Jvector2, n2, &ARES, n2, n2, n2, &JRES, &head_res);
    t_1 = (float)clock();
    float time_matrix_raz_23 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiple_sparse_matrix(Amatrix31, Avector3, head31, (n3*raz1/100)*(n3*raz1/100), Jmatrix31, Jvector3, n3, &ARES, n3, n3, n3, &JRES, &head_res);
    t_1 = (float)clock();
    float time_matrix_raz_31 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiple_sparse_matrix(Amatrix32, Avector3, head32, (n3*raz2/100)*(n3*raz2/100), Jmatrix32, Jvector3, n3, &ARES, n3, n3, n3, &JRES, &head_res);
    t_1 = (float)clock();
    float time_matrix_raz_32 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiple_sparse_matrix(Amatrix33, Avector3, head33, (n3*raz3/100)*(n3*raz3/100), Jmatrix33, Jvector3, n1, &ARES, n3, n3, n3, &JRES, &head_res);
    t_1 = (float)clock();
    float time_matrix_raz_33 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    //    memory_raz
    long int size_matrix_raz_1 = 0;
    for (int i = 0; i < n1*raz3/100; i++)
    {
        size_matrix_raz_1 += sizeof(Amatrix13[i]);
        size_matrix_raz_1 += sizeof(Jmatrix13[i]);
    }
    for (mas_struct *cur = head13; cur; cur = cur->next)
        size_matrix_raz_1 += sizeof(mas_struct);
    
    long int size_matrix_raz_2 = 0;
    for (int i = 0; i < n2*raz3/100; i++)
    {
        size_matrix_raz_2 += sizeof(Amatrix23[i]);
        size_matrix_raz_2 += sizeof(Jmatrix23[i]);
    }
    for (mas_struct *cur = head23; cur; cur = cur->next)
        size_matrix_raz_2 += sizeof(mas_struct);
    
    long int size_matrix_raz_3 = 0;
    for (int i = 0; i < n3*raz3/100; i++)
    {
        size_matrix_raz_3 += sizeof(Amatrix33[i]);
        size_matrix_raz_3 += sizeof(Jmatrix33[i]);
    }
    for (mas_struct *cur = head33; cur; cur = cur->next)
        size_matrix_raz_3 += sizeof(mas_struct);
    
    printf("┌───────────────────────────┬────────────┬────────────┬────────────┐\n"
           "│        Matrix size        │ %10i │ %10i │ %10i │\n"
           "├───────────────────────────┼────────────┼────────────┼────────────┤\n", n1, n2, n3);
    printf("│ %d%% sparse matrix         │ %10.6f │ %10.6f │ %10.6f │\n", raz1, time_matrix_raz_11, time_matrix_raz_21, time_matrix_raz_31);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ %d%% sparse matrix         │ %10.6f │ %10.6f │ %10.6f │\n", raz2, time_matrix_raz_12, time_matrix_raz_22, time_matrix_raz_32);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ %d%% sparse matrix         │ %10.6f │ %10.6f │ %10.6f │\n", raz3, time_matrix_raz_13, time_matrix_raz_23, time_matrix_raz_33);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ %d%% standart matrix       │ %10.6f │ %10.6f │ %10.6f │\n", raz1, time_matrix11, time_matrix21, time_matrix31);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ %d%% standart matrix       │ %10.6f │ %10.6f │ %10.6f │\n", raz2, time_matrix12, time_matrix22, time_matrix32);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ %d%% standart matrix       │ %10.6f │ %10.6f │ %10.6f │\n", raz3, time_matrix13, time_matrix23, time_matrix33);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ Sparse matrix memory      │ %10lu │ %10lu │ %10lu │\n", size_matrix_raz_1, size_matrix_raz_2, size_matrix_raz_3);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ Standart matrix memory    │ %10lu │ %10lu │ %10lu │\n", size_matrix1, size_matrix2, size_matrix3);
    printf("└───────────────────────────┴────────────┴────────────┴────────────┘\n");
    printf("\n");
    
    
    free(matrix11);
    free(matrix12);
    free(matrix13);
    free(matrix21);
    free(matrix22);
    free(matrix23);
    free(matrix31);
    free(matrix32);
    free(matrix33);
    free(vector1);
    free(vector2);
    free(vector3);
    free(ARES);
    free(JRES);
    free(Amatrix11);
    free(Amatrix12);
    free(Amatrix13);
    free(Amatrix21);
    free(Amatrix22);
    free(Amatrix23);
    free(Amatrix31);
    free(Amatrix32);
    free(Amatrix33);
    free(Jmatrix11);
    free(Jmatrix12);
    free(Jmatrix13);
    free(Jmatrix21);
    free(Jmatrix22);
    free(Jmatrix23);
    free(Jmatrix31);
    free(Jmatrix32);
    free(Jmatrix33);
}

mas_struct* create_elem(int index, int string, int column)
{
    mas_struct *elem = malloc(sizeof(mas_struct));
    
    if (elem)
    {
        elem->index = index;
        elem->string = string;
        elem->column = column;
        elem->next = NULL;
    }
    
    return elem;
}

mas_struct* add_end(mas_struct *head, mas_struct *elem)
{
    mas_struct *cur = head;
    
    if (!head)
        return elem;
    for ( ; cur->next; cur = cur->next);
    cur->next = elem;
    
    return head;
}

double** create_matrix(int n, int m)
{
    double **pa = malloc(n*sizeof(double*)+n*m*sizeof(double));
    if (pa)
    {
        for (int i = 0; i<n; i++)
            pa[i] = (double*)((char*)pa + n*sizeof(double*) + i*m*sizeof(double));
        
        for (int i = 0; i < n; i++)
            for (int k = 0; k < m; k++)
                pa[i][k] = 0;
    }
    return pa;
}

void read_num(int *num, char message[])
{
    int rc;
    char tmp;
    printf("%s", message);
    while(((rc = scanf("%d%c", num, &tmp)) != 2 && rc != EOF) || tmp != '\n')
    {
        printf("Input error.  %s", message);
        do
            rc = scanf("%c", &tmp);
        while(rc != EOF && tmp != '\n');
    }
}

void read_char(char *num, char message[])
{
    int rc;
    char tmp;
    printf("%s", message);
    while(((rc = scanf("%c%c", num, &tmp)) != 2 && rc != EOF) || tmp != '\n')
    {
        printf("Input error.  %s", message);
        do
            rc = scanf("%c", &tmp);
        while(rc != EOF && tmp != '\n');
    }
}

void matrix_from_normal_to_raz(int **JA, double **A, mas_struct **head, double **p, int n, int m, int not_0_el)
{
    *A = malloc(not_0_el*sizeof(double));
    *JA = malloc(not_0_el*sizeof(int));
    int num = 0;
    bool first_el;
    *head = NULL;
    for (int i = 0; i < n; i++)
    {
        first_el = 1;
        for (int j = 0; j < m; j++)
            if (p[i][j])
            {
                (*A)[num] = p[i][j];
                (*JA)[num] = j;
                if (first_el)
                {
                    mas_struct *new_elem = create_elem(num, i, j);
                    *head = add_end(*head, new_elem);
                }
                first_el = 0;
                num++;
            }
    }
}

double** matrix_from_raz_to_normal(int **JA, double **A, mas_struct **head, int n, int m, int not_0_el)
{
    double **normal_matrix = create_matrix(n, m);
    mas_struct *cur = *head;
    int num  = 0;
    bool flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (cur)
        {
            for (int j = 0; j < m; j++)
            {
                if (cur->column == j && (*JA)[cur->index] == j)
                {
                    flag = 1;
                    normal_matrix[i][j] = (*A)[num++];
                }
                else if (flag && (*JA)[num] == j)
                    normal_matrix[i][j] = (*A)[num++];
                else
                    normal_matrix[i][j] = 0;
            }
            cur = cur->next;
            flag = 0 ;
        }
        else
            for (int k = 0; k < m; k++)
                normal_matrix[i][k] = 0;
    }
    return normal_matrix;
}

void null_array(double *a, int n)
{
    for(int i = 0; i < n; i++)
        a[i] = 0;
}

void copy_vector(double * v_values, int * v_index, double * v_res_values, int n, int n_res)
{
    null_array(v_res_values, n_res);
    for(int i = 0; i < n; i++)
        v_res_values[v_index[i]] = v_values[i];
}

void multiple_sparse_matrix(double *A1, double *A2, mas_struct *I1, int num, int *J1, int *J2, int num2, double **ARES, int n, int m, int m1, int **JRES, mas_struct **IRES)
{
    mas_struct *cur = I1;
    int string = 0, column = 0;
    *ARES = (double *)malloc(m * sizeof(double));
    *JRES = (int *)malloc(m * sizeof(int));
    null_array(*ARES, m);
    
    double *vector = (double *)malloc(m1 * sizeof(double));
    copy_vector(A2, J2, vector, num2, n);
    
    for(int i = 0; i < num; i++)
    {
        column = 0;
        for(cur = I1; cur && cur->index <= i; cur = cur->next)
            string = cur->string;
        
        (*ARES)[J1[i]] += A1[i] * vector[string];
    }
    num = 0;
    for (int i = 0; i < m; i++)
        if ((*ARES)[i])
        {
            if (!num)
            {
                mas_struct *new_elem = create_elem(i, 0, 0);
                *IRES = add_end(*IRES, new_elem);
            }
            (*JRES)[num++] = i;
        }
}

double** mult_matrix(double **matrix1, int num1, int m1, double **matrix2, int num2, int m2)
{
    double **result = NULL;
    if (m1 == num2)
    {
        result = create_matrix(num1, m2);
        for (int i = 0; i < num1; i++)
            for (int k = 0; k < m2; k++)
                for (int j = 0; j < m1; j++)
                    result[i][k] += matrix1[i][j] * matrix2[j][k];
    }
    return result;
}

double **create_test_matrix(int n, int raz)
{
    double **matrix = create_matrix(n, n);
    for (int i = 0; i < (int)((raz*n)/100); i++)
        for (int j = 0; j < (int)((raz*n)/100); j++)
            matrix[j][i] = -1000 + (rand() % 2000);
    
    return matrix;
}

double **create_test_vector(int n)
{
    double **vector = create_matrix(1, n);
    for (int i = 0; i < n; i++)
        vector[0][i] = i+1;
    
    return vector;
}
