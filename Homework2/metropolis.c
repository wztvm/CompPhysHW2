//
//  metropolis.c
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#include "metropolis.h"
#include <gsl/gsl_rng.h>
#include <time.h>
#include "statistical_util.h"

#define E_CuCu -436.0
#define E_ZnZn -113.0
#define E_CuZn -294.0

/* Runs the Metropolis algorithm using a BodyCenteredCubicLattice l 
 *
 * Options
 *      unsigned int n_iterations; // number of iterations
 *      double temperature; // temperature kept by the algorithm
 *      unsigned int auto_corr_k_max; // cutoff for autocorrelation index
 *      unsigned int block_avg_block_size; // size of block in block average
 *
 * Output
 *      energy
 *      long_range_order
 *      short_range_order
 *      heat_capacity
 *
 * All output are returned with 
 *      double mean;
 *      double s_autocorrelation;
 *      double std_autocorrelation;
 *      double s_block_average;
 *      double std_block;
 */
void metropolis(BodyCenteredCubicLattice *l,
                              MetropolisOptions o, MetropolisOutput * output) {
    
    //Declares arrays to hold E, P and r
    double *E = malloc(o.n_iterations * sizeof(double));
    double *P = malloc(o.n_iterations * sizeof(double));
    double *r = malloc(o.n_iterations * sizeof(double));
    
    //Declares variables to be used as temporary energy values
    double energy_old;
    double energy_new;
    double delta_E;
    
    // Declares variable used for temporary storage
    double probability_ratio;
    
    //Declares latticenodes to be used as random nodes
    LatticeNode *r_node1;
    LatticeNode *r_node2;
    
    //Initializes E, P and r
    E[0] = bcc_energy(l, NodeTypeCopper, NodeTypeZinc, E_CuCu, E_ZnZn, E_CuZn);
    P[0] = bcc_long_range_order(l, NodeTypeCopper);
    r[0] = bcc_average_short_range_order(l);
    
    // Setting up random number generation
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *rng = gsl_rng_alloc(T);
    gsl_rng_set(rng,time(NULL));
    
    for (unsigned int i = 1; i < o.n_iterations; i++) {
        if(i%10000==0){
            bcc_type_count_prinf(l,NodeTypeCopper,NodeTypeZinc);
        }
        energy_old = E[i - 1];
        
        //Metropolis step 1
        r_node1 = bcc_get_node_random(l, rng);
        r_node2 = bcc_get_node_random(l, rng);
        node_swap_types(r_node1, r_node2);
        
        //Metropolis step 2
        energy_new = bcc_energy(l, NodeTypeCopper, NodeTypeZinc,
                                E_CuCu, E_ZnZn, E_CuZn);
        delta_E = energy_new - energy_old;
        
        //Metropolis step 3
        probability_ratio = get_boltzmann_dist_frac(delta_E, o.temperature);
        if ((delta_E <= 0) || ( probability_ratio >= gsl_rng_uniform(rng))) {
            E[i] = energy_new;
        } else {
            E[i] = energy_old;
            node_swap_types(r_node1, r_node2);
        }
        
        //Computes P and r
        P[i] = bcc_long_range_order(l, NodeTypeCopper);
        r[i] = bcc_average_short_range_order(l);
    }
    
    double n_iter = o.n_iterations;
    
    MetropolisDataElement energy = {
        .mean = mean(E, n_iter),
        .s_autocorrelation = get_s_autocorr(E,n_iter,
                                              o.auto_corr_k_max),
        .s_block_average = get_s_block_averaging(E, n_iter,
                                                   o.block_avg_block_size),
        .std_autocorrelation
            = energy.s_autocorrelation / n_iter* var(E, n_iter),
        .std_block_average
            = energy.s_block_average / n_iter * var(E, n_iter)
    };
    
    MetropolisDataElement long_range_order = {
        .mean = mean(P, n_iter),
        .s_autocorrelation = get_s_autocorr(P,n_iter,
                                            o.auto_corr_k_max),
        .s_block_average = get_s_block_averaging(P, n_iter,
                                                 o.block_avg_block_size),
        .std_autocorrelation
        = long_range_order.s_autocorrelation / n_iter * var(P, n_iter),
        .std_block_average
        = long_range_order.s_block_average / n_iter * var(P, n_iter)
    };

    MetropolisDataElement short_range_order = {
        .mean = mean(r, n_iter),
        .s_autocorrelation = get_s_autocorr(r,n_iter,
                                            o.auto_corr_k_max),
        .s_block_average = get_s_block_averaging(r, n_iter,
                                                 o.block_avg_block_size),
        .std_autocorrelation
        = short_range_order.s_autocorrelation / n_iter * var(r, n_iter),
        .std_block_average
        = short_range_order.s_block_average / n_iter * var(r, n_iter)
    };

    MetropolisDataElement heat_capacity = {
        .mean = get_C(E, o.n_iterations, o.temperature),
        .s_autocorrelation = 0.0,
        .s_block_average = 0.0,
        .std_autocorrelation = 0.0,
        .std_block_average= 0.0
    };
    
    output->energy = energy;
    output->long_range_order = long_range_order;
    output->short_range_order = short_range_order;
    output->heat_capacity = heat_capacity;
    
    //Frees arrays
    free(E); E = NULL;
    free(P); P = NULL;
    free(r); r = NULL;
}

void MetropolisDataElement_fprintf(FILE*file,MetropolisDataElement e,
                                   char* var_name){
    fprintf(file, "(%s): \n\tmean: %0.4f, \n\ts_auto_corr: %0.4f, \n\tstd_auto_corr: %0.4f, "
            "\n\ts_block_average: %0.4f, \n\tstd_block_average: %0.4f \n",
            var_name, e.mean,
            e.s_autocorrelation,e.std_autocorrelation,
            e.s_block_average,e.std_block_average);
}
