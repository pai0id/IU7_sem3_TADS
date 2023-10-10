#include "UI.h"

void print_line()
{
    for (int i = 1; i <= LINE_LEN; ++i)
    {
        if (i % 5 == 0 || i == 1)
            printf("%d", i);
        else if (!(i % 5 == 1 && i > 9))
            printf("-");
    }
    printf("\n");
    for (int i = 1; i <= LINE_LEN; ++i)
    {
        if (i % 5 == 0 || i == 1)
            printf("|");
        else
            printf(" ");
    }
    printf("\n");
}

void print_ui()
{
    printf("/");
    for (size_t i = 0; i < 100; ++i)
        printf("-");
    printf("\\ \n");
    printf("| Поляков Андрей ИУ7-32Б   Вариант 5\n| Программа, выполняющая умножение двух длинных чисел в форме +-m.n E +-K\n");
    printf("| (длина m+n до 40 для первого числа, до 35 для второго и до 40 для результата, а длина K до 5)\n");
    printf("\\");
    for (size_t i = 0; i < 100; ++i)
        printf("-");
    printf("/ \n\n");
}
