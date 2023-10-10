#include <string.h>
#include "book.h"
#include "err.h"

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

int read_book(FILE *f, struct book_t *pbook)
{
    char buf_surname[SUR_SIZE + 1];
    char buf_title[TITLE_SIZE + 1];
    char buf_publisher[PUBLISHER_SIZE + 1];
    int page_cnt;
    lit_types type;
    char tmp[2];
    int rc;

    if (f == stdin)
        printf("Введите фамилию автора: ");
    rc = str_read(f, buf_surname, sizeof(buf_surname), SUR_SIZE);
    if (rc)
        return rc;
    
    if (f == stdin)
        printf("Введите название: ");
    rc = str_read(f, buf_title, sizeof(buf_title), TITLE_SIZE);
    if (rc)
        return rc;

    if (f == stdin)
        printf("Введите издательство: ");
    rc = str_read(f, buf_publisher, sizeof(buf_publisher), PUBLISHER_SIZE);
    if (rc)
        return rc;

    if (f == stdin)
        printf("Введите количество страниц: ");
    if (fscanf(f, "%d", &page_cnt) != 1)
        return ERR_IO;
    if (page_cnt <= 0)
        return ERR_RANGE;
    fgets(tmp, sizeof(tmp), f);

    if (f == stdin)
    {
        printf("Введите вид литературы (1: техническая 2: художественная 3: детская): ");
        if (fscanf(f, "%u", &type) != 1)
            return ERR_IO;
        if (type > CHILD)
            return ERR_RANGE;
        fgets(tmp, sizeof(tmp), f);
    }
    else
    {
        char buf_type[TYPE_SIZE + 1];
        rc = str_read(f, buf_type, sizeof(buf_type), TYPE_SIZE);
        if (rc)
            return rc;
        if (strcmp(buf_type, "technical") == 0)
            type = ENG;
        else if (strcmp(buf_type, "fiction") == 0)
            type = FICTION;
        else if (strcmp(buf_type, "children") == 0)
            type = CHILD;
        else
            return ERR_IO;
    }

    if (type == ENG)
    {
        char buf_industry[IND_SIZE + 1];
        eng_lang lang;
        int year;

        if (f == stdin)
            printf("Введите отрасль: ");
        else
            fgets(tmp, sizeof(tmp), f);
        rc = str_read(f, buf_industry, sizeof(buf_industry), IND_SIZE);
        if (rc)
            return rc;

        if (f == stdin)
        {
            printf("Введите язык литературы (1: отечественная 2: переводная): ");
            if (fscanf(f, "%u", &lang) != 1)
                return ERR_IO;
            if (lang > TRANSLATED)
                return ERR_RANGE;
            fgets(tmp, sizeof(tmp), f);
        }
        else
        {
            char buf_lang[LANG_SIZE + 1];
            rc = str_read(f, buf_lang, sizeof(buf_lang), LANG_SIZE);
            if (rc)
                return rc;
            if (strcmp(buf_lang, "eng") == 0)
                lang = TRANSLATED;
            else if (strcmp(buf_lang, "rus") == 0)
                lang = RUS;
            else
                return ERR_IO;
        }

        if (f == stdin)
            printf("Введите год издания: ");
        if (fscanf(f, "%d", &year) != 1)
            return ERR_IO;
        if (year <= 0)
            return ERR_RANGE;
        fgets(tmp, sizeof(tmp), f);

        strcpy((pbook->chars).eng.industry, buf_industry);
        (pbook->chars).eng.lang = lang;
        (pbook->chars).eng.year = year;
    }
    else if (type == FICTION)
    {
        fict_types type;

        if (f == stdin)
        {
            printf("Введите вид художественной литературы (1: роман, 2: пьеса, 3: поэзия): ");
            if (fscanf(f, "%u", &type) != 1)
                return ERR_IO;
            if (type > POETRY)
                return ERR_RANGE;
            fgets(tmp, sizeof(tmp), f);
        }
        else
        {
            char buf_type_f[TYPE_SIZE + 1];
            rc = str_read(f, buf_type_f, sizeof(buf_type_f), TYPE_SIZE);
            if (rc)
                return rc;
            if (strcmp(buf_type_f, "novel") == 0)
                type = NOVEL;
            else if (strcmp(buf_type_f, "play") == 0)
                type = PLAY;
            else if (strcmp(buf_type_f, "poetry") == 0)
                type = POETRY;
            else
                return ERR_IO;
        }

        (pbook->chars).fict.type = type;
    }
    else if (type == CHILD)
    {
        int min_age;
        child_types type;

        if (f == stdin)
            printf("Введите минимальный возраст: ");
        if (fscanf(f, "%d", &min_age) != 1)
            return ERR_IO;
        if (min_age < 0)
            return ERR_RANGE;
        fgets(tmp, sizeof(tmp), f);

        if (f == stdin)
        {
            printf("Введите вид детской литературы (1: сказки, 2: стихи): ");
            if (fscanf(f, "%u", &type) != 1)
                return ERR_IO;
            if (type > POEMS)
                return ERR_RANGE;
            fgets(tmp, sizeof(tmp), f);
        }
        else
        {
            char buf_type[TYPE_SIZE + 1];
            rc = str_read(f, buf_type, sizeof(buf_type), TYPE_SIZE);
            fgets(tmp, sizeof(tmp), f);
            if (rc)
                return rc;
            if (strcmp(buf_type, "fairytale") == 0)
                type = TALES;
            else if (strcmp(buf_type, "poem") == 0)
                type = POEMS;
            else
                return ERR_IO;
        }

        (pbook->chars).child.min_age = min_age;
        (pbook->chars).child.type = type;
    }
    if (f != stdin)
        fgets(tmp, sizeof(tmp), f);

    strcpy(pbook->surname, buf_surname);
    strcpy(pbook->title, buf_title);
    strcpy(pbook->publisher, buf_publisher);
    pbook->page_cnt = page_cnt;
    pbook->type = type;
    return OK;
}

void print_book_column(FILE *f, struct book_t *pbook)
{
    fprintf(f, "%s\n", pbook->surname);
    fprintf(f, "%s\n", pbook->title);
    fprintf(f, "%s\n", pbook->publisher);
    fprintf(f, "%d\n", pbook->page_cnt);
    switch (pbook->type)
    {
    case ENG:
        fprintf(f, "technical\n");
        fprintf(f, "%s\n", (pbook->chars).eng.industry);
        if ((pbook->chars).eng.lang == TRANSLATED)
            fprintf(f, "eng\n");
        else if ((pbook->chars).eng.lang == RUS)
            fprintf(f, "rus\n");
        fprintf(f, "%d\n", (pbook->chars).eng.year);
        break;
    
    case FICTION:
        fprintf(f, "fiction\n");
        if ((pbook->chars).fict.type == NOVEL)
            fprintf(f, "novel\n");
        else if ((pbook->chars).fict.type == PLAY)
            fprintf(f, "play\n");
        else if ((pbook->chars).fict.type == POETRY)
            fprintf(f, "poetry\n");
        break;

    case CHILD:
        fprintf(f, "children\n");
        fprintf(f, "%d\n", (pbook->chars).child.min_age);
        if ((pbook->chars).child.type == TALES)
            fprintf(f, "fairytale\n");
        else if ((pbook->chars).child.type == POEMS)
            fprintf(f, "poem\n");
        break;

    default:
        break;
    }
    fprintf(f, "\n");
}

void print_book_line(FILE *f, struct book_t *pbook)
{
    fprintf(f, "%20s|", pbook->surname);
    fprintf(f, "%24s|", pbook->title);
    fprintf(f, "%18s|", pbook->publisher);
    fprintf(f, "%16d|", pbook->page_cnt);
    switch (pbook->type)
    {
    case ENG:
        fprintf(f, "    technical   | ");
        fprintf(f, "%s - ", (pbook->chars).eng.industry);
        if ((pbook->chars).eng.lang == TRANSLATED)
            fprintf(f, "eng - ");
        else if ((pbook->chars).eng.lang == RUS)
            fprintf(f, "rus - ");
        fprintf(f, "%d", (pbook->chars).eng.year);
        break;
    
    case FICTION:
        fprintf(f, "     fiction    | ");
        if ((pbook->chars).fict.type == NOVEL)
            fprintf(f, "novel");
        else if ((pbook->chars).fict.type == PLAY)
            fprintf(f, "play");
        else if ((pbook->chars).fict.type == POETRY)
            fprintf(f, "poetry");
        break;

    case CHILD:
        fprintf(f, "    children    | ");
        fprintf(f, "%d - ", (pbook->chars).child.min_age);
        if ((pbook->chars).child.type == TALES)
            fprintf(f, "fairytale");
        else if ((pbook->chars).child.type == POEMS)
            fprintf(f, "poem");
        break;

    default:
        break;
    }
    fprintf(f, "\n");
}

int book_cmp_by_page_cnt(struct book_t *l, struct book_t *r)
{
    return l->page_cnt - r->page_cnt;
}
