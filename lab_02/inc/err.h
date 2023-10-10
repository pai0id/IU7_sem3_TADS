#ifndef ERR_H
#define ERR_H

#include <stdio.h>

#define OK 0                /// Ошибок не возникло
#define ERR_IO 1            /// Ошибка ввода
#define ERR_RANGE 2         /// Ошибка размера
#define ERR_OVERFLOW 3      /// Переполнение
#define ERR_ARGS 4          /// Ошибка аргументов командной строки
#define ERR_NO_FILE 5       /// Файл отсутствует
#define ERR_EMPTY 6         /// Массив пуст
#define ERR_NOT_FOUND 7     /// Структура не найдена
#define ERR_EXIT 8
#define ERR_WRONG_COMMAND 9
#define ERR_NO_SPEC 10

void prn_msg(int rc);

#endif
