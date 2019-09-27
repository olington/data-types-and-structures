#include "testing.h"
#include "matr.h"
#include "multiplication.h"

int** testMatrix(int n, int raz)
{
    int **matrix = createMatrix(n, n);
    for (int i = 0; i < (int)((raz * n) / 100); i++)
        for (int j = 0; j < (int)((raz * n) / 100); j++)
            matrix[j][i] = -100 + rand() % 200;
    
    return matrix;
}

int** testVector(int n)
{
    int **vector = createMatrix(1, n);
    for (int i = 0; i < n; i++)
        vector[0][i] = i + 1;
    
    return vector;
}

int multiplyMatrixTest(int **matr, int dim)
{
    int *column = *testVector(dim);
    if (column != NULL)
    {
        int *result = (int *)calloc(dim, sizeof(int));
        if (result != NULL)
        {
            for (int i = 0; i < dim; i++)
                for (int j = 0;j < dim; j++)
                    result[i] = result[i] + column[j] * matr[j][i];
            
            printf("\n");
            free(result);
        }
        return 0;
    }
    else
        return 1;
}

int multiplySparseMatrixTest(int dim, int not_zero, int *A, int *IA, int *JA)
{
    int *column = *testVector(dim);
    int status = 0;
    int count_s = 0;
    
    for(int m = 0; m < dim; m++)
    {
        if(column[m] != 0)
            count_s++;
    }
    int* AS = (int *)malloc(count_s * sizeof(int));
    if (AS == NULL)
        status = 1;
    
    int * JAS = (int *)malloc((dim + 1)*sizeof(int));
    if (JAS == NULL)
        status = 1;
    
    if (status)
    {
        if (!JAS)
            free(JAS);
        if (!AS)
            free(AS);
        return status;
    }
    
    if (count_s != 0)
    {
        int flag = 0;
        int s = count_s - 1;
        JAS[dim] = count_s;
        
        for (int i = dim - 1; i >= 0; i--)
        {
            flag = 0;
            if (column[i] != 0)
            {
                AS[s] = column[i];
                JAS[i] = s;
                s--;
                flag = 1;
            }
            
            if (flag == 0)
                JAS[i] = JAS[i + 1];
        }
    }
    else
    {
        if (!JAS)
            free(JAS);
        if (!AS)
            free(AS);
        printf("\nThere are no nonzero elements in the vector column\n");
        return 0;
    }
    if (column != NULL)
    {
        int * AR = (int *)calloc(dim, sizeof(int));
        if (AR == NULL)
            status = 1;
        
        int * JAR = (int *)malloc((dim + 1) * sizeof(int));
        if (JAR == NULL)
            status = 1;
        JAR[dim] = dim - 1;
        if (JAR != NULL && AR != NULL)
        {
            int r = 0;
            int k = 0;
            int count_r = 0;
            for (int i = 0; i < dim; i++)
            {
                for(int z = 0, j = JA[i]; j <= JA[i + 1] - 1; z++)
                {
                    if (IA[k] == z)
                    {
                        if (JAS[z]!=JAS[z+1])
                        {
                            AR[r] += AS[JAS[z]] * A[k];
                        }
                        k++;
                        j++;
                    }
                }
                if (AR[r] != 0)
                {
                    count_r++;
                    JAR[i] = r;
                    r++;
                }
                else
                    JAR[i] = -1;
            }
            
            for (int i = dim - 1; i >= 0; i--)
                if(JAR[i] == -1)
                    JAR[i] = JAR[i + 1];
            
            printf("\nResult: \nА: ");
            for (int i = 0; i < count_r; i++)
                printf("%d ",AR[i]);
            printf("\nJA: ");
            for (int i = 0; i < dim + 1; i++)
                printf("%d ",JAR[i]);
            printf("\n");
        }
        if (!JAR)
            free(JAR);
        if (!AR)
            free(AR);
        free(column);
        return 0;
    }
    
    else
        return 1;
    if (!JAS)
        free(JAS);
    if (!AS)
        free(AS);
}

void testing()
{
    float t_0, t_1;
    srand((unsigned int)time(NULL));
    
    int **matrix11 = testMatrix(n1, m1);
    int **matrix12 = testMatrix(n1, m2);
    int **matrix13 = testMatrix(n1, m3);
    
    int **matrix21 = testMatrix(n2, m1);
    int **matrix22 = testMatrix(n2, m2);
    int **matrix23 = testMatrix(n2, m3);

    int **matrix31 = testMatrix(n3, m1);
    int **matrix32 = testMatrix(n3, m2);
    int **matrix33 = testMatrix(n3, m3);
    
    t_0 = (float)clock();
    multiplyMatrixTest(matrix11, n1);
    t_1 = (float)clock();
    float time_matrix11 = (t_1 - t_0) / CLOCKS_PER_SEC;
    t_0 = (float)clock();
    multiplyMatrixTest(matrix12, n1);
    t_1 = (float)clock();
    float time_matrix12 = (t_1 - t_0) / CLOCKS_PER_SEC;
    t_0 = (float)clock();
    multiplyMatrixTest(matrix13, n1);
    t_1 = (float)clock();
    float time_matrix13 = (t_1 - t_0) / CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiplyMatrixTest(matrix21, n2);
    t_1 = (float)clock();
    float time_matrix21 = (t_1 - t_0) / CLOCKS_PER_SEC;
    t_0 = (float)clock();
    multiplyMatrixTest(matrix22, n2);
    t_1 = (float)clock();
    float time_matrix22 = (t_1 - t_0) / CLOCKS_PER_SEC;
    t_0 = (float)clock();
    multiplyMatrixTest(matrix23, n2);
    t_1 = (float)clock();
    float time_matrix23 = (t_1 - t_0) / CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiplyMatrixTest(matrix31, n3);
    t_1 = (float)clock();
    float time_matrix31 = (t_1 - t_0) / CLOCKS_PER_SEC;
    t_0 = (float)clock();
    multiplyMatrixTest(matrix32, n3);
    t_1 = (float)clock();
    float time_matrix32 = (t_1 - t_0) / CLOCKS_PER_SEC;
    t_0 = (float)clock();
    multiplyMatrixTest(matrix33, n3);
    t_1 = (float)clock();
    float time_matrix33 = (t_1 - t_0) / CLOCKS_PER_SEC;
    

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
    
    int *A11 = (int *)malloc(((n1 * m1) / 100) * sizeof(int));
    int *A12 = (int *)malloc(((n1 * m2) / 100) * sizeof(int));
    int *A13 = (int *)malloc(((n1 * m3) / 100) * sizeof(int));
    int *A21 = (int *)malloc(((n2 * m1) / 100) * sizeof(int));
    int *A22 = (int *)malloc(((n2 * m2) / 100) * sizeof(int));
    int *A23 = (int *)malloc(((n2 * m3) / 100) * sizeof(int));
    int *A31 = (int *)malloc(((n3 * m1) / 100) * sizeof(int));
    int *A32 = (int *)malloc(((n3 * m2) / 100) * sizeof(int));
    int *A33 = (int *)malloc(((n3 * m3) / 100) * sizeof(int));
    
    int *IA11 = (int *)malloc(((n1 * m1) / 100) * sizeof(int));
    int *IA12 = (int *)malloc(((n1 * m2) / 100) * sizeof(int));
    int *IA13 = (int *)malloc(((n1 * m3) / 100) * sizeof(int));
    int *IA21 = (int *)malloc(((n2 * m1) / 100) * sizeof(int));
    int *IA22 = (int *)malloc(((n2 * m2) / 100) * sizeof(int));
    int *IA23 = (int *)malloc(((n2 * m3) / 100) * sizeof(int));
    int *IA31 = (int *)malloc(((n3 * m1) / 100) * sizeof(int));
    int *IA32 = (int *)malloc(((n3 * m2) / 100) * sizeof(int));
    int *IA33 = (int *)malloc(((n3 * m3) / 100) * sizeof(int));
    
    int *JA11 = (int *)malloc(((n1 * m1) / 100 + 1) * sizeof(int));
    int *JA12 = (int *)malloc(((n1 * m2) / 100 + 1) * sizeof(int));
    int *JA13 = (int *)malloc(((n1 * m3) / 100 + 1) * sizeof(int));
    int *JA21 = (int *)malloc(((n2 * m1) / 100 + 1) * sizeof(int));
    int *JA22 = (int *)malloc(((n2 * m2) / 100 + 1) * sizeof(int));
    int *JA23 = (int *)malloc(((n2 * m3) / 100 + 1) * sizeof(int));
    int *JA31 = (int *)malloc(((n3 * m1) / 100 + 1) * sizeof(int));
    int *JA32 = (int *)malloc(((n3 * m2) / 100 + 1) * sizeof(int));
    int *JA33 = (int *)malloc(((n3 * m3) / 100 + 1) * sizeof(int));
    
    convertIntoSparseMatrix(matrix11, n1, ((n1 * m1) / 100), A11, IA11, JA11);
    convertIntoSparseMatrix(matrix12, n1, ((n1 * m2) / 100), A12, IA12, JA12);
    convertIntoSparseMatrix(matrix13, n1, ((n1 * m3) / 100), A13, IA13, JA13);
    convertIntoSparseMatrix(matrix11, n2, ((n2 * m1) / 100), A21, IA21, JA21);
    convertIntoSparseMatrix(matrix11, n2, ((n2 * m2) / 100), A22, IA22, JA22);
    convertIntoSparseMatrix(matrix11, n2, ((n2 * m3) / 100), A23, IA23, JA23);
    convertIntoSparseMatrix(matrix11, n3, ((n2 * m1) / 100), A31, IA31, JA31);
    convertIntoSparseMatrix(matrix11, n3, ((n2 * m2) / 100), A32, IA32, JA32);
    convertIntoSparseMatrix(matrix11, n3, ((n2 * m3) / 100), A33, IA33, JA33);
    
    t_0 = (float)clock();
    multiplySparseMatrixTest(n1, ((n1 * m1) / 100), A11, IA11, JA11);
    t_1 = (float)clock();
    float time_matrix_raz_11 = (t_1 - t_0) / CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiplySparseMatrixTest(n1, ((n1 * m2) / 100), A12, IA12, JA12);
    t_1 = (float)clock();
    float time_matrix_raz_12 = (t_1 - t_0) / CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiplySparseMatrixTest(n1, ((n1 * m3) / 100), A13, IA13, JA13);
    t_1 = (float)clock();
    float time_matrix_raz_13 = (t_1 - t_0) / CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiplySparseMatrixTest(n2, ((n2 * m1) / 100), A21, IA21, JA21);
    t_1 = (float)clock();
    float time_matrix_raz_21 = (t_1 - t_0) / CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiplySparseMatrixTest(n2, ((n2 * m2) / 100), A22, IA22, JA22);
    t_1 = (float)clock();
    float time_matrix_raz_22 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiplySparseMatrixTest(n2, ((n2 * m3) / 100), A23, IA23, JA23);
    t_1 = (float)clock();
    float time_matrix_raz_23 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiplySparseMatrixTest(n3, ((n3 * m1) / 100), A31, IA31, JA31);
    t_1 = (float)clock();
    float time_matrix_raz_31 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiplySparseMatrixTest(n3, ((n3 * m2) / 100), A32, IA32, JA32);
    t_1 = (float)clock();
    float time_matrix_raz_32 = (t_1-t_0)/CLOCKS_PER_SEC;
    
    t_0 = (float)clock();
    multiplySparseMatrixTest(n3, ((n3 * m3) / 100), A33, IA33, JA33);
    t_1 = (float)clock();
    float time_matrix_raz_33 = (t_1-t_0)/CLOCKS_PER_SEC;
    

    long int size_matrix_raz_1 = 0;
    for (int i = 0; i < n1 * m3 / 100; i++)
    {
        size_matrix_raz_1 += sizeof(A13[i]);
        size_matrix_raz_1 += sizeof(IA13[i]);
        size_matrix_raz_1 += sizeof(JA13[i]);
    }
    
    long int size_matrix_raz_2 = 0;
    for (int i = 0; i < n2 * m3 / 100; i++)
    {
        size_matrix_raz_2 += sizeof(A23[i]);
        size_matrix_raz_2 += sizeof(IA23[i]);
        size_matrix_raz_2 += sizeof(JA23[i]);
    }
    
    long int size_matrix_raz_3 = 0;
    for (int i = 0; i < n3 * m3 / 100; i++)
    {
        size_matrix_raz_3 += sizeof(A33[i]);
        size_matrix_raz_3 += sizeof(IA33[i]);
        size_matrix_raz_3 += sizeof(JA33[i]);
    }
    
    printf("┌───────────────────────────┬────────────┬────────────┬────────────┐\n"
           "│        MATRIX SIZE        │ %10i │ %10i │ %10i │\n"
           "├───────────────────────────┼────────────┼────────────┼────────────┤\n", n1, n2, n3);
    printf("│%d%% OF FULLNESS(RAZ METHOD)│ %10.6f │ %10.6f │ %10.6f │\n", m1, time_matrix_raz_11, time_matrix_raz_21, time_matrix_raz_31);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│%d%% OF FULLNESS(RAZ METHOD)│ %10.6f │ %10.6f │ %10.6f │\n", m2, time_matrix_raz_12, time_matrix_raz_22, time_matrix_raz_32);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│%d%% OF FULLNESS(RAZ METHOD)│ %10.6f │ %10.6f │ %10.6f │\n", m3, time_matrix_raz_13, time_matrix_raz_23, time_matrix_raz_33);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ %d%% OF FULLNESS (ORDINARY)│ %10.6f │ %10.6f │ %10.6f │\n", m1, time_matrix11, time_matrix21, time_matrix31);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ %d%% OF FULLNESS (ORDINARY)│ %10.6f │ %10.6f │ %10.6f │\n", m2, time_matrix12, time_matrix22, time_matrix32);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ %d%% OF FULLNESS (ORDINARY)│ %10.6f │ %10.6f │ %10.6f │\n", m3, time_matrix13, time_matrix23, time_matrix33);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│ RAZ MATRIX MEMORY (BYTES) │ %10lu │ %10lu │ %10lu │\n", size_matrix_raz_1, size_matrix_raz_2, size_matrix_raz_3);
    printf("├───────────────────────────┼────────────┼────────────┼────────────┤\n"
           "│   MATRIX MEMORY (BYTES)   │ %10lu │ %10lu │ %10lu │\n", size_matrix1, size_matrix2, size_matrix3);
    printf("└───────────────────────────┴────────────┴────────────┴────────────┘\n");
    
    
    free(matrix11);
    free(matrix12);
    free(matrix13);
    free(matrix21);
    free(matrix22);
    free(matrix23);
    free(matrix31);
    free(matrix32);
    free(matrix33);
    free(A11);
    free(A12);
    free(A13);
    free(A21);
    free(A22);
    free(A23);
    free(A31);
    free(A32);
    free(A33);
    free(IA11);
    free(IA12);
    free(IA13);
    free(IA21);
    free(IA22);
    free(IA23);
    free(IA31);
    free(IA32);
    free(IA33);
    free(JA11);
    free(JA12);
    free(JA13);
    free(JA21);
    free(JA22);
    free(JA23);
    free(JA31);
    free(JA32);
    free(JA33);
}
