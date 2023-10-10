#include "controls.h"

int get_command(struct book_t *books, size_t *n, size_t *id_arr)
{
    int command, rc = OK;
    char tmp[7];

    printf("Команда: ");
    if (scanf("%d", &command) != 1)
    {
        fgets(tmp, sizeof(tmp), stdin);
        return ERR_IO;
    }
    fgets(tmp, sizeof(tmp), stdin);
    switch (command)
    {
    case EXIT:
        return ERR_EXIT;
        break;

    case READ: ;
        char filename[20];
        FILE *f;
        printf("Введите название файла: ");
        rc = str_read(stdin, filename, sizeof(filename), 20);
        if (rc)
            return rc;
        f = fopen(filename, "r");
        if (f == NULL)
            return ERR_NO_FILE;
        rc = read_arr(f, books, n);
        fclose(f);
        if (rc)
            return rc;
        create_id_cnt_pages_arr(*n, id_arr);
        break;

    case ADD: ;
        struct book_t book;
        printf("Введите структуру:\n");
        rc = read_book(stdin, &book);
        if (rc)
            return rc;
        rc = add_book(&book, books, n, id_arr);
        if (rc)
            return rc;
        break;

    case DEL: ;
        size_t i;
        printf("Введите индекс: ");
        if (scanf("%lu", &i) != 1)
            return ERR_IO;
        fgets(tmp, sizeof(tmp), stdin);
        remove_book(i, books, n, id_arr);
        break;

    case PRINT_STRUCT:
        print_table_header();
        print_arr_line(stdout, books, *n);
        break;

    case PRINT_STRUCT_BY_KEY:
        print_table_header();
        print_arr_by_ids_line(stdout, books, *n, id_arr);
        break;

    case PRINT_KEY:
        print_table_ids_header();
        print_arr_id_line(stdout, books, *n, id_arr);
        break;

    case SORT_STRUCT:
        bubble_sort_book_arr(books, *n);
        create_id_cnt_pages_arr(*n, id_arr);
        break;

    case SORT_KEY:
        bubble_sort_book_id_arr(books, *n, id_arr);
        break;

    case SPEC: ;
        char str[20];
        printf("Введите фамилию: ");
        rc = str_read(stdin, str, sizeof(str), 20);
        if (rc)
            return rc;
        print_table_header();
        rc = print_spec(books, *n, str);
        if (rc)
            return rc;
        break;

    case RESEARCH:
        run_tests(books, *n, id_arr);
        break;

    case LOAD: ;
        char filenam[20];
        FILE *f_out;
        printf("Введите название файла: ");
        rc = str_read(stdin, filenam, sizeof(filenam), 20);
        if (rc)
            return rc;
        f_out = fopen(filenam, "w");
        if (f_out == NULL)
            return ERR_NO_FILE;
        print_arr_column(f_out, books, *n);
        fclose(f_out);
        break;

    case INFO:
        print_info();
        break;
    
    default:
        return ERR_WRONG_COMMAND;
        break;
    }
    return OK;
}

