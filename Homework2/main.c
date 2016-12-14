//
//  main.c
//  Homework2
//
//  Created by David Dagson on 2016-12-05.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <time.h>

#include "BodyCenteredCubicLattice.h"
#include "BodyCenteredCubicLatticeRandom.h"
#include "LatticeNode.h"







int main(int argc, const char * argv[]) {
    
    BodyCenteredCubicLattice * l = bcc_alloc(3);
    bcc_init(l);
    
    gsl_rng_env_setup();
    const gsl_rng_type *T= gsl_rng_default;
    gsl_rng *rng = gsl_rng_alloc(T);
    gsl_rng_set(rng,time(NULL));
    
    LatticeNode *n = bcc_get_node_random(l, rng);
    LatticeNode *m = bcc_get_node_random(l, rng);
    node_swap_types(n,m);
    
    double P = bcc_long_range_order(l,NodeTypeCopper);
    
    double r = bcc_short_range_order(n);
    
    double r_avg = bcc_average_short_range_order(l);
    
    double E_cu_cu = -436.0; // meV
    double E_zn_zn = -113.0;
    double E_cu_zn = -294.0;
    
    double energy = bcc_energy(l,NodeTypeCopper,NodeTypeZinc,
                               E_cu_cu,E_zn_zn,E_cu_zn);
    
    printf("Lattice energy: %f\n",energy);
    printf("Short range order: %f\n",r);
    printf("Average short range order  %f\n", r_avg);
    printf("Long range order %f\n",P);
    
    bcc_free(l);
    return 0;
}
