#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdio.h>
#include "mtr.h"

typedef enum {EXIT, READ_MTR_F, READ_MTR_IN, READ_V_F, READ_V_IN, PRINT_MTR,
 PRINT_V, MULT, OLD_MULT, CMP, PRINT_MTR_F, PRINT_V_F, INFO} actions;

int get_command(mtr_t **mtr, vector_t **v);

#endif
