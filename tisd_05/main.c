#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "array.h"
#include "process.h"
#include "time.h"
#include "display.h"

int main()
{
    srand(time(NULL));
    int n = 1000;
    int interval = 100;
    interval_time t1 = {1, 5};
    interval_time t2 = {0, 9};
    interval_time t3 = {0, 4};
    interval_time t4 = {0, 8};
    
    int flag;
    int choice = 0;
    while(choice != 3)
    {
        printf("\nВыберите одно из следующих действий:\n\n");
        printf("1. Моделирование для очереди на массиве\n");
        printf("2. Моделирование для очереди на списке\n");
        printf("3. Выход\n\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        fflush (stdin);
        switch(choice)
        {
            case 1:
                workArray(n, interval, t1, t2, t3, t4, 0);
                break;
            case 2:
                printf("Вывести информацию о памяти? 1 - да, 0 - нет\n");
                printf("Выбор: ");
                scanf("%d", &flag);
                fflush (stdin);
                if(flag != 1)
                    flag = 0;
                workList(n, interval, t1, t2, t3, t4, flag);
                break;
            case 3:
                break;
            default:
                printf("Несуществующая команда\n");
                break;
        }
    }
    return 0;
}
