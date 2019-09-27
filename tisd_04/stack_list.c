#include "stack_list.h"

void listPush(list_t** list, char elem, int *size)
{
    if (MAX_STACK > *size)
    {
        list_t* node = malloc(sizeof(list_t));
        node->symb = elem;
        node->next = *list;
        (*size)++;
        *list = node;
    }
    
    else
        puts("Переполнение стека\n");
}

void pushMemory(list_mem **list, void *p)
{
    list_mem *node = malloc(sizeof(list_t));
    node->p = p;
    node->next = *list;
    *list = node;
}

void printMemory(const list_mem *list, int size)
{
    if (size == 0)
        puts("Нет освобожденной памяти\n");
    
    else
    {
        if (list)
        {
            printf("%p ", list->p);
            printMemory(list->next, size);
        }
        printf("\n");
    }
}

char listPop(list_t** list, list_mem **list_del, int *size, int *size_del)
{
    if (0 != *size)
    {
        list_t *temp = *list;
        pushMemory(list_del, &temp->symb);
        (*size_del)++;
        char data = temp->symb;
        *list = temp->next;
        (*size)--;
        free(temp);
        return data;
    }
    else
    {
        puts("Пустой стек\n");
        return '\0';
    }
}

void printListWithMemory(const list_t *list, int size)
{
    if (size == 0)
        puts("Пустой стек\n");
    
    else
    {
        if (list)
        {
            void *p = &(list->symb);
            printf("%6c %p\n", list->symb, p);
            printListWithMemory(list->next, size);
        }
    }
    printf("\n");
}


void printList(const list_t *list, int size)
{
    if (size == 0)
        puts("Пустой стек\n");
    
    else
    {
        if (list)
        {
            printf("%c ", list->symb);
            printList(list->next, size);
        }
    }
}

void printListBackwards(const list_t *list)
{
    if (list)
    {
        printListBackwards(list->next);
        printf("%c ", list->symb);
    }
    printf("\n");
}
