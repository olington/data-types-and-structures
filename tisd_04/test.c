#include "test.h"
#include "stack_array.h"
#include "stack_list.h"

void printEfficiency(int count)
{
    list_t *list = NULL;
    char *string = calloc(MAX_STACK, sizeof(char));
    list_mem *list_del = NULL;
    int size1 = 0, size2 = 0, size_del = 0;
    srand((unsigned int)time(NULL));
    
    double tick1 = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++)
        listPush(&list, 'a', &size1);
    double tock1 = (double)clock() / CLOCKS_PER_SEC;
    double tick2 = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++)
    {
        arrayPush(&string, 'a', size2);
        size2++;
    }
    
    double tock2 = (double)clock() / CLOCKS_PER_SEC;
    
    printf("\n\nВремя %d 'push'\n", count);
    printf("1. Односвязный список: %f\n", tock1 - tick1);
    printf("2. Массив: %f\n", tock2 - tick2);
    
    tick1 = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++)
        listPop(&list, &list_del, &size1, &size_del);
    tock1 = (double)clock() / CLOCKS_PER_SEC;
    tick2 = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < count; i++)
    {
        arrayPop(&string, size2);
        size2--;
    }
    tock2 = (double)clock() / CLOCKS_PER_SEC;
    
    printf("\n\nВремя %d 'pop'\n", count);
    printf("1. Односвязный список: %f\n", tock1 - tick1);
    printf("2. Массив: %f\n", tock2 - tick2);
    
    printf("\nРазмер односвязного списка из %d элементов: %d\n", count, 5 * count);
    printf("Размер массива из %d элементов: %d\n", count, sizeof(char) * count);
    free(string);
}

void testing()
{
    printEfficiency(100);
    printEfficiency(500);
    printEfficiency(1000);
    printEfficiency(MAX_STACK);
    
}
