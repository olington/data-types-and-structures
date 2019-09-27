#include "menu.h"

void print_menu()
{
    printf("\n\n\tМеню:\n");
    printf("1. Добавить число в двоичное дерево\n");
    printf("2. Добавить число в сбалансированное дерево\n");
    printf("3. Добавить число в хеш-таблицу\n");
    printf("4. Добавить число в файл\n");
    printf("5. Вывод хеш-таблицы\n\n");
    printf("6. Эффективность поиска\n");
    printf("7. Эффективность добавления\n");
    printf("8. Среднее число сравнений\n");
    //printf("9. Fill the file with random numbers\n");
    //printf("10. Fill the file like a list\n");
    printf("0. Выход\n");
    printf("Выберите пунт меню: \n");
}

void get_str(char *str)
{
    int code = 1;
    while(code)
    {
        gets(str);
        if (strcmp(str,""))
            code = 0;
        else
            printf("Пустой ввод\n Попробуйте снова\n");
    }
}

char get_char()
{
    char str[128];
    int code = 1;
    while(code)
    {
        gets(str);
        if (!strcmp(str,""))
            printf("Пустой ввод\n Попробуйте снова\n");
        else if (strlen(str) > 1)
            printf("Введите одно число\n");
        else
            code = 0;
    }
    return str[0];
}

int get_nature()
{
    int x = -1, code = 1;
    while(code || (x < 0))
    {
        code = scanf("%d", &x) - 1;
        fflush (stdin);
        if((code!=0) || (x<0))
            printf("Пустой ввод\n Попробуйте снова\n");
    }
    return x;
}

int get_number()
{
    int x = -1, code = 1;
    while(code)
    {
        code = scanf("%d", &x) - 1;
        fflush (stdin);
        if(code!=0)
            printf("Пустой ввод\n Попробуйте снова\n");
    }
    return x;
}

int get_menu_choice()
{
    int exit_code = -1;
    int z;
    do
    {
        z = get_nature();
        if (z < 0 || z > 10)
            printf("Несуществующий пункт\n");
        else
            exit_code = 0;
    }
    while(exit_code);
    return z;
}
