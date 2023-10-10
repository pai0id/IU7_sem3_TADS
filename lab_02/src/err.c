#include "err.h"

void prn_msg(int rc)
{
    switch(rc)
    {
    case OK:
        break;
    case ERR_IO:
        printf("\033[0;31m Ошибка ввода\n\033[0;37m");
        break;
    case ERR_RANGE:
        printf("\033[0;31m Ошибка размера\n\033[0;37m");
        break;
    case ERR_OVERFLOW:
        printf("\033[0;31m Переполнение\n\033[0;37m");
        break;
    case ERR_ARGS:
        printf("\033[0;31m Ошибка аргументов командной строки\n\033[0;37m");
        break;
    case ERR_NO_FILE:
        printf("\033[0;31m Файл отсутствует\n\033[0;37m");
        break;
    case ERR_EMPTY:
        printf("\033[0;31m Массив пуст\n\033[0;37m");
        break;
    case ERR_NOT_FOUND:
        printf("\033[0;31m Структура не найдена\n\033[0;37m");
        break;
    case ERR_EXIT:
        break;
    case ERR_WRONG_COMMAND:
        printf("\033[0;31m Некорректная комманда\n\033[0;37m");
        break;
    case ERR_NO_SPEC:
        printf("\033[0;31m Нет романов данного автора\n\033[0;37m");
        break;
    default:
        printf("\033[0;31m Неизвестная ошибка\n\033[0;37m");
    }
}
