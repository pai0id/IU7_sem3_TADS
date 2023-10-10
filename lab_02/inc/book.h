#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>

#define SUR_SIZE 50
#define TITLE_SIZE 50
#define PUBLISHER_SIZE 50
#define IND_SIZE 50

#define TYPE_SIZE 9
#define LANG_SIZE 3

typedef enum {ENG = 1,  FICTION, CHILD} lit_types;

typedef enum {RUS = 1, TRANSLATED} eng_lang;

struct eng_chars_t
{
    char industry[IND_SIZE + 1];
    eng_lang lang;
    int year;
};

typedef enum {NOVEL = 1, PLAY, POETRY} fict_types;

struct fict_chars_t
{
    fict_types type;
};

typedef enum {TALES = 1, POEMS} child_types;

struct child_chars_t
{
    int min_age;
    child_types type;
};

struct book_t
{
    char surname[SUR_SIZE + 1];
    char title[TITLE_SIZE + 1];
    char publisher[PUBLISHER_SIZE + 1];
    int page_cnt;
    lit_types type;
    union type_chars_u
    {
        struct eng_chars_t eng;
        struct fict_chars_t fict;
        struct child_chars_t child;
    } chars;
};

#include <string.h>
#include "book.h"
#include "err.h"

int str_read(FILE *f, char *str, size_t size, size_t max_size);

int read_book(FILE *f, struct book_t *pbook);

void print_book_column(FILE *f, struct book_t *pbook);

void print_book_line(FILE *f, struct book_t *pbook);

int book_cmp_by_page_cnt(struct book_t *l, struct book_t *r);

#endif
