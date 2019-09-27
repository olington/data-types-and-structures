#ifndef stack_list_h
#define stack_list_h

#include <stdio.h>
#include <stdlib.h>
#include "stack_array.h"

typedef struct stack_list
{
    char symb;
    struct stack_list *next;
}list_t;

typedef struct deleted_memory
{
    void *p;
    struct deleted_memory *next;
}list_mem;


void listPush(list_t** list, char elem, int *size);
void pushMemory(list_mem **list, void *p);
void printMemory(const list_mem *list, int size);
char listPop(list_t** list, list_mem **list_del, int *size, int *size_del);
void printListWithMemory(const list_t *list, int size);
void printList(const list_t *list, int size);
void printListBackwards(const list_t *list);

#endif /* stack_list_h */
