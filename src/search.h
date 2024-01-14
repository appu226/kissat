#ifndef _search_h_INCLUDED
#define _search_h_INCLUDED

struct kissat;

int kissat_search (struct kissat *);
int kissat_search_for_variable_elimination (struct kissat *solver, int* idx_array, unsigned idx_array_size);

#endif
