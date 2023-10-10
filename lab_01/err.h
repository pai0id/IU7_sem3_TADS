#ifndef ERR_H
#define ERR_H

#define OK 0
#define ERR_IO 1
#define ERR_RANGE_EXP 2
#define ERR_RANGE_MANT 3

/**
 * \brief Выводит сообщение об ошибке на основе переданного кода ошибки.
 *
 * Эта функция принимает код ошибки (rc) и выводит соответствующее сообщение об ошибке.
 * Если код ошибки равен OK, ничего не происходит. В противном случае, выводится соответствующее сообщение:
 * - ERR_IO: "Incorrect input"
 * - ERR_RANGE: "Range error occured"
 * - Другие значения: "An unknown error occured"
 *
 * \param rc [in] - код ошибки, для которого нужно вывести сообщение
 */
void print_err_msg(int rc);

#endif
