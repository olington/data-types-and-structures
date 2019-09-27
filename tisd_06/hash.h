#include "struct.h"
#ifndef HASH_H
#define HASH_H

int my_hash(int key, int len);
void add_to_hash_table(int key, my_int** table, int len, int* back);
void add_to_ind(int key, my_int** table, int len, int j, int* back);
void free_hash_table(my_int** table, int len);
void print_hash_table(my_int** table, int len);
my_int* find_in_table(my_int** table, int len, int key);
my_int* find_in_table_comp(my_int** table, int len, int key, int* comp);
my_int* check_ind(my_int** table, int len, int key, int j);
my_int* check_ind_comp(my_int** table, int len, int key, int j, int* comp);
#endif /*HASH_H*/
