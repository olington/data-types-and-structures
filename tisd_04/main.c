#include <stdio.h>
#include "input.h"
#include "stack_array.h"
#include "stack_list.h"
#include "palindrome.h"
#include "test.h"

int main()
{
    int flag = 0, choice = 0, type = 0;
    list_t *list = NULL;
    list_mem *list_del = NULL;
    char *arr = calloc(MAX_STACK, sizeof(char));
    int size = 0, size_del = 0;
    char elem = 0;
    
    printf("Программа реализуюет операции добавления и удаления элементов из стека и отображения текущего состояния стека.\n\n");
    printf("Задание: используя стек, определить, является ли строка палиндромом.\n\n");
    
    printf("    Меню:\n");
    printf(" 1. Реализация массивом \n");
    printf(" 2. Реализация списком\n");
    
    printf("\nВыберите опцию: ");
    
    while (type < 1 || type > 2)
    {
        //puts("Несуществующая опция\n");
        readInt(&type);
    }
    
    while (flag == 0)
    {
        if (type == 1)
        {
            printf("\n");
            printf("    Меню:\n");
            printf(" 1. Показать стек \n");
            printf(" 2. Добавить эелемент\n");
            printf(" 3. Удалить элемент\n");
            printf(" 4. Палиндром\n");
            printf(" 5. Эффективность\n");
            printf(" 6. Выход\n");
            
            printf("\nВыберите опцию: ");
            
            while (choice < 1 || choice > 6)
            {
                //puts("Несуществующая опция\n");
                readInt(&choice);
            }
            
            switch (choice)
            {
                case 1:
                    printArray(arr, size);
                    choice = 0;
                    break;
                case 2:
                    printf("На вход подается один элемент типа char\n");
                    printf("Введите элемент: ");
                    readChar(&elem);
                    arrayPush(&arr, elem, size);
                    listPush(&list, elem, &size);
                    choice = 0;
                    break;
                case 3:
                    arrayPop(&arr, size);
                    listPop(&list, &list_del, &size, &size_del);
                    choice = 0;
                    break;
                case 4:
                    palindrome(list, list_del, size, size_del, arr);
                    flag = 1;
                    choice = 0;
                    break;
                case 5:
                    testing();
                    printf("\n");
                    printf("Вывод:\n");
                    printf("Стек-массив на 84 процента быстрее\n");
                    printf("Стек-массив занимает в 5 раз меньше памяти\n");
                    choice = 0;
                    break;
                case 6:
                    flag = 1;
                    choice = 0;
                    break;
                default:
                    break;
            }
        }
        
        if (type == 2)
        {
            printf("\n");
            printf("    Меню:\n");
            printf(" 1. Показать стек \n");
            printf(" 2. Добавить эелемент\n");
            printf(" 3. Удалить элемент\n");
            printf(" 4. Показать освобожденные адреса\n");
            printf(" 5. Показать текущее состояние стека с адресами\n");
            printf(" 6. Палиндром\n");
            printf(" 7. Эффективность\n");
            printf(" 8. Выход\n");

            printf("\nВыберите опцию: ");
            
            while (choice < 1 || choice > 8)
            {
                //puts("Несуществующая опция\n");
                readInt(&choice);
            }
            
            switch (choice)
            {
                case 1:
                    printList(list, size);
                    choice = 0;
                    break;
                case 2:
                    printf("На вход подается один элемент типа char\n");
                    printf("Введите элемент: ");
                    readChar(&elem);
                    arrayPush(&arr, elem, size);
                    listPush(&list, elem, &size);
                    choice = 0;
                    break;
                case 3:
                    arrayPop(&arr, size);
                    listPop(&list, &list_del, &size, &size_del);
                    choice = 0;
                    break;
                case 4:
                    printMemory(list_del, size_del);
                    choice = 0;
                    break;
                case 5:
                    printListWithMemory(list, size);
                    choice = 0;
                    break;
                case 6:
                    palindrome(list, list_del, size, size_del, arr);
                    flag = 1;
                    choice = 0;
                    break;
                case 7:
                    testing();
                    printf("\n");
                    printf("Вывод:\n");
                    printf("Стек-массив на 84 процента быстрее\n");
                    printf("Стек-массив занимает в 5 раз меньше памяти\n");
                    choice = 0;
                    break;
                case 8:
                    flag = 1;
                    choice = 0;
                    break;
                default:
                    break;
            }
        }
    }
    free(arr);
    return 0;
}
