#include "err.h"
#include <stdio.h>

void print_err_msg(int rc)
{
    switch (rc)
    {
    case OK:
        break;

    case ERR_IO:
        printf("ERROR: Incorrect input\n");
        break;

    case ERR_RANGE_EXP:
        printf("ERROR: Range error occured with exponent\n");
        break;

    case ERR_RANGE_MANT:
        printf("ERROR: Range error occured with mantissa\n");
        break;
    
    default:
        printf("ERROR: An unknown error occured\n");
        break;
    }
}
