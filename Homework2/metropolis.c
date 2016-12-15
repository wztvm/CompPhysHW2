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
#include <math.h>
#include "statistical_util.h"

#define E_CuCu -436.0
#define E_ZnZn -113.0
#define E_CuZn -294.0

static void MetropolisInternal_fprintf(FILE * file,double energy,
                               double P,
                               double r){
    fprintf(file,"%e\t%e\t%e\n",energy,P,r);
}

void autocorr_fprintf(FILE *file, double *auto_corr,unsigned int k_step, unsigned int n_k){
    for (unsigned int l=0;l<n_k;l++){
        fprintf(file,"%i\t%e\n",k_step*l,auto_corr[l]);
    }
}

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
    double energy;
    double delta_E;
    
    // Declares variable used for temporary storage
    double probability_ratio;
    
    //Declares latticenodes to be used as random nodes
    LatticeNode *r_node1;
    LatticeNode *r_node2;
    
    //Initializes E, P and r
    energy = bcc_energy(l, NodeTypeCopper, NodeTypeZinc, E_CuCu, E_ZnZn, E_CuZn);;
    double long_range_order = bcc_long_range_order(l, NodeTypeCopper);
    double avg_short_range_order = bcc_average_short_range_order(l);
    
    // Setting up random number generation
    gsl_rng_env_setup();
    const gsl_rng_type *T = gsl_rng_default;
    gsl_rng *rng = gsl_rng_alloc(T);
    gsl_rng_set(rng,time(NULL));
    
    FILE * file = fopen("metropolis.dat","a");
    
    for (unsigned int i = 1; i < o.n_iterations + o.equilibration_skip; i++) {
        
        //Metropolis step 1
        r_node1 = bcc_get_node_random(l, rng);
        r_node2 = bcc_get_node_random(l, rng);
        node_swap_types(r_node1, r_node2);
        
        //Metropolis step 2
        energy_old = energy;
        energy = bcc_energy(l, NodeTypeCopper, NodeTypeZinc,
                                E_CuCu, E_ZnZn, E_CuZn);
        delta_E = energy - energy_old;
        
        //Metropolis step 3
        probability_ratio = get_boltzmann_dist_frac(delta_E, o.temperature);
        
        if ( (delta_E > 0.0) && (probability_ratio < gsl_rng_uniform(rng)) ) {
            // Discard energy and swap back
            energy = energy_old;
            node_swap_types(r_node1, r_node2);
        }
        
        //Computes P and r
        long_range_order = bcc_long_range_order(l, NodeTypeCopper);
        avg_short_range_order = bcc_average_short_range_order(l);
        
        
        if(i >= o.equilibration_skip){
            unsigned int index = i - o.equilibration_skip;
            E[index] = energy;
            P[index] = long_range_order;
            r[index] = avg_short_range_order;
        }
        if((i) % ((o.n_iterations+o.equilibration_skip)/(1000)) == 0){
            MetropolisInternal_fprintf(file,
                                       energy,
                                       long_range_order,
                                       avg_short_range_order);
        }
    }
    fclose(file);
    
    double n_iter = o.n_iterations;
    
    double s_autocorr;
    double s_block_avg;
    
    double *auto_corr = malloc(o.auto_corr_n_k*sizeof(*auto_corr));
    calc_autocorr(auto_corr, E, n_iter,o.auto_corr_k_step, o.auto_corr_n_k);
    FILE * file2 = fopen("energy_autocorr.dat","w");
    autocorr_fprintf(file, auto_corr, o.auto_corr_k_step, o.auto_corr_n_k);
    fclose(file2);
    free(auto_corr);
    
    s_autocorr = get_s_autocorr(E,n_iter,o.auto_corr_k_step, o.auto_corr_n_k);
    s_block_avg = get_s_block_averaging(E, n_iter, o.block_avg_block_size);
    MetropolisDataElement out_energy = {
        .mean = mean(E, n_iter),
        .s_autocorrelation = s_autocorr,
        .s_block_average = s_block_avg,
        .std_autocorrelation = sqrt(s_autocorr / n_iter* var(E, n_iter)),
        .std_block_average = sqrt(s_block_avg / n_iter * var(E, n_iter))
    };
    
    s_autocorr = get_s_autocorr(P,n_iter,o.auto_corr_k_step, o.auto_corr_n_k);
    s_block_avg = get_s_block_averaging(P, n_iter, o.block_avg_block_size);
    MetropolisDataElement out_long_range_order = {
        .mean = mean(P, n_iter),
        .s_autocorrelation = s_autocorr,
        .s_block_average = s_block_avg,
        .std_autocorrelation = sqrt(s_autocorr / n_iter * var(P, n_iter)),
        .std_block_average = sqrt(s_block_avg / n_iter * var(P, n_iter))
    };

    s_autocorr = get_s_autocorr(r,n_iter,o.auto_corr_k_step, o.auto_corr_n_k);
    s_block_avg = get_s_block_averaging(r, n_iter,o.block_avg_block_size);
    MetropolisDataElement out_short_range_order = {
        .mean = mean(r, n_iter),
        .s_autocorrelation = s_autocorr,
        .s_block_average = s_block_avg,
        .std_autocorrelation = sqrt(s_autocorr / n_iter * var(r, n_iter)),
        .std_block_average = sqrt(s_block_avg / n_iter * var(r, n_iter))
    };

    MetropolisDataElement out_heat_capacity = {
        .mean = get_C(E, o.n_iterations, o.temperature),
        .s_autocorrelation = 0.0,
        .s_block_average = 0.0,
        .std_autocorrelation = 0.0,
        .std_block_average= 0.0
    };
    
    output->energy = out_energy;
    output->long_range_order = out_long_range_order;
    output->short_range_order = out_short_range_order;
    output->heat_capacity = out_heat_capacity;
    
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

