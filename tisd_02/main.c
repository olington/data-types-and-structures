#include "Header.h"
#include "sort.h"

int main()
{    
    int choice = 0;
    int rec_num = 0;
    int flag_sort = 0;
    house_struct *houses = (house_struct *)malloc(sizeof(house_struct) * MAX_SIZE);
    key_table *key = (key_table *)malloc(sizeof(key_table) * MAX_SIZE);
    while(1)
    {
        printf("    Main menu:\n");
        printf("1.  Add new record\n");
        printf("2.  Delete record\n");
        printf("3.  Show table\n");
        printf("4.  Show key table\n");
        printf("5.  Sort table\n");
        printf("6.  Sort table by key\n");
        printf("7.  Find apartments\n");
        printf("8.  Show sorting perfomance\n");
        printf("0.  Exit\n");
        
        printf("\nPress option: ");
        if (scanf("%i", &choice) == 0)
            choice = 9;
        
        switch(choice)
        {
            // добавить запись
            case 1:
                if (rec_num == MAX_SIZE)
                {
                    printf("Table overflow\n");
                    exitMenu();
                    break;
                }
                
                printf("\n");
                printf("   Choose adding way:\n");
                printf("1. Import from file\n");
                printf("2. Input manually\n");
                printf("0. Exit to main menu\n");
                
                printf("\nPress option: ");
                if (scanf("%i", &choice) == 0)
                    choice = 9;
                
                switch(choice)
                {
                    // добавить запись из файла
                    case 1:
                        printf("\nPay attention!\n");
                        printf("Before importing, make sure that file contains following things:\n\n");
                        printf(" - Adress: up to 30 symbols\n");
                        printf(" - Total area: int number in range [20;200]\n");
                        printf(" - Number of rooms: int number in range [1;6]\n");
                        printf(" - Cost for square meter: int number in range [10;500 000]\n");
                        printf(" - Category (1: primary; 2: secondary)\n");
                        printf("In case of primary apartment:\n");
                        printf(" - Repair availability: (1: yes; 0: no) \n");
                        printf("In case of secondary apartment:\n");
                        printf(" - Year of construction: int number in range [1950;2018]\n");
                        printf(" - Number of previous owners: int number in range [1;50]\n");
                        printf(" - Number of previous dwellers: int number in range [1;10]\n");
                        printf(" - If there lived animals: (1: yes; 0: no) \n\n");
                        
                        FILE *f = fopen("/Users/olga/Documents/tisd/tisd_02/tisd_02/in.txt", "r");
                        
                        if (checkFile(f) == NO_ERROR)
                        {
                            recFromFile(houses, key, &rec_num, f, MAX_SIZE);
                            printf("Total number of records: %i\n", rec_num);
                            fclose(f);
                        }
                        
                        exitMenu();
                        break;
                        
                    // добавить запись вручную
                    case 2:
                        recTable(houses, key, &rec_num);
                        exitMenu();
                        break;
                    
                    // вернуться в меню
                    case 0:
                        system("clear");
                        break;
                        
                    default:
                        printf("\nUnknown parameter\n");
                        exitMenu();
                        break;
                }
                break;
                
            // удалить запись
            case 2:
                if (rec_num == 0)
                {
                    printf("\nTable is empty\n");
                    exitMenu();
                    break;
                }
                
                int num, answ;
                
                printf("\nInput index of recording (int, range = [0..%i]): ", rec_num - 1);
                if ((scanf("%i", &num) == 0) || (num > rec_num - 1) || (num < 0))
                {
                    printf("Input error\n");
                    exitMenu();
                    break;
                }
                
                printf("Do you really want to delete apartment in '%s'? (1: yes; 0: no): ", houses[num].adress);
                if ((scanf("%i", &answ) == 0) || (answ > 1) || (answ < 0))
                {
                    printf("Input error\n");
                    exitMenu();
                    break;
                }
                
                if (answ == 0)
                {
                    system("clear");
                    break;
                }
                
                if (answ == 1)
                {
                    for (int i = num; i < rec_num - 1; ++i)
                        houses[i] = houses[i + 1];
                    
                    rec_num--;
                }
                
                exitMenu();
                break;
                
            // вывести таблицу
            case 3:
                printTable(houses, key, &rec_num, flag_sort);
                exitMenu();
                break;
            
            // вывести таблицу ключей
            case 4:
                printKeyTable(key, &rec_num);
                exitMenu();
                break;
             
            // сортировка 
            case 5:
                if (rec_num == 0)
                {
                    printf("\nTable is empty\n");
                    exitMenu();
                    break;
                }
                
                flag_sort = 1;
                quick_sort(houses, 0, rec_num - 1);
                exitMenu();
                break;
                
                
            // сортировка по ключу
            case 6:
                if (rec_num == 0)
                {
                    printf("\nTable is empty\n");
                    exitMenu();
                    break;
                }
                
                key_quick_sort(key, 0, rec_num - 1);
                exitMenu();
                break;
                
            // поиск квартир заданного параметра
            case 7:
                findApartment(houses, key, rec_num);
                exitMenu();
                break;
                
            // скорость и память различных видов сортировки
            case 8:
                sorting_test();
                exitMenu();
                break;
                
            // выход
            case 0:
                free(houses);
                free(key);
                exit(NO_ERROR);
                
            default:
                printf("\nUnknown parameter\n");
                exitMenu();
                break;
                
        }
    }
    return NO_ERROR;
}

