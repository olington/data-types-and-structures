#include "stack_array.h"

void arrayPush(char **string, char symb, const int size)
{
    if (size < MAX_STACK)
        *(*string + size) = symb;
    
    else
        puts("Переполнение стека\n");
}

char arrayPop(char **string, int size)
{
    if (size != 0)
    {
        char p = *(*string + size - 1);
        *(*string + size - 1) = '\0';
        return p;
    }
    
    else
        puts("Пустой стек\n");
    return '\n';
}

void printArray(char *string, int size)
{
    if (size == 0)
        puts("Пустой стек\n");
    
    else
    {
        for (int i = size - 1; i >= 0; i--)
            printf("%c ", string[i]);
        
        printf("\n");
    }
}
