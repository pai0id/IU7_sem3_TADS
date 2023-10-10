/**
 *  \author Андрей ИУ7-32Б
 * 
 *  Вариант 5
 * 
 *  Программа, выполняющая умножение двух длинных чиселв форме +-m.n E +-K
 *  (длина m+n до 40 для первого числа, до 35 для второго и до 40 для результата, а длина K до 5.
 * 
 *  
 */

#include <stdio.h>
#include "real_nums.h"
#include "calc.h"
#include "err.h"
#include "UI.h"

int main()
{
    struct num_t num1, num2, res;
    int rc = 0;
    print_ui();
    printf("Введите первое число:\n");
    print_line();
    rc = read_real_num(stdin, &num1, 40);
    if (!rc)
    {
        printf("Введите второе число:\n");
        print_line();
        rc = read_real_num(stdin, &num2, 35);
    }
    if (!rc)
    {
        rc = mult_nums(&num1, &num2, &res, 40);
        if (!rc)
        {
            print_line();
            printf("Res: ");
            print_real_num(stdout, &res);
        }
    }
    print_err_msg(rc);
    return rc;
}
