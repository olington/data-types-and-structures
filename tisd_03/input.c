#include "input.h"
#include "matr.h"

int** manualInput(int *dim, int *not_zero)
{
    int flag = 1;
    int num, x, y;
    
    printf("\nEnter the dimension of the matrix: ");
    
    while(flag == 1)
    {
        while(scanf("%d", dim) == 0)
        {
            printf("\nInput error\nEnter the dimension of the matrix: ");
            fflush(stdin);
        }

        if (*dim < 1)
            printf("\nIncorrect dimension\nEnter the dimension of the matrix: ");
        else
            flag = 0;
    }
    
    int **matr = (int**)calloc((*dim), sizeof(int*));
    if (matr != NULL)
    {
        int i = 0;
        for (; i < *dim; i++)
        {
            matr[i] = (int*)calloc((*dim), sizeof(int));
            if (matr[i] == NULL)
                freeMatrix(matr, *dim);
        }
    }
    
    flag = 1;
    
    printf("\nEnter the number of nonzero elements: ");
    
    while(flag == 1)
    {
        while(scanf("%d", not_zero) == 0)
        {
            printf("\nInput error\nEnter the number of nonzero elements: ");
            fflush(stdin);
        }
        if ((*not_zero < 0) || (*not_zero > (*dim * *dim)))
            printf("\nIncorrect input\nEnter the number of nonzero elements: ");
        else
            flag = 0;
    }
    for (int i = 0; i<*not_zero;i++)
    {
        flag = 1;
        printf("\nEnter string: ");
        while(flag == 1)
        {
            while(scanf("%d", &x) == 0)
            {
                printf("\nInput error\nEnter string: ");
                fflush(stdin);
            }
            if (x < 0 || x > *dim-1)
                printf("\nIncorrect input\nEnter string: ");
            else
                flag = 0;
        }
        flag = 1;
        printf("\nEnter column: ");
        while(flag == 1)
        {
            while(scanf("%d", &y) == 0)
            {
                printf("\nInput error\nEnter column: ");
                fflush(stdin);
            }
            if (y < 0 || y > *dim - 1)
                printf("\nIncorrect input\nEnter column: ");
            else
                flag = 0;
        }
        flag = 1;
        printf("\nEnter the number: ");
        while(scanf("%d", &num) == 0)
        {
            printf("\nInput error\nEnter the number: ");
            fflush(stdin);
        }
        matr[x][y] = num;
    }
    return matr;
}

int** fileInput(int *dim, int *not_zero)
{
    FILE *f = fopen("matrix.txt","r");
    int x, y, num;
    fscanf(f,"%d %d\n", dim, not_zero);
    int **matr = (int**)calloc((*dim), sizeof(int*));
    if (matr != NULL)
    {
        int i = 0;
        for (; i < *dim; i++)
        {
            matr[i] = (int*)calloc((*dim), sizeof(int));
            if (matr[i] == NULL)
            {
                freeMatrix(matr, *dim);
            }
        }
    }
    for (int i = 0; i < *not_zero; i++)
    {
        fscanf(f,"%d %d %d\n", &x, &y, &num);
        matr[x][y] = num;
    }
    fclose(f);
    return matr;
}

void efficient()
{
    FILE *f = fopen("eff.txt","r");
    char s[79];
    while(!feof(f))
    {
        fgets(s, 79, f);
        printf("%s",s);
    }
    fclose(f);
    printf("\n");
    printf("\nВывод: ");
    printf("\nИспользование разреженной матрицы выгодно при малом проценте заполнения и большой размерности матрицы");
    printf("\nВыигрыш по памяти: примерно при заполении 27%");
    printf("\nВыигрыш по времени: примерно до 29%\n");
    printf("\n");
}
