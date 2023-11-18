#include <stdio.h>
#include "arr_stack.h"
#include "list_stack.h"
#include "test_stack.h"
#include "stack_op.h"
#include "err.h"

void print_info()
{
    for (size_t i = 0; i < 100; ++i)
        printf("-");
    printf("\n");
    printf("\033[0;36m Поляков Андрей ИУ7-32Б Вариант 8\n\n");
    printf("Программа позволяющая работать  со  стеком, выполняющяя  операции  добавления, удаления  элементов\n и  вывода  текущего состояния стека.\n");
    printf("Стек реализован двумя способами: статическим  массивом и односвязным списком.\n");
    printf("Программа позволяет отсортировать введенные в два стека данные в третий стек. При этом все данные переносятся в третий стек\n");
    printf("Также программа позволяет произвести сравнение эффективноости сортировки при разных представлениях стека\n");
    printf("\n\033[0;37m");
    for (size_t i = 0; i < 100; ++i)
        printf("-");
    printf("\n");
}

int main()
{
    freed_stack_t freed_stack = init_freed_stack(100);

    list_stack_t list_stack1 = NULL;
    list_stack_t list_stack2 = NULL;
    list_stack_t sorted_list_stack = NULL;

    arr_stack_t arr_stack1 = arr_stack_create();
    arr_stack_make_empty(arr_stack1);
    arr_stack_t arr_stack2= arr_stack_create();
    arr_stack_make_empty(arr_stack2);
    arr_stack_t sorted_arr_stack = arr_stack_create();
    arr_stack_make_empty(sorted_arr_stack);

    int choice;
    int data;
    int cnt, rc, x;
    char tmp[7];

    while (1)
    {
        printf("Стeки реализованные с помощью массива:\n");
        printf("\n 1. Добавить элемент в стек 1\n");
        printf("-1. Взять элемент из стека 1\n");
        printf(" 2. Добавить элемент в стек 2\n");
        printf("-2. Взять элемент из стека 2\n");
        printf(" 3. Отсортировать стеки и вывести результат\n");
        printf(" 4. Вывести оба стека\n");
        printf("\nСтeки реализованные с помощью списка:\n");
        printf("\n 5. Добавить элемент в стек 1\n");
        printf("-5. Взять элемент из стека 1\n");
        printf(" 6. Добавить элемент в стек 2\n");
        printf("-6. Взять элемент из стека 2\n");
        printf(" 7. Отсортировать стеки и вывести результат\n");
        printf(" 8. Вывести оба стека\n");
        printf("\n 9. Сравнить производительность\n");
        printf("10. Информация\n");
        printf(" 0. Выход\n");
        printf("Выберите действие: ");
        if (scanf("%d", &choice) != 1)
            choice = 123;
        fgets(tmp, sizeof(tmp), stdin);

        printf("\033[0;36m");
        switch (choice)
        {
            case 1:
                printf("Введите значение для добавления в стек 1: ");
                if (scanf("%d", &data) != 1 || getc(stdin) != '\n')
                {
                    fgets(tmp, sizeof(tmp), stdin);
                    printf("Ошибка ввода\n");
                    break;
                }
                rc = arr_stack_push(arr_stack1, data);
                if (rc)
                    printf("Переполнение\n");
                break;
            case -1:
                rc = arr_stack_pop(arr_stack1, &x);
                if (rc)
                    printf("Стек пуст\n");
                else
                    printf("Элемент = %d\n", x);
                break;
            case 2:
                printf("Введите значение для добавления в стек 2: ");
                if (scanf("%d", &data) != 1 || getc(stdin) != '\n')
                {
                    fgets(tmp, sizeof(tmp), stdin);
                    printf("Ошибка ввода\n");
                    break;
                }
                rc = arr_stack_push(arr_stack2, data);
                if (rc)
                    printf("Переполнение\n");
                break;
            case -2:
                rc = arr_stack_pop(arr_stack2, &x);
                if (rc)
                    printf("Стек пуст\n");
                else
                    printf("Элемент = %d\n", x);
                break;
            case 3:
                if (arr_stack_is_empty(arr_stack1) ||
                    arr_stack_is_empty(arr_stack2))
                {
                    printf("Не все стеки введены\n");
                    break;
                }
                if (!arr_stack_can_be_merged(arr_stack1, arr_stack2))
                {
                    printf("Суммарный размер стеков превышает допустимый размер стека\n");
                    break;
                }
                arr_stack_make_empty(sorted_arr_stack);
                arr_stack_merge_sort(arr_stack1, arr_stack2, sorted_arr_stack);
                printf("Отсортированный стек:\n");
                arr_stack_print_stack(sorted_arr_stack);
                break;
            case 4:
                printf("Стек 1:\n");
                arr_stack_print_stack(arr_stack1);
                printf("Стек 2:\n");
                arr_stack_print_stack(arr_stack2);
                printf("\n");
                break;
            case 5:
                printf("Введите значение для добавления в стек 1: ");
                if (scanf("%d", &data) != 1 || getc(stdin) != '\n')
                {
                    fgets(tmp, sizeof(tmp), stdin);
                    printf("Ошибка ввода\n");
                    break;
                }
                list_stack1 = list_stack_push(list_stack1, data, freed_stack);
                break;
            case -5:
                rc = list_stack_pop(&list_stack1, &x, freed_stack);
                if (rc)
                    printf("Стек пуст\n");
                else
                    printf("Элемент = %d\n", x);
                break;
            case 6:
                printf("Введите значение для добавления в стек 2: ");
                if (scanf("%d", &data) != 1 || getc(stdin) != '\n')
                {
                    fgets(tmp, sizeof(tmp), stdin);
                    printf("Ошибка ввода\n");
                    break;
                }
                list_stack2 = list_stack_push(list_stack2, data, freed_stack);
                break;
            case -6:
                rc = list_stack_pop(&list_stack2, &x, freed_stack);
                if (rc)
                    printf("Стек пуст\n");
                else
                    printf("Элемент = %d\n", x);
                break;
            case 7:
                if (list_stack_is_empty(list_stack1) ||
                    list_stack_is_empty(list_stack2))
                {
                    printf("Не все стеки введены\n");
                    break;
                }
                list_stack_destroy(sorted_list_stack, freed_stack);
                sorted_list_stack = NULL;
                list_stack_merge_sort(&list_stack1, &list_stack2, &sorted_list_stack, freed_stack);
                printf("Отсортированный стек:\n");
                list_stack_print_stack(sorted_list_stack);
                break;
            case 8:
                printf("Стек 1:\n");
                list_stack_print_stack(list_stack1);
                printf("Стек 2:\n");
                list_stack_print_stack(list_stack2);
                printf("Массив освобожденных адрессов:\n");
                print_freed_stack(freed_stack);
                printf("\n");
                break;
            case 9:
                printf("Введите количество элементов для сортировки: ");
                if (scanf("%d", &cnt) != 1)
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                if (cnt <= 0 || cnt > 10000)
                {
                    printf("Ошибка диапазона\n");
                    break;
                }
                start_test(cnt);
                break;
            case 10:
                print_info();
                break;
            case 0:
                arr_stack_destroy(arr_stack1);
                arr_stack_destroy(arr_stack2);
                arr_stack_destroy(sorted_arr_stack);

                list_stack_destroy(list_stack1, freed_stack);
                list_stack_destroy(list_stack2, freed_stack);
                list_stack_destroy(sorted_list_stack, freed_stack);

                printf("Массив освобожденных адрессов:\n");
                print_freed_stack(freed_stack);
                printf("\n");
                
                destroy_freed_stack(freed_stack);
                return 0;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
                break;
        }
        printf("\033[0;37m");
    }

    return 0;
}
