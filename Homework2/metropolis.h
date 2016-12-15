//
//  metropolis.h
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#ifndef metropolis_h
#define metropolis_h

#include <gsl/gsl_rng.h>
#include "BodyCenteredCubicLattice.h"
#include "BodyCenteredCubicLatticeRandom.h"

typedef struct MetropolisOptionsTag{
    unsigned int n_iterations;
    unsigned int auto_corr_k_max;
    unsigned int block_avg_block_size;
    double temperature;
} MetropolisOptions;
/*
const MetropolisOptions MetropolisDefaultOptions = {
    .n_iterations = 100,
    .auto_corr_k_max = 100,
    .block_avg_block_size = 100,
    .temperature = 100
};
*/
typedef struct MetropolisDataElementTag{
    double mean;
    double s_autocorrelation;
    double s_block_average;
    double std_autocorrelation;
    double std_block_average;
} MetropolisDataElement;

typedef struct {
    MetropolisDataElement energy;
    MetropolisDataElement long_range_order;
    MetropolisDataElement short_range_order;
    MetropolisDataElement heat_capacity;
} MetropolisOutput;

//Runs the Metropolis algorithm using a BodyCenteredCubicLattice l for nbr_of_iters iterations with temperature T. To calculoate the statistical inefficiency s the maximum index for the autocorrelation function k_max and block size B are used. The results are saved in the ResultStructtruct res.
void metropolis(BodyCenteredCubicLattice *l,
                              MetropolisOptions options,MetropolisOutput *output);

void MetropolisDataElement_fprintf(FILE*file,MetropolisDataElement e,
                                   char* var_name);

#endif /* metropolis_h */
