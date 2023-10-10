#include "real_nums.h"
#include "err.h"
#include <ctype.h>

void normalize(struct num_t *num)
{
    while (num->mantissa_size > 0 && num->mantissa[num->mantissa_size - 1] == 0)
        num->mantissa_size--;
    while (num->mantissa_size > 0 && num->mantissa[0] == 0)
    {
        for (size_t i = 0; i < num->mantissa_size; ++i)
            num->mantissa[i] = num->mantissa[i + 1];
        num->mantissa_size--;
        num->exponent--;
    }
}

int read_real_num(FILE *f, struct num_t *num, size_t mantissa_max_size)
{
    char curr = getc(f);
    size_t digits = 0, digits_after_point = 0;
    if (curr == '+' || curr == '-')
    {
        num->sign = curr;
        curr = getc(f);
    }
    else
        num->sign = '+';
    while (curr == '0')
    {
        curr = getc(f);
        if (curr == '\n' || curr == 'E')
            num->mantissa[digits++] = 0;
    }
    while (isdigit(curr))
    {
        if (digits >= mantissa_max_size)
            return ERR_RANGE_MANT;
        num->mantissa[digits] = curr - '0';
        digits++;
        curr = getc(f);
    }
    if (curr == '.')
    {
        curr = getc(f);
        if (isdigit(curr))
        {
            while (isdigit(curr))
            {
                if (digits >= mantissa_max_size)
                {
                    while (curr == '0')
                        curr = getc(f);
                    if (isdigit(curr))
                        return ERR_RANGE_MANT;
                    else
                        break;
                }
                num->mantissa[digits] = curr - '0';
                digits++;
                digits_after_point++;
                curr = getc(f);
            }
        }
        else
            return ERR_IO;
    }
    if (digits == 0)
        return ERR_IO;
    while (curr == ' ')
        curr = getc(f);
    if (curr == 'E')
    {
        if (fscanf(f, "%d", &num->exponent) != 1)
            return ERR_IO;
        else if (num->exponent > EXPONENT_UP_LIMIT ||
         num->exponent < EXPONENT_DOWN_LIMIT)
            return ERR_RANGE_EXP;
        curr = getc(f);
    }
    else
        num->exponent = 0;
    num->exponent -= digits_after_point;
    num->exponent += digits;
    num->mantissa_size = digits;
    normalize(num);
    while (curr == ' ')
        curr = getc(f);
    if (curr != '\n')
        return ERR_IO;
    return OK;
}

void print_real_num(FILE *f, struct num_t *num)
{
    fprintf(f, "%c0.", num->sign);
    for (size_t i = 0; i < num->mantissa_size; ++i)
    {
        fprintf(f, "%d", num->mantissa[i]);
    }
    if (num->mantissa_size == 0)
        fprintf(f, "0 E0\n");
    else
        fprintf(f, " E%d\n", num->exponent);
}
