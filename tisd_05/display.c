#include "display.h"

void showLen(queue* q)
{
    printf("Текущая длина %s: %d\n", q->name, q->tmp_size);
    if (q->count_req > 0)
        printf("Средняя длина of %s: %f\n", q->name, (double) q->sum_size / (double) q->count_req);
}
