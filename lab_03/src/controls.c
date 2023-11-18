#include "controls.h"
#include "mtr_io.h"
#include "mtr_alloc.h"
#include "mtr_op.h"
#include "UI.h"
#include "research.h"
#include <string.h>
#include <math.h>

int str_read(FILE *f, char *str, size_t size, size_t max_size)
{
    size_t len;

    if (!fgets(str, size, f))
        return ERR_IO;
    len = strlen(str);
    if (len && str[len - 1] == '\n')
    {
        str[len - 1] = 0;
        len--;
    }
    if (!len || len > max_size)
        return ERR_RANGE;
    return OK;
}

size_t cnt_nz(double **data, size_t n, size_t m)
{
    size_t cnt = 0;
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (fabs(data[i][j]) > EPS)
                cnt++;
    return cnt;
}

int get_command(mtr_t **mtr, vector_t **v)
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

    case READ_MTR_F: ;
        if (*mtr != NULL)
        {
            matrix_free(*mtr);
            *mtr = NULL;
        }
        char filename[20];
        FILE *f;
        printf("Введите название файла: ");
        rc = str_read(stdin, filename, sizeof(filename), 20);
        if (rc)
            return rc;
        f = fopen(filename, "r");
        if (f == NULL)
            return ERR_NO_FILE;
        rc = matrix_read(f, mtr);
        fclose(f);
        if (rc)
        {
            *mtr = NULL;
            return rc;
        }
        break;

    case READ_MTR_IN: ;
        if (*mtr != NULL)
        {
            matrix_free(*mtr);
            *mtr = NULL;
        }
        rc = matrix_read(stdin, mtr);
        if (rc)
        {
            *mtr = NULL;
            return rc;
        }
        break;

    case READ_V_F: ;
        if (*v != NULL)
        {
            vector_free(*v);
            *v = NULL;
        }
        char file[20];
        FILE *f1;
        printf("Введите название файла: ");
        rc = str_read(stdin, file, sizeof(file), 20);
        if (rc)
            return rc;
        f1 = fopen(file, "r");
        if (f1 == NULL)
            return ERR_NO_FILE;
        rc = vector_read(f1, v);
        fclose(f1);
        if (rc)
        {
            *v = NULL;
            return rc;
        }
        break;

    case READ_V_IN:
        if (*v != NULL)
        {
            vector_free(*v);
            *v = NULL;
        }
        rc = vector_read(stdin, v);
        if (rc)
        {
            *v = NULL;
            return rc;
        }
        break;

    case PRINT_MTR:
        if (*mtr != NULL)
        {
            printf("Матрица:\n");
            matrix_print(stdout, *mtr);
        }
        else
            return ERR_NO_MTR;
        break;

    case PRINT_V:
        if (*v != NULL)
        {
            printf("Вектор-столбец:\n");
            vector_print(stdout, *v);
        }
        else
            return ERR_NO_V;
        break;

    case MULT:
        if (*mtr != NULL && *v != NULL)
        {
            vector_t *res;
            rc = matrix_mult(*mtr, *v, &res);
            if (!rc)
            {
                vector_print(stdout, res);
                vector_free(res);
            }
            else
                return rc;
        }
        else if (*mtr == NULL)
            return ERR_NO_MTR;
        else
            return ERR_NO_V;
        break;

    case OLD_MULT:
        if (*mtr != NULL && *v != NULL)
        {
            double **old_mtr = transform_mtr(*mtr);
            if (old_mtr == NULL)
                return ERR_MEM;
            double **old_v = transform_vector(*v);
            if (old_v == NULL)
            {
                old_matrix_free(old_mtr, (*mtr)->rows);
                return ERR_MEM;
            }
            double **res;
            size_t nres, mres;
            rc = old_matrix_mult(old_mtr, (*mtr)->rows, (*mtr)->cols, old_v, (*v)->rows, 1, &res, &nres, &mres);
            if (!rc)
                old_matrix_print_coord(stdout, res, nres, mres, cnt_nz(res, nres, mres));
            old_matrix_free(old_mtr, (*mtr)->rows);
            old_matrix_free(old_v, (*v)->rows);
            return rc;
        }
        else if (*mtr == NULL)
            return ERR_NO_MTR;
        else
            return ERR_NO_V;
        break;

    case CMP: ;
        rc = cmp_methods(*mtr, *v);
        return rc;
        break;

    case PRINT_MTR_F:
        if (*mtr != NULL)
        {
            char filename[20];
            FILE *f;
            printf("Введите название файла: ");
            rc = str_read(stdin, filename, sizeof(filename), 20);
            if (rc)
                return rc;
            f = fopen(filename, "w");
            if (f == NULL)
                return ERR_NO_FILE;
            matrix_print(f, *mtr);
        }
        else
            return ERR_NO_MTR;
        break;

    case PRINT_V_F: ;
        if (*v != NULL)
        {
            char filename[20];
            FILE *f;
            printf("Введите название файла: ");
            rc = str_read(stdin, filename, sizeof(filename), 20);
            if (rc)
                return rc;
            f = fopen(filename, "w");
            if (f == NULL)
                return ERR_NO_FILE;
            vector_print(f, *v);
        }
        else
            return ERR_NO_V;
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

