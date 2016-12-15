//
//  main.c
//  Homework2
//
//  Created by David Dagson on 2016-12-05.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "BodyCenteredCubicLattice.h"
#include "metropolis.h"
#include <time.h>

MetropolisOptions getMetropolisOptions(double temperature){
    const MetropolisOptions options = {
        .n_iterations = 10000,
        .auto_corr_k_max = 3000,
        .block_avg_block_size = 3000,
        .temperature = temperature
    };
    return options;
}

int main(int argc, const char * argv[]) {
    BodyCenteredCubicLattice * l = bcc_alloc(10);
    bcc_init(l);
    
    
    // Setting up random number generation
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *rng = gsl_rng_alloc(T);
    gsl_rng_set(rng,time(NULL));
    
    MetropolisOutput *output = malloc(sizeof(*output));
    for(double temp=500.0;temp<=1000.0;temp+=100.0){
        printf("\nMetropolis - Starting point\n");
        double E = bcc_energy(l, NodeTypeCopper, NodeTypeZinc, -436.0, -113.0, -294.0);
        printf("%0.5f\n",E);
        bcc_type_count_prinf(l,NodeTypeCopper,NodeTypeZinc);
        
        MetropolisOptions options = getMetropolisOptions(temp);
        metropolis(l,options,output);
        bcc_type_count_prinf(l,NodeTypeCopper,NodeTypeZinc);
    
        MetropolisDataElement_fprintf(stdout, output->energy, "Energy");
        MetropolisDataElement_fprintf(stdout, output->long_range_order, "Long range order");
        MetropolisDataElement_fprintf(stdout, output->short_range_order, "Short range order");
        MetropolisDataElement_fprintf(stdout, output->heat_capacity, "Heat Capacity");
    }
    bcc_free(l);
    return 0;
}
