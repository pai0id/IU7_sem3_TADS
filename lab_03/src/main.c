#include "mtr_io.h"
#include "mtr_alloc.h"
#include "mtr_op.h"
#include "mtr.h"
#include "UI.h"
#include "controls.h"
#include "err.h"
#include <string.h>

int main(void)
{
    int rc = OK;
    mtr_t *mtr = NULL;
    vector_t *v = NULL;
    while (rc != ERR_EXIT)
    {
        print_actions();
        rc = get_command(&mtr, &v);
        prn_msg(rc);
    }
    if (mtr != NULL)
        matrix_free(mtr);
    if (v != NULL)
        vector_free(v);
    return OK;
}
