#include "struct.h"
#ifndef FUNC_H
#define FUNC_H

unsigned long long tick(void);
void efficient();
void add_to_file(int key, char* file_name, int* back);
void efficient_find();
void efficient_add();
void comparisons();
void random_fill_file(char* file_name, int len);
void list_fill_file(char* file_name, int len);
void comparison_hash_table(int len);

#endif /*EFFICIENCY_H*/
