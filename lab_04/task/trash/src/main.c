#include <stdio.h>

int main()
{
    Stack stack1, stack2, sortedStack;
    initStack(&stack1);
    initStack(&stack2);
    initStack(&sortedStack);

    int num1, num2;

    printf("Введите числа для первого стека (введите 0 для завершения):\n");
    do {
        scanf("%d", &num1);
        if (num1 != 0) {
            push(&stack1, num1);
        }
    } while (num1 != 0);

    printf("Введите числа для второго стека (введите 0 для завершения):\n");
    do {
        scanf("%d", &num2);
        if (num2 != 0) {
            push(&stack2, num2);
        }
    } while (num2 != 0);

    sortStack(&stack1, &sortedStack);
    sortStack(&stack2, &sortedStack);

    printf("Отсортированный стек:\n");
    while (!isEmpty(&sortedStack)) {
        printf("%d ", pop(&sortedStack));
    }

    return 0;
}
