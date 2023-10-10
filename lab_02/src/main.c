#include <stdio.h>
#include "book.h"
#include "book_arr.h"
#include "controls.h"
#include "err.h"
#include "UI.h"

int main(void)
{
    struct book_t books[N];
    size_t n = 0;
    size_t id_arr[N];
    int rc = OK;
    while (rc != ERR_EXIT)
    {
        print_actions();
        rc = get_command(books, &n, id_arr);
        prn_msg(rc);
    }
    return OK;
}

