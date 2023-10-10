#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdio.h>
#include "book.h"
#include "book_arr.h"
#include "UI.h"
#include "research.h"

typedef enum {EXIT, READ, ADD, DEL, PRINT_STRUCT, PRINT_STRUCT_BY_KEY,
 PRINT_KEY, SORT_STRUCT, SORT_KEY, SPEC, RESEARCH, LOAD, INFO} actions;

int get_command(struct book_t *books, size_t *n, size_t *id_arr);

#endif
