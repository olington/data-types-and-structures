#include "menu.h"

int menuWork(void) 
{
    printf("\n   Select an action:\n");
    printf("1. Multiply the matrix and column vector stored in this form to produce the result in the same form\n");
    printf("2. Multiplication using the standard algorithm\n");
    printf("3. Output matrix in standard format\n");
    printf("4. Output matrix in sparse format\n");
    printf("0. Back to menu\n");
    
    printf("\nOption: ");
    
    int choice;
    if (scanf("%d",&choice))
    {
        if (choice < 6 && choice >= 0)
        {
            fflush(stdin);
            return choice;
        }
        else
        {
            printf("\nError. Nonexistent option\n");
            fflush(stdin);
            return -1;
        }
    }
    else
    {
        fflush(stdin);
        printf("\nError. Nonexistent option\n");
        return -1;
    }
}
