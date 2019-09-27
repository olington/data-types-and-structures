#ifndef Header_h
#define Header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define NO_ERROR 0          // ошибок нет
#define OPEN_ERROR -1       // ошибка открытия файла
#define EMPTY -2            // пустой файл
#define SYMBOL -3           // некорректный ввод
#define OUT_OF_RANGE -4     // выход за пределы чисел

#define CHAR_SIZE 32        // размер адресса
#define MAX_SIZE 50         // максимальный размер таблицы

typedef struct              // структура первичных квартир
{
    int repairs;            // ремонт: да/нет
} primary_house;

typedef struct              // структура вторичных квартир
{
    int year;               // год постройки дома
    int prev_owners;        // число предыдущих владельцев
    int prev_dwellers;      // число предыдущих жильцов
    int animals;            // животные: да/нет
} secondary_house;

typedef union                       // объединение
{
    primary_house primary;          // первичное жилье
    secondary_house secondary;      // вторичное жилье
} type;

typedef struct                      // структура квартир
{
    char adress[CHAR_SIZE];         // адресс
    int area;                       // общая площадь
    int rooms;                      // число комнат
    int price;                      // цена за квадратный метр
    int category;                   // категория: первичное/вторичное
    int index;                      // индекс
    type type;
} house_struct;

typedef struct                      // структура таблицы ключей
{
    int index;                      // индекс
    int area;                       // площадь
} key_table;

int checkFile(FILE *f);
int readChar(char *s, FILE *f, int len);
int readInt(int *n, FILE *f, int min_range, int max_range);
void recFromFile(house_struct *houses, key_table *key, int *rec_num, FILE *f, int size);
void recTable(house_struct *houses, key_table *key, int *rec_num);
void printTable (house_struct *houses, key_table *key, int *rec_num, int *flag_sort);
void printKeyTable (key_table *key, int *rec_num);
void findApartment(house_struct *houses, key_table *key, int rec_num);
void exitMenu();

#endif /* Header_h */
