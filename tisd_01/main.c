#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LEN_TZ 30       // максимальная длина мантиссы
#define EXP_LIMIT 99999     // наибольший возможный порядок
#define MAX_LEN 32          // максимальная длина мантиссы с учетом точки и Е
#define BASE 10             // система счисления

#define BAD_DATA -1                 // некорректный ввод
#define CHAR_IN_POWER -2            // число состоит не только 
#define MANTISSA_SIZE_ERROR -3      // превышения размера мантиссы
#define POWER_SIZE_ERROR -4         // превышение размера порядка
#define NOT_INTEGER -5              // длинное число не является целым

//структура длинного числа
typedef struct mantiss_struct
{
    bool sign;                      // знак (1 - введён '-', 0 - нет знака(по умолчанию))
    int e;                          // экспонента
    int arr[MAX_LEN];               // мантисса
    int n;                          // длина всего числа
    int mantissa_len;               // длина мантиссы
} mantiss_struct;

// пустой шаблон для целого числа -0 E 0
struct mantiss_struct getEmptyMantissStruct()
{
    struct mantiss_struct emptyMantissStruct;
    emptyMantissStruct.sign = true;
    emptyMantissStruct.e = 0;

    for(int i = 0; i < MAX_LEN; i++)
        emptyMantissStruct.arr[i] = 0;
    
    emptyMantissStruct.n = 1;
    return emptyMantissStruct;
}

// функция переворачивает массив в структуре
void reverse(struct mantiss_struct *res)
{
    int c, i, j;
    c = i = j = 0;
    for(i = 0, j = res->n - 1; i < j; i++, j--)
    {
        c = res->arr[i];
        res->arr[i] = res->arr[j];
        res->arr[j] = c;
    }
}

// функция проверяет, является ли введенный символ числом
bool isDigit(char value)
{
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 10; i++)
    {
        if (digits[i] == value)
            return true;
    }
    return false;
}

// ввод длинного действительного числа
int inputMantissFloat(struct mantiss_struct *array)
{
    char value = '\0';
    array->n = 0;
    //int i = 0;
    array->e = 0;
    //bool hasPoint = false;
    bool dot_status = false;
    bool status = false;
    int dot_index = 0;
    array->sign = true;
    
    fflush(stdin);
    
    while(scanf("%c", &value))
    {
        if (value == 'E' || value == 'e')                           // проверка наличия Е
        {
            char pow[5];
            int i = 0;
            bool stat_sign = false;
            while(scanf("%c", &value) && value != '\n')
            {
                if (value == '-' && !stat_sign && i == 0)
                    stat_sign = true;
                else
                {
                    if (!isDigit(value))
                        return CHAR_IN_POWER;
                    
                    if (i >= EXP_LIMIT)
                        return POWER_SIZE_ERROR;
                }
                if (value != '-') {
                    pow[i] = value;
                    i++;
                }
            }
            if (stat_sign)                                         // индекс точки
                dot_index += atoi(pow);
            else
                dot_index -= atoi(pow);
            break;
        }
        
        if (value != '\n')
        {
            if (!status && value != '0')
                status = true;
            
            if (status)
            {
                if (value != '.')
                {
                    if (isDigit(value))
                    {
                        array->arr[array->n] = value - '0';             // перевод char в int
                        array->n++;
                        if(dot_status)
                            dot_index++;
                        
                    }
                    else
                    {
                        if (value == '-')
                        {
                            if (array->n != 0)
                                return BAD_DATA;
                            
                            if (!array->sign)
                                return BAD_DATA;
                            
                            array->sign = false;
                        }
                        else
                            return BAD_DATA;
                    }
                    if (array->n > MAX_LEN - 2)
                        return MANTISSA_SIZE_ERROR;
                }
                else
                {
                    if (dot_status)
                        return BAD_DATA;
                    dot_status = true;
                }
            }
        }
        else
            break;
    }
    
    array->e += dot_index;
    array->mantissa_len = array->n;
    
    return 0;
}

// ввод длинного целого числа
int inputMantissInteger(struct mantiss_struct *array)
{
    char value = '\0';
    array->n = 0;
    bool status = false;
    array->sign = true;
    
    fflush(stdin);
    
    while(scanf("%c", &value))
    {
        if (value == 'E' || value == 'e' || value == '.')           // проверка на целое число
            return BAD_DATA;
        
        if (value != '\n')
        {
            if (!status && value != '0')
                status = true;
            
            if (status)
            {
                if (isDigit(value))
                {
                    array->arr[array->n] = value - '0';             // перевод char в int
                    array->n++;
                }
                else
                {
                    if (value == '-')
                    {
                        if (array->n != 0)
                            return BAD_DATA;
                            
                        if (!array->sign)
                            return BAD_DATA;
                            
                        array->sign = false;
                    }
                    else
                        return BAD_DATA;
                }
                if (array->n > MAX_LEN - 2)
                    return MANTISSA_SIZE_ERROR;
            }
        }
        else
            break;
    }
    
    array->mantissa_len = array->n;
    
    return 0;
}

// добавление нулей
void addNulls(struct mantiss_struct *value)
{
    for(; value->n < MAX_LEN - 1; value->arr[value->n] = 0, value->n++);
}

// сдвигает числа на один разряд вправо
void extend(struct mantiss_struct *tmp)
{
    for (int i = tmp->n; i >= 1; i--)
        tmp->arr[i] = tmp->arr[i-1];
    tmp->arr[0] = 0;
    if (tmp->arr[tmp->n])
        tmp->n++;
}

// функция умножения длинного числа на короткое целое
mantiss_struct multiply(const struct mantiss_struct *number, int multiplier)
{
    struct mantiss_struct res = getEmptyMantissStruct();            // пустая структура результата
    res.n = number->n;
    int r = 0;                                                      // значение, переносимое в следующий разряд
    int i = 0;

    for (; i < res.n || r; i++)
    {
        res.arr[i] = number->arr[i] * multiplier + r;
        r = res.arr[i] / 10;
        res.arr[i] -= r * 10;
    }
    res.n = i;
    return res;
}

// функция сравнения двух длинных чисел
bool compare(struct mantiss_struct number_1, struct mantiss_struct number_2)
{
    if (number_1.n != number_2.n)                               // если одинаковой длины
        return number_1.n > number_2.n;

    for (int i = number_1.n - 1; i >= 0; i--)                   // если разной длины
    {
        if (number_1.arr[i] != number_2.arr[i])
            return number_1.arr[i] > number_2.arr[i];
    }
    return false;
}

// функция вычитания двух длинных чисел
mantiss_struct difference(struct mantiss_struct number_1, struct mantiss_struct number_2)
{
    struct mantiss_struct res = number_1;                   // перезапись уменьшаемого в пустой массив

    for (int i = 0; i < res.n; i++)
    {
        res.arr[i] -= number_2.arr[i];                      // вычитание элементов по разрядам
        if (res.arr[i] < 0)
        {
            res.arr[i] += 10;
            res.arr[i + 1]--;
        }
    }
    int lead_null_indx = res.n-1;
    while (lead_null_indx && !res.arr[lead_null_indx])
        lead_null_indx--;
    res.n = lead_null_indx + 1;
    return res;
}

// функция удаляет незначащие нули
int delUselessNulls(struct mantiss_struct *value)
{
    int i = 0;
    for(; i != MAX_LEN && !value->arr[i]; i++);
    return i;
}

// функция округления
void roundArr(struct mantiss_struct *value)
{
    int i = 1;
    while(i != value->n)
    {
        if (value->arr[i] == BASE - 1)
            value->arr[i] = 0;
        else
        {
            value->arr[i]++;
            if (value->arr[i] != BASE - 1)
                break;
        }

        i++;
    }
}

// функция деления
mantiss_struct division(struct mantiss_struct *dividend, struct mantiss_struct *divider)
{
    struct mantiss_struct res = getEmptyMantissStruct();        // результат
    struct mantiss_struct tmp = getEmptyMantissStruct();        // промежуточное делимое

    bool stat = false;
    int z = 0;

    for (int i = dividend->n - 1; i >= 0; i--)
    {
        extend(&tmp);                                   // "домножение" делимого до размера делителя
        tmp.arr[0] = dividend->arr[i];
        int x = 0;                                      // подбираем такой x, что cur * x < tmp
        int l = 0, r = BASE;

        while (l <= r)
        {
            int m = (l + r) >> 1;

            struct mantiss_struct cur;                  // промежуточный делитель
            cur = getEmptyMantissStruct();
            cur = multiply(divider, m);

            if (!compare(cur, tmp))                     // если делимое больше делителя
            {
                x = m;
                l = m + 1;
            }
            else                                        // если делитель больше делимого
                r = m - 1;
        }
        z++;

        if (z == MAX_LEN - 1 && x >= 5)
            stat = true;
        else
            res.arr[i] = x;                             // добавление x в результат

        struct mantiss_struct mul;                      // результат умножения делителя на целое число
        mul = getEmptyMantissStruct();
        mul = multiply(divider, x);
        tmp = difference(tmp, mul);

        if (i >= dividend->n - dividend->mantissa_len)
            res.e++;                                    // нахождение экспоненты
    }

    int lead_null_indx = dividend->n - 1;                           // удаление незначащих нулей
    while (lead_null_indx >= 0 && !res.arr[lead_null_indx])
    {
        lead_null_indx--;
        res.e--;
        z--;
    }

    res.n = lead_null_indx + 1;
    z = z - delUselessNulls(&res);

    if (stat)
        roundArr(&res);

    res.e -= dividend->e - divider->e;
    
    if(dividend->sign == 0 && divider->sign == 0)               // определение знака результата
        res.sign = 0;
    else if(dividend->sign == 1 && divider->sign == 1)
        res.sign = 0;
    else
        res.sign = dividend->sign + divider->sign;
    return res;
}

// функция проверяет, является ли число нулем
bool isZero(struct mantiss_struct *divider)
{
    for(int i = 0; i < divider->n; i++)
    {
        if(divider->arr[i] != 0)
            return false;
    }
    return true;
}

// функция вывода длинного числа на экран
void writeMantiss(struct mantiss_struct *res)
{
    
    if (res->e <= EXP_LIMIT && res->e >= -EXP_LIMIT)
    {
        if(res->sign == true)
            printf("-");

        printf("0.");

        int i = 0;
        for(i = res->n - 1; i >= delUselessNulls(res); i--)
            printf("%d", res->arr[i]);

        printf(" E %d\n", res->e);
    }
    else
        puts("\nError: Out of Range");
}

int main()
{
    struct mantiss_struct devidend = getEmptyMantissStruct();
    struct mantiss_struct divider = getEmptyMantissStruct();
    struct mantiss_struct res = getEmptyMantissStruct();

    int status = 0;
    
    printf("If number is positive - symbol '+' is not needed\n\n");

    printf("|    Input intenger number   |\n");
    printf(" ----------------------------\n");
    printf("1        10        20       30\n");
    printf("|--------|---------|---------|\n");

    setbuf(stdout, NULL);

    status = inputMantissInteger(&devidend);       // ввод делимого
    switch (status)
    {
        case (BAD_DATA):
            printf("\nError: Incorrect input\n");
            return 0;
            break;
        case (MANTISSA_SIZE_ERROR):
            printf("\nError: Mantissa is too big\n");
            return 0;
            break;
        case (POWER_SIZE_ERROR):
            printf("\nError: Power is too big\n");
            return 0;
            break;
        case (CHAR_IN_POWER):
            printf("\nError: Incorrect input\n");
            return 0;
            break;
    }
    
    addNulls(&devidend);
    reverse(&devidend);

    printf("\n");
    printf("| Input float number without space |\n");
    printf(" ----------------------------------\n");
    printf("1        10        20       30e1   5\n");
    printf("|--------|---------|---------|Е|---|\n");
    
    status = inputMantissFloat(&divider);            // ввод делителя
    switch (status)
    {
        case (BAD_DATA):
            printf("\nError: Incorrect input\n");
            return 0;
            break;
        case (MANTISSA_SIZE_ERROR):
            printf("\nError: Mantissa is too big\n");
            return 0;
            break;
        case (POWER_SIZE_ERROR):
            printf("\nError: Power is too big\n");
            return 0;
            break;
        case (CHAR_IN_POWER):
            printf("\nError: Incorrect input\n");
            return 0;
            break;
    }
    
    // проверка деления на ноль
    if (isZero(&divider))
    {
        printf("\nError: Division by zero\n");
        return 0;
    }
    
    reverse(&divider);
    res = division(&devidend, &divider);

    printf("\nAnswer: ");
    writeMantiss(&res);

    return 0;
}
