#ifndef stack_array_h
#define stack_array_h

#include <stdio.h>

#define MAX_STACK 3

void arrayPush(char **string, char symb, const int size);
char arrayPop(char **string, int size);
void printArray(char *string, int size);

#endif /* stack_array_h */
