#include "input.h"

void readChar(char *num)
{
    int rc;
    char tmp;
    
    while(((rc = scanf("%c%c", num, &tmp)) != 2 && rc != EOF) || tmp != '\n')
    {
        printf("Ошибка ввода, введите элемент: ");
        do
            rc = scanf("%c", &tmp);
        while(rc != EOF && tmp != '\n');
    }
}

void readInt(int *num)
{
    int rc;
    char tmp;
    
    while(((rc = scanf("%d%c", num, &tmp)) != 2 && rc != EOF) || tmp != '\n')
    {
        printf("Ошибка ввода, пожалуйста, введите число: ");
        
        do
            rc = scanf("%c", &tmp);
        while(rc != EOF && tmp != '\n');
    }
}
