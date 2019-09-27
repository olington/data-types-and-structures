#include "palindrome.h"

void palindrome(list_t *list, list_mem *list_del, int size, int size_del, char string[])
{
    if (size == 0)
        puts("Пустой стек\n");

    else
    {
        int i = 0, flag = 1, size1 = size;
        puts("Строка: ");
        printList(list, size);
        printf("\n");
        //printf("%d\n", size);
        //puts(string);
        char *word = calloc(size + 1, sizeof(char));
        while (size1)
        {
            word[size1 - 1] = arrayPop(&string, size1);
            size1--;
        }
        while (list)
        {
            char x = listPop(&list, &list_del, &size, &size_del);
            char y = word[i];
            if (x != y)
            {
                //printf("%c %c\n", x, y);
                flag = -1;
            }
            i++;
        }
        if (flag > 0)
            printf("Является палиндромом\n");

        else
            printf("Не является палиндромом\n");
        
    }
}
