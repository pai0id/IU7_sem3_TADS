#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"
#include "tree.h"
#include "research.h"

int main()
{
    int choice;
    char tmp[7];

    struct Node* root = NULL;
    char input[100];
    char inp;

    while (1)
    {
        print_actions();
        printf("Выберите действие: ");
        if (scanf("%d", &choice) != 1)
            choice = 123;
        fgets(tmp, sizeof(tmp), stdin);

        switch (choice)
        {
            case 1:
                printf("Введите строку: ");
                scanf("%s", input);
                if (strlen(input) == 0)
                {
                    printf("Пустая строка\n");
                    break;
                }
                for (int i = 0; input[i] != '\0'; i++)
                    root = insert(root, input[i]);

                break;
            case 2:
                printf("Введите символ: ");
                if (scanf("%c", &inp) != 1)
                {
                    printf("Символ не введен");
                    break;
                }

                root = insert(root, inp);

                break;
            case 3:
                printf("Введите символ: ");
                if (scanf("%c", &inp) != 1)
                {
                    printf("Символ не введен");
                    break;
                }

                root = del_node(root, inp);

                break;
            case 4:
                if (!root)
                    printf("Пустое дерево");
                else
                    in_order_traversal(root);
                printf("\n");

                break;
            case 5:
                if (!root)
                    printf("Пустое дерево");
                else
                    print_tree(root, NULL, 0);
                printf("\n");

                break;
            case 6:
                if (!root)
                {
                    printf("Пустое дерево\n");
                    break;
                }
                else
                {
                    printf("Введите символ: ");
                    if (scanf("%c", &inp) != 1)
                    {
                        printf("Символ не введен");
                        break;
                    }
                    struct Node* found = search(root, inp);
                    print_tree(found, NULL, 0);
                    printf("\n");
                }

                break;
            case 7:
                root = del_rep_nodes(root);

                break;
            case 8:
                cmp_del_rep();
                break;
            case 9:
                cmp_find();
                break;
            case 10:
                print_info();

                break;
            case -1:
                free_tree(root);
                root = NULL;
                break;
            case 0:
                free_tree(root);
                return 0;
                break;
        }
    }

    return 0;
}
