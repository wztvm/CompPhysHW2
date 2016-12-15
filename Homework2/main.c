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
        .n_iterations = 100000,
        .auto_corr_k_max = 100,
        .block_avg_block_size = 100,
        .temperature = temperature
    };
    return options;
}

int main(int argc, const char * argv[]) {
    BodyCenteredCubicLattice * l = bcc_alloc(10);
    bcc_init(l);
    
    bcc_type_count_prinf(l,NodeTypeCopper,NodeTypeZinc);
    
    // Setting up random number generation
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *rng = gsl_rng_alloc(T);
    gsl_rng_set(rng,time(NULL));
    for(int a = 0;a<5000;a++){
    node_swap_types(bcc_get_node_random(l, rng),
                        bcc_get_node_random(l, rng));
    bcc_type_count_prinf(l,NodeTypeCopper,NodeTypeZinc);
    }
    
    MetropolisOutput *output = malloc(sizeof(*output));
    for(double temp=10000.0;temp<=100000.0;temp+=10000.0){
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
