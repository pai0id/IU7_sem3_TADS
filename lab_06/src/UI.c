#include "UI.h"
#include <stdio.h>

void print_actions()
{
    printf("Выберите действие:\n");
    printf("1) Добавить строку в дерево\n");
    printf("2) Добавить узел\n");
    printf("3) Удалить узел\n");
    printf("4) Вывести в строку\n");
    printf("5) Вывести в виде дерева\n");
    printf("6) Вывести узел\n");
    printf("7) Удалить повторяющиеся буквы\n");
    printf("8) Сравнить время удаления повторяющихся букв из дерева и из строки\n");
    printf("9) Сравнить эффективность алгоритма поиска\n");
    printf("10) Вывести информацию о программе\n");
    printf("-1) Очистить дерево\n");
    printf("0) Выход\n");
}

void print_info()
{
    for (size_t i = 0; i < 100; ++i)
        printf("-");
    printf("\n");
    printf("\033[0;36m Поляков Андрей ИУ7-32Б\n\n");
    printf("Построить двоичное дерево поиска из букв вводимой строки.\n");
    printf("Вывести его на экран в виде дерева. Выделить цветом все буквы, встречающиеся более одного раза.\n");
    printf("Удалить из дерева эти буквы. Вывести оставшиеся элементы дерева при постфиксном его обходе.\n");
    printf("Сравнить время удаления повторяющихся букв из дерева и из строки.Реализовать основные операции работы с деревом:\n");
    printf("обход дерева, включение, исключение и поиск узлов. Сравнить эффективность алгоритмов сортировки и\n");
    printf("поиска в зависимости от высоты деревьев и степени их ветвления.\n");
    for (size_t i = 0; i < 100; ++i)
        printf("-");
    printf("\n\033[0;37m");
}
