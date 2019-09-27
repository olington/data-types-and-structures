#ifndef sort_h
#define sort_h

#define SORT_1 1000
#define SORT_2 5000
#define SORT_3 10000

void sort(house_struct *houses, int rec_num);
void quick_sort(house_struct *houses, int first, int last);
void key_sort(key_table *key, int rec_num);
void key_quick_sort(key_table *key, int first, int last);
void inputTestTable(house_struct *houses, key_table *key, int *rec_num, int size);
void sorting_test();

#endif /* sort_h */
