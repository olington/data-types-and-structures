#include "Header.h"

// функция проверяет наличие файла
int checkFile(FILE *f)
{
    if (!f)
    {
        printf("Opening file error\n");
        return OPEN_ERROR;
    }
    
    if (fgetc(f) == EOF)
    {
        printf("Empty file\n");
        fclose(f);
        return EMPTY;
    }
    
    rewind(f);
    return NO_ERROR;
}

// функция считывает char
int readChar(char *s, FILE *f, int len)
{
    int ch, i = 0;
    ch = fgetc(f);
    if (ch == '\n')
        return EMPTY;
    
    while (1)
    {
        if (i > len)
            return OUT_OF_RANGE;
        
        if (ch == EOF)
            return ch;
        
        if (ch == '\n')
        {
            s[i] = '\0';
            return NO_ERROR;
        }
        
        s[i++] = ch;
        ch = fgetc(f);
    }
    return NO_ERROR;
}

// функция считывает int
int readInt(int *n, FILE *f, int min_range, int max_range)
{
    char *num;
    int ch, i = 0;
    num = calloc(50, sizeof(*num));
    ch = fgetc(f);
    if (ch == '\n')
        return EMPTY;
    
    while (1)
    {
        
        if (ch == EOF)
            return ch;
        
        if (ch == '\n')
        {
            num[i] = '\0';
            break;
        }
        
        if ((ch > 57) || (ch < 48))
            return SYMBOL;
        
        else
            num[i++] = ch;
        
        ch = fgetc(f);
    }
    
    ch = atoi(num);
    free(num);
    
    if ((ch > max_range) || (ch < min_range))
        return OUT_OF_RANGE;
    
    *n = ch;
    return NO_ERROR;
}

// функция добавляет запись из файла
void recFromFile(house_struct *houses, key_table *key, int *rec_num, FILE *f, int size)
{
    int cur_rec = 0;
    char *entry;
    entry = calloc(31, sizeof(*entry));
    
    int number, status;
    
    while (1)
    {
        if (*rec_num == size)
        {
            printf("Table overflow\n");
            break;
        }
        
        // адресс
        status = readChar(entry, f, CHAR_SIZE);
        
        if (status == EOF)
            break;
        
        else if (status == OUT_OF_RANGE)
        {
            printf("Record #%i is out of range!\n", cur_rec);
            break;
        }
        
        else if (status == EMPTY)
        {
            printf("Record #%i adress is empty\n", cur_rec);
            break;
        }
        
        else if (status == NO_ERROR)
            strcpy(houses[*rec_num].adress, entry);
        
        // общая площадь
        status = readInt(&number, f, 20, 200);
        
        if (status == EOF)
            break;
        
        else if (status == OUT_OF_RANGE)
        {
            printf("Record #%i: total area is out of range\n", cur_rec);
            break;
        }
        
        else if (status == SYMBOL)
        {
            printf("Record #%i: total area contains wrong symbol (input int number)\n", cur_rec);
            break;
        }
        
        else if (status == EMPTY)
        {
            printf("Record #%i: total area is empty\n", cur_rec);
            break;
        }
        
        else if (status == NO_ERROR)
        {
            houses[*rec_num].area = number;
            key[*rec_num].area = houses[*rec_num].area;
        }
        
        // количество комнат
        status = readInt(&number, f, 1, 6);
        
        if (status == EOF)
            break;
        
        else if (status == OUT_OF_RANGE)
        {
            printf("Record #%i: number of rooms is out of range\n", cur_rec);
            break;
        }
        
        else if (status == SYMBOL)
        {
            printf("Record #%i: number of rooms contains wrong symbol (input int number)\n", cur_rec);
            break;
        }
        
        else if (status == EMPTY)
        {
            printf("Record #%i: number of rooms is empty\n", cur_rec);
            break;
        }
        
        else if (status == NO_ERROR)
            houses[*rec_num].rooms = number;
        
        // стоимость одного квадратного метра
        status = readInt(&number, f, 10, 500000);
        
        if (status == EOF)
            break;
        
        else if (status == OUT_OF_RANGE)
        {
            printf("Record #%i: cost for square meter is out of range\n", cur_rec);
            break;
        }
        
        else if (status == SYMBOL)
        {
            printf("Record #%i: cost for square meter contains wrong symbol (input int number)\n", cur_rec);
            break;
        }
        
        else if (status == EMPTY)
        {
            printf("Record #%i: cost for square meter is empty\n", cur_rec);
            break;
        }
        
        else if (status == NO_ERROR)
            houses[*rec_num].price = number;
        
        // первичное или вторичное
        status = readInt(&number, f, 1, 2);
        
        if (status == EOF)
            break;
        
        else if (status == OUT_OF_RANGE)
        {
            printf("Record #%i: type is out of range\n", cur_rec);
            break;
        }
        
        else if (status == SYMBOL)
        {
            printf("Record #%i: type contains wrong symbol (input int number)\n", cur_rec);
            break;
        }
        
        else if (status == EMPTY)
        {
            printf("Record #%i: typer is empty\n", cur_rec);
            break;
        }
        
        else if (status == NO_ERROR)
            houses[*rec_num].category = number;
        
        if (houses[*rec_num].category == 1)
        {
            // первичное
            status = readInt(&number, f, 0, 1);
            
            if (status == EOF)
                break;
            
            else if (status == OUT_OF_RANGE)
            {
                printf("Record #%i: repairs is out of range\n", cur_rec);
                break;
            }
            
            else if (status == SYMBOL)
            {
                printf("Record #%i: repairs contains wrong symbol (input int number)\n", cur_rec);
                break;
            }
            
            else if (status == EMPTY)
            {
                printf("Record #%i: repairs is empty\n", cur_rec);
                break;
            }
            
            else if (status == NO_ERROR)
                houses[*rec_num].type.primary.repairs = number;
        }
        
        // вторичное
        else if (houses[*rec_num].category == 2)
        {
            // год постройки
            status = readInt(&number, f, 1950, 2018);
            
            if (status == EOF)
                break;
            
            else if (status == OUT_OF_RANGE)
            {
                printf("Record #%i: year of construction is out of range\n", cur_rec);
                break;
            }
            
            else if (status == SYMBOL)
            {
                printf("Record #%i: year of construction contains wrong symbol (input int number)\n", cur_rec);
                break;
            }
            
            else if (status == EMPTY)
            {
                printf("Record #%i: year of construction is empty\n", cur_rec);
                break;
            }
            
            else if (status == NO_ERROR)
                houses[*rec_num].type.secondary.year = number;
            
            // кол-во предыдущих владельцев
            status = readInt(&number, f, 1, 50);
            
            if (status == EOF)
                break;
            
            else if (status == OUT_OF_RANGE)
            {
                printf("Record #%i: number of previous owners is out of range\n", cur_rec);
                break;
            }
            
            else if (status == SYMBOL)
            {
                printf("Record #%i: number of previous owners contains wrong symbol (input int number)\n", cur_rec);
                break;
            }
            
            else if (status == EMPTY)
            {
                printf("Record #%i: number of previous owners is empty\n", cur_rec);
                break;
            }
            
            else if (status == NO_ERROR)
                houses[*rec_num].type.secondary.prev_owners = number;
            
            // кол-во предыдущих жильцов
            status = readInt(&number, f, 1, 10);
            
            if (status == EOF)
                break;
            
            else if (status == OUT_OF_RANGE)
            {
                printf("Record #%i: number of previous dwellers is out of range\n", cur_rec);
                break;
            }
            
            else if (status == SYMBOL)
            {
                printf("Record #%i: number of previous dwellers contains wrong symbol (input int number)\n", cur_rec);
                break;
            }
            
            else if (status == EMPTY)
            {
                printf("Record #%i: number of previous dwellers is empty\n", cur_rec);
                break;
            }
            
            else if (status == NO_ERROR)
                houses[*rec_num].type.secondary.prev_dwellers = number;
            
            // жили ли животные
            status = readInt(&number, f, 0, 1);
            
            if (status == EOF)
                break;
            
            else if (status == OUT_OF_RANGE)
            {
                printf("Record #%i: number of previous dwellers is out of range\n", cur_rec);
                break;
            }
            
            else if (status == SYMBOL)
            {
                printf("Record #%i: number of previous dwellers contains wrong symbol (input int number)\n", cur_rec);
                break;
            }
            
            else if (status == NO_ERROR)
                houses[*rec_num].type.secondary.animals = number;
        }
        
        key[*rec_num].index = *rec_num;
        houses[*rec_num].index = *rec_num;
        (*rec_num)++;
        cur_rec++;
    }
    
    if (size == MAX_SIZE)
        printf("%i records added successfully.\n", cur_rec);
    free(entry);
}

// функция добавляет запись вручную
void recTable(house_struct *houses, key_table *key, int *rec_num)
{
    printf("\n");
    int answ = 1;
    int cur_rec = 0;
    char *entry;
    entry = calloc(31, sizeof(*entry));
    
    int number, status;
    
    while (1)
    {
        if (*rec_num == MAX_SIZE)
        {
            printf("Table overflow\n");
            break;
        }
        
        fgetc(stdin);
        
        // адресс
        printf("Input adress: up to 30 symbols: ");
        status = readChar(entry, stdin, CHAR_SIZE);
        
        if (status == EOF)
            break;
        
        else if (status == OUT_OF_RANGE)
        {
            printf("Record #%i is out of range!\n", cur_rec);
            break;
        }
        
        else if (status == EMPTY)
        {
            printf("Record #%i adress is empty\n", cur_rec);
            break;
        }
        
        else if (status == NO_ERROR)
            strcpy(houses[*rec_num].adress, entry);
        
        // общая площадь
        printf("Input total area: int number in range [20;200]: ");
        status = readInt(&number, stdin, 20, 200);
        
        if (status == EOF)
            break;
        
        else if (status == OUT_OF_RANGE)
        {
            printf("Record #%i: total area is out of range\n", cur_rec);
            break;
        }
        
        else if (status == SYMBOL)
        {
            printf("Record #%i: total area contains wrong symbol (input int number)\n", cur_rec);
            break;
        }
        
        else if (status == EMPTY)
        {
            printf("Record #%i: total area is empty\n", cur_rec);
            break;
        }
        
        else if (status == NO_ERROR)
        {
            houses[*rec_num].area = number;
            key[*rec_num].area = houses[*rec_num].area;
        }
        
        // количество комнат
        printf("Input number of rooms: int number in range [1;6]: ");
        status = readInt(&number, stdin, 1, 6);
        
        if (status == EOF)
            break;
        
        else if (status == OUT_OF_RANGE)
        {
            printf("Record #%i: number of rooms is out of range\n", cur_rec);
            break;
        }
        
        else if (status == SYMBOL)
        {
            printf("Record #%i: number of rooms contains wrong symbol (input int number)\n", cur_rec);
            break;
        }
        
        else if (status == EMPTY)
        {
            printf("Record #%i: number of rooms is empty\n", cur_rec);
            break;
        }
        
        else if (status == NO_ERROR)
            houses[*rec_num].rooms = number;
        
        // стоимость одного квадратного метра
        printf("Input cost for square meter: int number in range [10;500 000]: ");
        status = readInt(&number, stdin, 10, 500000);
        
        if (status == EOF)
            break;
        
        else if (status == OUT_OF_RANGE)
        {
            printf("Record #%i: cost for square meter is out of range\n", cur_rec);
            break;
        }
        
        else if (status == SYMBOL)
        {
            printf("Record #%i: cost for square meter contains wrong symbol (input int number)\n", cur_rec);
            break;
        }
        
        else if (status == EMPTY)
        {
            printf("Record #%i: cost for square meter is empty\n", cur_rec);
            break;
        }
        
        else if (status == NO_ERROR)
            houses[*rec_num].price = number;
        
        // первичное или вторичное
        printf("Input category (1: primary; 2: secondary): ");
        status = readInt(&number, stdin, 1, 2);
        
        if (status == EOF)
            break;
        
        else if (status == OUT_OF_RANGE)
        {
            printf("Record #%i: type is out of range\n", cur_rec);
            break;
        }
        
        else if (status == SYMBOL)
        {
            printf("Record #%i: type contains wrong symbol (input int number)\n", cur_rec);
            break;
        }
        
        else if (status == EMPTY)
        {
            printf("Record #%i: typer is empty\n", cur_rec);
            break;
        }
        
        else if (status == NO_ERROR)
            houses[*rec_num].category = number;
        
        if (houses[*rec_num].category == 1)
        {
            // первичное
            printf("Input repair availability (1: yes; 0: no): ");
            status = readInt(&number, stdin, 0, 1);
            
            if (status == EOF)
                break;
            
            else if (status == OUT_OF_RANGE)
            {
                printf("Record #%i: repairs is out of range\n", cur_rec);
                break;
            }
            
            else if (status == SYMBOL)
            {
                printf("Record #%i: repairs contains wrong symbol (input int number)\n", cur_rec);
                break;
            }
            
            else if (status == EMPTY)
            {
                printf("Record #%i: repairs is empty\n", cur_rec);
                break;
            }
            
            else if (status == NO_ERROR)
                houses[*rec_num].type.primary.repairs = number;
        }
        
        // вторичное
        else if (houses[*rec_num].category == 2)
        {
            // год постройки
            printf("Input year of construction: int number in range [1950;2018]: ");
            status = readInt(&number, stdin, 1950, 2018);
            
            if (status == EOF)
                break;
            
            else if (status == OUT_OF_RANGE)
            {
                printf("Record #%i: year of construction is out of range\n", cur_rec);
                break;
            }
            
            else if (status == SYMBOL)
            {
                printf("Record #%i: year of construction contains wrong symbol (input int number)\n", cur_rec);
                break;
            }
            
            else if (status == EMPTY)
            {
                printf("Record #%i: year of construction is empty\n", cur_rec);
                break;
            }
            
            else if (status == NO_ERROR)
                houses[*rec_num].type.secondary.year = number;
            
            // кол-во предыдущих владельцев
            printf("Input number of previous owners: int number in range [1;50]: ");
            status = readInt(&number, stdin, 1, 50);
            
            if (status == EOF)
                break;
            
            else if (status == OUT_OF_RANGE)
            {
                printf("Record #%i: number of previous owners is out of range\n", cur_rec);
                break;
            }
            
            else if (status == SYMBOL)
            {
                printf("Record #%i: number of previous owners contains wrong symbol (input int number)\n", cur_rec);
                break;
            }
            
            else if (status == EMPTY)
            {
                printf("Record #%i: number of previous owners is empty\n", cur_rec);
                break;
            }
            
            else if (status == NO_ERROR)
                houses[*rec_num].type.secondary.prev_owners = number;
            
            // кол-во предыдущих жильцов
            printf("Input number of previous dwellers: int number in range [1;10]: ");
            status = readInt(&number, stdin, 1, 10);
            
            if (status == EOF)
                break;
            
            else if (status == OUT_OF_RANGE)
            {
                printf("Record #%i: number of previous dwellers is out of range\n", cur_rec);
                break;
            }
            
            else if (status == SYMBOL)
            {
                printf("Record #%i: number of previous dwellers contains wrong symbol (input int number)\n", cur_rec);
                break;
            }
            
            else if (status == EMPTY)
            {
                printf("Record #%i: number of previous dwellers is empty\n", cur_rec);
                break;
            }
            
            else if (status == NO_ERROR)
                houses[*rec_num].type.secondary.prev_dwellers = number;
            
            // жили ли в квартире животные
            printf("Input if there lived animals (1: yes; 0: no): ");
            status = readInt(&number, stdin, 0, 1);
            
            if (status == EOF)
                break;
            
            else if (status == OUT_OF_RANGE)
            {
                printf("Record #%i: animals living is out of range\n", cur_rec);
                break;
            }
            
            else if (status == SYMBOL)
            {
                printf("Record #%i: animals living contains wrong symbol (input int number)\n", cur_rec);
                break;
            }
            
            else if (status == EMPTY)
            {
                printf("Record #%i: animals living is empty\n", cur_rec);
                break;
            }
            
            else if (status == NO_ERROR)
                houses[*rec_num].type.secondary.animals = number;
        }
        
        key[*rec_num].index = *rec_num;
        houses[*rec_num].index = *rec_num;
        (*rec_num)++;
        cur_rec++;
        
        printf("Do you want to add one more record? (1: yes; 0: no): ");
        if ((scanf("%i",&answ) == 0) || (answ > 1) || (answ < 0))
        {
            printf("Input error!\n");
            break;
        }
        
        if (answ == 0)
            break;
    }
    free(entry);
    printf("%i records added successfully.\nTotal number of records: %i\n", cur_rec, *rec_num);
}

void printTable (house_struct *houses, key_table *key, int *rec_num, int *flag_sort)
{
    if (*rec_num == 0)
    {
        printf("\nTable is empty\n");
        return;
    }
    
    int k_index;
    
    printf("\n");
    printf("┌────┬──────────────────────────┬───────┬───────┬────────────┬──────────┬─────────┬──────┬────────┬──────────┬─────────┐\n");
    printf("│ №  │ Adress                   │ Area  │ Rooms │ Cost of 1m │ Category │ Repairs │ Year │ Owners | Dwellers | Animals |\n");
    printf("├────┼──────────────────────────┼───────┼───────┼────────────┼──────────┼─────────┼──────┼────────┼──────────┼─────────┤\n");
    
    for (int i = 0; i < *rec_num; i++)
    {
        if(flag_sort == 1)
            k_index = key[i].index;
        else
            k_index = houses[i].index;
        printf("│ %2d │ %24s │ %5d │ %5d │ %10d │", i, houses[k_index].adress, houses[k_index].area, houses[k_index].rooms, houses[k_index].price);
        
        if (houses[k_index].category == 1)
        {
            if (houses[k_index].type.primary.repairs == 1)
                printf(" Primary  │   Yes   │ ---- │ ------ │ -------- │ ------- │\n");
            
            if (houses[k_index].type.primary.repairs == 0)
                printf(" Primary  │   No    │ ---- │ ------ │ -------- │ ------- │\n");
        }
        
        if (houses[k_index].category == 2)
        {
            if (houses[k_index].type.secondary.animals == 1)
                printf(" Secondary│ ------- │ %4d │ %6d │ %8d │   Yes   │\n", houses[k_index].type.secondary.year, houses[k_index].type.secondary.prev_owners, houses[k_index].type.secondary.prev_dwellers);
            
            if (houses[k_index].type.secondary.animals == 0)
                printf(" Secondary│ ------- │ %4d │ %6d │ %8d │   No    │\n", houses[k_index].type.secondary.year, houses[k_index].type.secondary.prev_owners, houses[k_index].type.secondary.prev_dwellers);
        }
        
        if (i != *rec_num-1)
            printf("├────┼──────────────────────────┼───────┼───────┼────────────┼──────────┼─────────┼──────┼────────┼──────────┼─────────┤\n");
        else
            printf("└────┴──────────────────────────┴───────┴───────┴────────────┴──────────┴─────────┴──────┴────────┴──────────┴─────────┘\n");
    }
}

void printKeyTable (key_table *key, int *rec_num)
{
    if (*rec_num == 0)
    {
        printf("\nTable is empty\n");
        return;
    }
    
    printf("\n");
    printf("┌─────────────┬───────────┬───────────────┐\n");
    printf("│ Table index │ Key index │   Total area  │\n");
    printf("├─────────────┼───────────┼───────────────┤\n");
    
    for (int i = 0; i < *rec_num; i++)
    {
        printf("│ %11i │ %9i │ %13i │\n", i, key[i].index, key[i].area);
        
        if (i != *rec_num - 1)
            printf("├─────────────┼───────────┼───────────────┤\n");
        else
            printf("└─────────────┴───────────┴───────────────┘\n");
    }
}

// функция находит квартиры по фильтру
void findApartment(house_struct *houses, key_table *key, int rec_num)
{
    if (rec_num == 0)
    {
        printf("\nTable is empty!\n");
        return;
    }
    
    int min_price, max_price, flag = 0;
    int k_index;
    
    printf("Input minimal price for one square meter: ");
    
    if (scanf("%i", &min_price) == 0)
    {
        printf("Input error\n");
        return;
    }
    printf("Input miaximal price for one square meter: ");
    
    if (scanf("%i", &max_price) == 0)
    {
        printf("Input error\n");
        return;
    }
    
    if (min_price > max_price)
    {
        printf("Min price is bigger than max price\n");
        return;
    }
    
    if (min_price < 1)
    {
        printf("Price is out of permitted range\n");
        return;
    }
    
    for (int i = 0; i < rec_num; i++)
    {
        k_index = key[i].index;
        
        if ((houses[k_index].price >= min_price) && (houses[k_index].price <= max_price))
        {
            if (houses[k_index].rooms == 2)
            {
                if (houses[k_index].category == 2)
                {
                    if (houses[k_index].type.secondary.animals == 0)
                    {
                        if (flag == 0)
                        {
                            flag = 1;
                            printf("\n");
                            printf("┌────┬──────────────────────────┬───────┬───────┬────────────┬──────────┬─────────┬──────┬────────┬──────────┬─────────┐\n");
                            printf("│ №  │ Adress                   │ Area  │ Rooms │ Cost of 1m │ Category │ Repairs │ Year │ Owners | Dwellers | Animals |\n");
                            printf("├────┼──────────────────────────┼───────┼───────┼────────────┼──────────┼─────────┼──────┼────────┼──────────┼─────────┤\n");
                            printf("│ %2d │ %24s │ %5d │ %5d │ %10d │ Secondary│ ------- │ %4d │ %6d │ %8d │   No    │\n", i, houses[k_index].adress, houses[k_index].area, houses[k_index].rooms, houses[k_index].price, houses[k_index].type.secondary.year, houses[k_index].type.secondary.prev_owners, houses[k_index].type.secondary.prev_dwellers);
                        }
                    
                        else
                        {
                            if ((i > 0) && (i < rec_num))
                                printf("├────┼──────────────────────────┼───────┼───────┼────────────┼──────────┼─────────┼──────┼────────┼──────────┼─────────┤\n");
                        
                            printf("│ %2d │ %24s │ %5d │ %5d │ %10d │ Secondary│ ------- │ %4d │ %6d │ %8d │   No    │\n", i, houses[k_index].adress, houses[k_index].area, houses[k_index].rooms, houses[k_index].price, houses[k_index].type.secondary.year, houses[k_index].type.secondary.prev_owners, houses[k_index].type.secondary.prev_dwellers);
                        }
                    }
                }
            }
        }
        }
    
        if (flag == 0)
            printf("There's no such apartments\n");
        else
            printf("└────┴──────────────────────────┴───────┴───────┴────────────┴──────────┴─────────┴──────┴────────┴──────────┴─────────┘\n");
}

void exitMenu()
{
    printf("Press enter to continue: ");
    while (getchar() != '\n');
    getchar();
    system("clear");
}
