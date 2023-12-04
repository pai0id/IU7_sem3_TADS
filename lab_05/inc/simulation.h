#ifndef SIM_H
#define SIM_H

#include <stdio.h>
#include <stdbool.h>

typedef enum types {T1, T2} types;

int simulate_arr(int num_req, const double t1_in, const double t1_out, const double t2_in, const double t2_out, const double t3_in, const double t3_out, bool print);

int simulate_arr_stat(int num_req, const double t1_s, const double t1_f, const double t2_s, const double t2_f, const double t3_s, const double t3_f, bool print);

int simulate_list(int num_req, const double t1_in, const double t1_out, const double t2_in, const double t2_out, const double t3_in, const double t3_out, bool print);

#endif
