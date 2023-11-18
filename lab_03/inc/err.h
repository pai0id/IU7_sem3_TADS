#ifndef ERR_H
#define ERR_H

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_MEM 3
#define ERR_ARGS 4
#define ERR_NO_FILE 5
#define ERR_EXIT 6
#define ERR_WRONG_COMMAND 7
#define ERR_NO_MTR 8
#define ERR_NO_V 9

#define EPS 1e-7

void prn_msg(int rc);

#endif
