#include "menu.h"

void exitMenu()
{
    printf("Нажмите enter, чтобы продолжить: ");
    while (getchar() != '\n');
    getchar();
    system("clear");
}
