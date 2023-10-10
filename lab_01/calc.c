#include "calc.h"

int mult_nums(const struct num_t *num1,const struct num_t *num2, struct num_t *res, size_t max_res_len)
{
    int res_tmp[MAX_MANTISSA_LEN * 2];
    size_t k = 0;
    int carry = 0;

    res->sign = (num1->sign == num2->sign) ? '+' : '-';

    for (size_t i = 0; i < MAX_MANTISSA_LEN * 2; ++i)
        res_tmp[i] = 0;
    for (int i = num1->mantissa_size - 1; i >= 0; --i)
    {
        k = num1->mantissa_size - 1 - i;
        for (int j = num2->mantissa_size - 1; j >= 0; --j)
            res_tmp[k++] += num1->mantissa[i] * num2->mantissa[j];
    }
    for (size_t i = 0; i < k; ++i)
    {
        res_tmp[i] += carry;
        carry = res_tmp[i] / 10;
        res_tmp[i] %= 10;
    }
    while (carry != 0)
    {
        res_tmp[k++] += carry;
        carry = res_tmp[k] / 10;
        res_tmp[k] %= 10;
    }
    size_t i = 0;
    while (k - i > max_res_len)
    {
        res_tmp[i + 1] = res_tmp[i] / 5 == 1 ? res_tmp[i + 1] + 1: res_tmp[i + 1];
        i++;
    }
    while (res_tmp[i] > 9)
        res_tmp[++i] += 1;
    res->mantissa_size = 0;
    size_t tmp = k;
    while (k-- > i)
        res->mantissa[res->mantissa_size++] = res_tmp[k];
    res->exponent = num1->exponent + num2->exponent - num1->mantissa_size - num2->mantissa_size + tmp;
    normalize(res);

    if (res->mantissa[0] && (res->exponent > EXPONENT_UP_LIMIT ||
         res->exponent < EXPONENT_DOWN_LIMIT))
            return ERR_RANGE_EXP;
    else if (!res->mantissa[0])
        res->exponent = 0;
    return OK;
}
