#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "hash.h"
#include "struct.h"
#include "efficiency.h"
#include "tree.h"

#define LEN 1000
#define ITERATION 10
#define CPU_GHZ 1.7 

void add_to_file(int key, char* file_name, int* back)
{
	FILE* f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r+");
	int x;
	while(1)
	{
		if(feof(f))
			break;
		fscanf(f, "%d", &x);
		if (x == key)
		{
			*back = -1;
			fclose(f);
			return;
		}
	}
	fprintf(f, " %d", key);
	fclose(f);
}

void random_fill_file(char* file_name, int len)
{
	FILE* f = fopen(file_name, "w");
	fclose(f);
	srand(time(NULL));
	int code;
	int count = 0;
	int x;
	while(count < len)
	{
		code = 0;
		x = rand()%50000 - 25000;
		add_to_file(x, file_name, &code);
		if(!code)
			count += 1;
	}
}

void list_fill_file(char* file_name, int len)
{
	FILE*f = fopen(file_name, "w");
	for (int i = len; i>0; i--)
		fprintf(f, " %d", i);
	fclose(f);
}

void efficient_find()
{
	int x;
	node* head = NULL;
	node* head_b = NULL;
	node* cur;
	node* cur_b;
	int count = 0;
	int max = 0;
	int code;
    FILE* f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
	while(1)
	{
		if(feof(f))
			break;
		fscanf(f, "%d", &x);
		count += 1;
		if (fabs(x) > max)
			max = fabs(x);
		cur = create_item(x, 1);
		cur_b = create_item(x, 1);
		head = insert(head, cur, &code);
		head_b = insert_balance(head_b, cur_b, &code);
	}
	fclose(f);
	
	if (count > 0)
	{
		int len = 131072;											// len
		my_int* hash_table[len];
		my_int* elem;
		for (int i = 0; i < len; i++)
		{
			elem = malloc(sizeof(my_int));
			elem->flag = elem-> value = 0;
			hash_table[i] = elem;
		}
		f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
		while(1)
		{
			if(feof(f))
				break;
			fscanf(f, "%d", &x);
			add_to_hash_table(x, hash_table, len, &code);
		}
		fclose(f);
		printf("Время нахождения всех 1000 элементов\n");
		double a;
		unsigned long long tb, te, tall;
		tall = 0;
		f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
		while(1)
		{
			if(feof(f))
				break;
			fscanf(f, "%d", &x);
			tb = tick();
			find(head, x);
			te = tick();
			tall += te-tb;
		}
		fclose(f);
		a = tall;
		a = a / (CPU_GHZ * 1000000);
		printf("Двоичное дерево: %f ms\n", a);
		
		tall = 0;
		f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
		while(1)
		{
			if(feof(f))
				break;
			fscanf(f, "%d", &x);
			tb = tick();
			find(head_b, x);
			te = tick();
			tall += te - tb;
		}
		fclose(f);
		a = tall;
		a = a / (CPU_GHZ * 1000000);
		printf("Сбалансированное дерево: %f ms\n", a);
		
		tall = 0;
		f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
		while(1)
		{
			if(feof(f))
				break;
			fscanf(f, "%d", &x);
			tb = tick();
			find_in_table(hash_table, len, x);
			te = tick();
			tall += te - tb;
		}
		fclose(f);
		a = tall;
		a = a / (CPU_GHZ * 1000000);
		printf("Хеш-таблица: %f ms\n", a);
		
		free_hash_table(hash_table, len);
		free_tree(head);
		free_tree(head_b);
	}
}

void efficient_add()
{
	printf("Время добавления 1000 элементов\n");
	double a;
	unsigned long long tb, te, tall, tall2;
	FILE* f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "w");
	fclose(f);
	srand(time(NULL));
	int code;
	int count = 0;
	int x;

	tall = 0;
	while(count < 1000)
	{
		code = 0;
		x = rand()%50000 - 25000;
		tb = tick();
		add_to_file(x, "/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", &code);
		te = tick();
		tall += te - tb;
		if(!code)
			count += 1;
	}
	a = tall;
	a = a / (CPU_GHZ * 1000000);
	//printf("File (using file_add and reopening): %f ms\n", a);
	
	f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "w");
	fclose(f);
	
	int q;
	tall = 0;
	count = 0;
	f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r+");
	while(count < 1000)
	{
		code = 0;
		x = rand()%50000 - 25000;
		tb = tick();
		while(1)
		{
			if(feof(f))
				break;
			fscanf(f, "%d", &q);
			if (q == x)
			{
				code = 1;
				break;
			}
		}
		if (!code)
			fprintf(f, " %d", x);
		fseek(f, SEEK_SET, 0);
		te = tick();
		tall += te - tb;
		if(!code)
			count += 1;
	}
	a = tall;
	a = a / (CPU_GHZ * 1000000);
	printf("File: %f ms\n", a);
	fclose(f);
	
	count = 0;
	tall = tall2 = 0;
	node* head = NULL;
	node* head_b = NULL;
	node* cur;
	node* cur_b;
	int max = 0;
	while(count < 1000)
	{
		code = 0;
		x = rand()%50000 - 25000;
		cur = create_item(x, 1);
		cur_b = create_item(x, 1);
		tb = tick();
		head = insert(head, cur, &code);
		te = tick();
		tall += te - tb;
		tb = tick();
		head_b = insert_balance(head_b, cur_b, &code);
		te = tick();
		tall2 += te - tb;
		if(!code)
			count += 1;
		if (fabs(x) > max)
			max = fabs(x);
	}
	a = tall;
	a = a / (CPU_GHZ * 1000000);
	printf("Двоичное дерево: %f ms\n", a);
	a = tall2;
	a = a / (CPU_GHZ * 1000000);
	printf("Сбалансированное дерево: %f ms\n", a);
	
	if (count > 0)
	{
		int len = 131072;		        //len
		my_int* hash_table[len];
		my_int* elem;
		for (int i = 0; i < len; i++)
		{
			elem = malloc(sizeof(my_int));
			elem->flag = elem-> value = 0;
			hash_table[i] = elem;
		}
		f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
		tall = 0;
		while(1)
		{
			if(feof(f))
				break;
			fscanf(f, "%d", &x);
			tb = tick();
			add_to_hash_table(x, hash_table, len, &code);
			te = tick();
			tall += te - tb;
		}
		fclose(f);
		a = tall;
		a = a / (CPU_GHZ * 1000000);
		printf("Хеш-таблица: %f ms\n", a);
		
		free_hash_table(hash_table, len);
		free_tree(head);
		free_tree(head_b);
	}
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void comparisons()
{
	int x;
	node* head = NULL;
	node* head_b = NULL;
	node* cur;
	node* cur_b;
	int count = 0;
	int max = 0;
	int code;
    FILE* f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
	while(1)
	{
		if(feof(f))
			break;
		fscanf(f, "%d", &x);
		count += 1;
		if (fabs(x) > max)
			max = fabs(x);
		cur = create_item(x, 1);
		cur_b = create_item(x, 1);
		head = insert(head, cur, &code);
		head_b = insert_balance(head_b, cur_b, &code);
	}
	fclose(f);
	
	if (count > 0)
	{	
		printf("Среднее число сравнений\n");
		
		int comp = 0; 
		f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
		while(1)
		{
			if(feof(f))
				break;
			fscanf(f, "%d", &x);
			find_comp(head, x, &comp);
		}
		fclose(f);
		printf("Двоичное дерево: %f\n", (double)comp/1000);
		
		comp = 0;
		f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
		while(1)
		{
			if(feof(f))
				break;
			fscanf(f, "%d", &x);
			find_comp(head_b, x, &comp);
		}
		fclose(f);
		printf("Сбалансированное дерево: %f\n", (double)comp/1000);
		
		int znak = 1;
		int len = 512;
		while(znak == 1 && len <= 65536)
		{
			len *= 2;
			comparison_hash_table(len);
			printf("Нажмите 1, если хотите рестуктуризировать таблицу, иначе - любую другую цифру\n");
			znak = get_number();
		}
		if (len == 131072)
			printf("...");
		
		free_tree(head);
		free_tree(head_b);
	}
}

void comparison_hash_table(int len)
{
	int x;
	int code = 0;
	my_int* hash_table[len];
	my_int* elem;
	for (int i = 0; i < len; i++)
	{
		elem = malloc(sizeof(my_int));
		elem->flag = elem-> value = 0;
		hash_table[i] = elem;
	}
	FILE* f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
	while(1)
	{
		if(feof(f))
			break;
		fscanf(f, "%d", &x);
		add_to_hash_table(x, hash_table, len, &code);
	}
	fclose(f);
	int comp = 0;
	f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/a.txt", "r");
	while(1)
	{
		if(feof(f))
			break;
		fscanf(f, "%d", &x);
		find_in_table_comp(hash_table, len, x, &comp);
	}
	fclose(f);
	printf("Хеш-таблица: %f\n\n\n", (double)comp/1000);
	free_hash_table(hash_table, len);
}
