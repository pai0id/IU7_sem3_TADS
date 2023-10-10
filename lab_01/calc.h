#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include "real_nums.h"
#include "err.h"

/**
 * \brief Умножает два числа и сохраняет результат в структуре res.
 *
 * Эта функция умножает два числа, представленных в структурах num_t (num1 и num2), и сохраняет результат в структуре res.
 * Максимальная длина результата ограничена значением max_res_len.
 *
 * \param num1 [in] - указатель на первое число для умножения
 * \param num2 [in] - указатель на второе число для умножения
 * \param res [out] - указатель на структуру, в которую будет сохранен результат
 * \param max_res_len [in] - максимальная длина результата
 * 
* \return Код ошибки:
 *         - OK, если найдено произведение
 *         - ERR_RANGE, если превышен максимальный размер порядка
 */
int mult_nums(const struct num_t *num1,const struct num_t *num2, struct num_t *res, size_t max_res_len);

#endif
