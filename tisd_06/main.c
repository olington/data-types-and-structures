#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "menu.h"
#include "hash.h"
#include "efficiency.h"
#include "struct.h"
#include "tree.h"

#define MAX_SIZE_TABLE 100000

/*
 В текстовом файле содержатся целые числа. Построить ДДП из чисел файла. Вывести его на экран в виде дерева. Сбалансировать полученное дерево и вывести его на экран. Построить хеш-таблицу из чисел файла. Использовать закрытое хеширование для устранения коллизий. Осуществить добавление введенного целого числа, если его там нет, в ДДП, в сбалансированное дерево, в хеш-таблицу и в файл. Сравнить время добавления, объем памяти и количество сравнений при использовании различных (4-х) структур данных. Если количество сравнений в хеш-таблице больше указанного, то произвести реструктуризацию таблицы, выбрав другую функцию.
 */

int main()
{
	int x;
	node* head = NULL;
	node* head_b = NULL;
	node* cur;
	node* cur_b;
	int count = 0;
	int max = 0;
	int code;
    FILE* f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/file.txt", "r");
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
		int len = 13;
		my_int* hash_table[len];
		my_int* elem;
		for (int i = 0; i < len; i++)
		{
			elem = malloc(sizeof(my_int));
			elem->flag = elem->value = 0;
			hash_table[i] = elem;
		}
		FILE* f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/file.txt", "r");
		while(1)
		{
			if(feof(f))
				break;
			fscanf(f, "%d", &x);
			add_to_hash_table(x, hash_table, len, &code);
		}
		fclose(f);
		
		f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/output.gv", "w");
		export_to_dot(f, head);
		fclose(f);

		f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/output_b.gv", "w");
		export_to_dot(f, head_b);
		fclose(f);
		
		int z = -1;
		do
		{
			code = 0;
			setbuf( stdout , NULL );
			print_menu();
			z = get_menu_choice();
			switch (z)
			{
				case 1:
					printf("Введите число: \n");
					x = get_number();
					cur = create_item(x, 1);
					head = insert(head, cur, &code);
					f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/output.gv", "w");
					export_to_dot(f, head);
					fclose(f);
					break;
				case 2:
					printf("Введите число: \n");
					x = get_number();
					cur_b = create_item(x, 1);
					head_b = insert_balance(head_b, cur_b, &code);
					f = fopen("/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/output_b.gv", "w");
					export_to_dot(f, head_b);
					fclose(f);
					break;
				case 3:
					printf("Введите число: \n");
					x = get_number();
					add_to_hash_table(x, hash_table, len, &code);
					break;
				case 4:
					printf("Введите число: \n");
					x = get_number();
					add_to_file(x, "/Users/olga/Documents/tisd/tisd_06_1/tisd_06_1/file.txt", &code);
					break;
				case 5:
					print_hash_table(hash_table, len);
					break;
				case 6:
					efficient_find();
					break;
				case 7:
					efficient_add();
					break;
				case 8:
					comparisons();
					break;
				case 9:
					random_fill_file("a.txt", 1000);
					break;
				case 10:
					list_fill_file("a.txt", 1000);
					break;
			}
			if (code)
				printf("Данное число уже есть в графе\n");
		}
		while (z != 0);
	
		free_hash_table(hash_table, len);
		free_tree(head);
		free_tree(head_b);
	}
	
    return 0;

}
