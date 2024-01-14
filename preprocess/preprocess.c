#include "../src/kissat.h"
#include "../src/eliminate.h"
#include "../src/dump.h"

#include <stdio.h>

int main()
{
    printf("[INFO] Starting kissat_preprocess.\n"); fflush(stdout);

    kissat* solver = kissat_init();

    // (~x V y) AND (~x V z) AND (x V ~y V ~z) AND (x V w V u) AND (~x V ~z V w) AND (~y V ~u V z)
    int x = 1, y = 2, z = 3, w = 4, u = 5;
    int clauses[] = {
        -x, y, 0,    -x, z, 0,   x, -y, -z, 0,      x, w, u, 0,    -x, -z, w, 0,      -y, -u, z, 0
    };
    unsigned clausessize = sizeof(clauses) / sizeof(int);
    for (unsigned i = 0; i < clausessize; ++i)
        kissat_add(solver, clauses[i]);

    int variables_to_eliminate[] = { x };
    kissat_eliminate_variables(
        solver, 
        variables_to_eliminate, 
        sizeof(variables_to_eliminate)/sizeof(int));

    unsigned result_size;
    int *cnf = kissat_dump_cnf(solver, &result_size);
    for (int *cnf_it = cnf, *cnf_end = (cnf + result_size); cnf_it < cnf_end; ++cnf_it)
    {
        printf("%d ", (*cnf_it));
        if (*cnf_it == 0)
            printf("\n");
    }
    // kissat_solve(solver);
    kissat_release(solver);
    printf("[INFO] Finished kissat_preprocess.\n"); fflush(stdout);
    return 0;
}