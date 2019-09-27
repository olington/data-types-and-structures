#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "math.h"
#include "struct.h"
#include "tree.h"

#define MAX_SIZE_TABLE 100000

int my_hash(int key, int len)
{
	return (int)fabs(key) % len;
}

void add_to_hash_table(int key, my_int** table, int len, int* back)
{
	int j = my_hash(key, len);
	add_to_ind(key, table, len, j, back);
}

void add_to_ind(int key, my_int** table, int len, int j, int* back)
{
	my_int* cur = table[j];
	if (cur->flag == 0)
	{
		cur->flag = 1;
		cur->value = key;
		table[j] = cur;
	}
	else if (cur->value == key)
	{
		*back = -1;
		return;
	}
	else
	{
		j += 1;
		if(j == len)
			j = 0;
		add_to_ind(key, table, len, j, back);
	}
}

void free_hash_table(my_int** table, int len)
{
	my_int* cur;
	for (int i = 0; i < len; i++)
	{
		cur = table[i];
		free(cur);
	}
}

void print_hash_table(my_int** table, int len)
{
	printf("Хеш-таблица:\n");
	my_int* cur;
	for (int i = 0; i < len; i++)
	{
		cur = table[i];
		printf("%d ", cur->value);
	}
}

my_int* find_in_table(my_int** table, int len, int key)
{
	int j = my_hash(key, len);
	my_int* cur = check_ind(table, len, key, j);
	return cur;
}

my_int* find_in_table_comp(my_int** table, int len, int key, int* comp)
{
	int j = my_hash(key, len);
	my_int* cur = check_ind_comp(table, len, key, j, comp);
	return cur;
}

my_int* check_ind(my_int** table, int len, int key, int j)
{
	my_int* cur = table[j];
	if (cur->flag == 0)
	{
		return cur;
	}
	else if (cur->value == key)
	{
		return cur;
	}
	else
	{
		j += 1;
		if (j == len)
			j = 0;
		cur = check_ind(table, len, key, j);
		return cur;
	}
}

my_int* check_ind_comp(my_int** table, int len, int key, int j, int* comp)
{
	my_int* cur = table[j];
	if (cur->flag == 0)
	{
		*comp += 1; 
		return cur;
	}
	else if (cur->value == key)
	{
		*comp += 1;
		return cur;
	}
	else
	{
		*comp += 1;
		j += 1;
		if (j == len)
			j = 0;
		cur = check_ind_comp(table, len, key, j, comp);
		return cur;
	}
}
