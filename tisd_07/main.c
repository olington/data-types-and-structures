#include "interface.h"
#include "graph.h"


/*Задача 12
 Задана система двусторонних дорог.
 Найти множество городов, расстояние от которых до выделенного города (столицы) больше, чем Т. */


int main(void)
{
    FILE *fin = fopen("/Users/olga/Documents/tisd/tisd_07/tisd_07/input.txt", "r");
    
    int menu = 0;
    int flag = 1;
    matr *graph = read_matr(fin);
    matr *best = NULL;
    double a;
    unsigned long long tb, te, tall;
    do
    {
        puts("\n\tМеню:");
        puts("1. Построить граф");
        puts("2. Найти пути до столицы");
        puts("3. Вывести матрицу дорог");
        puts("0. Выход");
        menu = menu_value();
        switch(menu)
        {
            case 1:
                show_matr_gv(graph);
                break;
            case 2:
                free_matr(best);
                show_best_gv(best, graph);
                tb = tick();
                best = floyd_warshall(graph);
                te = tick();
                tall = te - tb;
                a = tall;
                a = a / CLOCKS_PER_SEC;
                printf("Время выполнения: %f sec\n", a);
                break;
            case 3:
                print_matr(stdout, graph);
                break;
            //case 4:
                //print_matr(stdout, best);
                //show_best_gv(best, graph);
                //break;
            case 0:
                flag = 0;
                break;
            default:
                puts("Неизвестная команда");
                break;
        }
    } while (flag);
    
    free_matr(graph);
    free_matr(best);
    fclose(fin);
    return 0;
}
