#include "multiplication.h"
#include "matr.h"

int* getColumn(int dim, int not_zero)
{
    int num;
    
    int *column = (int *)malloc(dim * sizeof(int));
    if (column != NULL)
    {
        printf("\nVector column: \n");
        for (int i = 0; i < not_zero; i++)
        {
            printf("\nEnter %d element: ",i);
            while(scanf("%d", &num) == 0)
            {
                printf("\nInput error\nEnter %d element: ",i);
                fflush(stdin);
            }
            column[i] = num;
        }
        return column;
    }
    
    else
        return NULL;
}

int multiplyMatrix(int **matr, int dim, int not_zero)
{
    int *column = getColumn(dim, not_zero);
    if (column != NULL)
    {
        int *result = (int *)calloc(dim, sizeof(int));
        if (result != NULL)
        {
            for (int i = 0; i < dim; i++)
                for (int j = 0;j < dim; j++)
                    result[i] = result[i] + column[j] * matr[j][i];
            
            printf("\nVector column: \n");
            
            for (int j = 0; j < dim; j++)
                printf("%d ", result[j]);
            
            printf("\n");
            free(result);
        }
        free(column);
        return 0;
    }
    else
        return 1;
}

int multiplySparseMatrix(int dim, int not_zero, int *A, int *IA, int *JA)
{
    int *column = getColumn(dim, not_zero);
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
                        if (JAS[z]!=JAS[z + 1])
                            AR[r] += AS[JAS[z]] * A[k];
                        
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
