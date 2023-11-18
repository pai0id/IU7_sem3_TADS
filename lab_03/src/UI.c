#include "UI.h"

void print_actions()
{
    printf("Выберите действие:\n");
    printf("1) Считать матрицу из файла\n");
    printf("2) Ввести матрицу\n");
    printf("3) Считать вектор-столбец из файла\n");
    printf("4) Ввести вектор-столбец\n");
    printf("5) Вывести матрицу\n");
    printf("6) Вывести вектор-столбец\n");
    printf("7) Произвести умножение матрицы на вектор-столбец, применяя алгоритм работы с разреженными матрицами\n");
    printf("8) Произвести умножение матрицы на вектор-столбец, применяя стандартный алгоритм работы с матрицами\n");
    printf("9) Сравнить алгоритмы\n");
    printf("10) Сохранить матрицу в файл\n");
    printf("11) Сохранить вектор-столбец в файл\n");
    printf("12) Вывести информацию о программе\n");
    printf("0) Выход\n");
}

void print_info()
{
    for (size_t i = 0; i < 100; ++i)
        printf("-");
    printf("\n");
    printf("\033[0;36m Поляков Андрей ИУ7-32Б\n\n");
    printf("Программа позволяющая, применяя алгоритм работы с разреженными матрицами вещественных чисел\n");
    printf("и стандартный алгоритм работы с матрицами, произвести умножение:\n-Разреженной матрицы:");
    printf("    1) вектор A содержит значения ненулевых элементов\n");
    printf("    2) вектор JA содержит номера столбцов для элементов вектора A\n");
    printf("    3) - вектор IA, в элементе Nk которого находится номер компонент\n");
    printf("    в A и JA, с которых начинается описание строки Nk матрицы A\n");
    printf("\n-И Разреженного вектора-столбца:\n");
    printf("    1) вектор A содержит значения ненулевых элементов\n");
    printf("    2) вектор IA содержит номера строк для элементов вектора A\n");
    printf("Элементы матрицы и вектора необходимо вводить слева направо, сверху вниз\n");
    printf("\n- А также вывести результаты сравнения работы двух алгоритмов:\n");
    printf("    Программа замеряет время умножения разными алгоритмами.\n");
    printf("    Для каждого из тестов программа выполняет многочисленные замеры, пока их RSE не становится <5.\n");
    printf("    Затем все тестовые случаи сравниваются и оценивается их эффективность.\n\n\033[0;37m");
    for (size_t i = 0; i < 100; ++i)
        printf("-");
    printf("\n");
}