//
//  statistical_util.c
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#include "statistical_util.h"

#include <stdlib.h>
#include <math.h>

//Returns the mean of an input array x of size N
double mean(double* x, int N) {
    double mu = 0.0;
    unsigned int i;
    for (i = 0; i < N; i++) {
        mu += x[i];
    }
    mu /= ((double) N);
    return mu;
}

//Calculates the variance of an array x of size N
double var(double* x, int N) {
    double sigma = 0;
    const double mu = mean(x, N);
    unsigned int i;
    for (i = 0; i < N; i++) {
        sigma += (x[i] - mu) * (x[i] - mu);
    }
    sigma /= ((double) N);
    return sigma;
}

//Returns the fraction of two Boltzmann distributions with the same partition function and energy difference delta_E with temperature T
double get_boltzmann_dist_frac(double delta_E, double T) {
    return exp(-delta_E / (k_B * T));
}

//Returns the heat capacity using the average of an energy array E of size N and a temperature T
double get_C(double* E, int N, double T) {
    return var(E,N) / (k_B * T * T);
}

//Calculates the autocorrelation function for an array x of length N, for values of k = 0,...,k_max and inserts them into acorr
void calc_autocorr(double* acorr, double* x, int N,int k_step, int n_k) {
    //Calculates the mean and variance of x for later use
    const double var_x = var(x, N);
    const double mean_x = mean(x, N);
    
    //Calculates the correlations function for all k
    unsigned int i, l;
    for (l = 0; l < n_k; l++) {
        acorr[l] = 0;
        for (i = 0; i < N - l*k_step; i++) {
            acorr[l] += (x[i + l*k_step] - mean_x) * (x[i] - mean_x);
        }
        acorr[l] /= ((N - l*k_step) * var_x);
    }
}

//Finds the index i of a zero starting from index x_0 in an array x of size N. When found either i or i + 1 is returned depending on if x[i] or x[i + 1] lies closest to 0. If no zero is found it returns -1 and prints this to stdout
int find_zero(double* x, int N, int x_0) {
    unsigned int i;
    for (i = x_0; i < N - 1; i++) {
        if ((x[i] > 0.0 && x[i + 1] < 0.0) || (x[i] < 0.0 && x[i + 1] > 0.0)) {
            if (fabs(x[i]) < fabs(x[i + 1])) {
                return i;
            } else {
                return i + 1;
            }
            
        }
    }
    printf("No zero found, returning -1\n");
    return -1;
}

//Uses the autocorrelation function of the arrax x of size N with k_max + 1 points to calculate the statistical inefficiency s
double get_s_autocorr(double* x, int N, unsigned int k_step,unsigned int n_k) {
    //Calculates the autocorrelation function
    double *acorr = malloc((n_k + 1) * sizeof(double));
    calc_autocorr(acorr, x, N, k_step, n_k);
    
    //Subtracts acorr_s = exp(-2) from acorr to flace the zero at k = s
    const double acorr_s = exp(-2.0);
    for (unsigned int i = 0; i < n_k + 1; i++) {
        acorr[i] = acorr[i] - acorr_s;
    }
    
    //Finds and the zero for acorr[k] - acorr[s] starting from starting_index
    unsigned int starting_index = 0;
    double s = k_step*(double) find_zero(acorr, n_k, starting_index);
    
    //Frees F
    free(acorr); acorr = NULL;
    
    //Returns s
    return s;
}

//Returns an estimate of the statistical inefficiency s from an array x of size N using block-averaging with block size B
double get_s_block_averaging(double* x, int N, int B) {
    //Calculates the number of blocks. If N % B != 0 the rest is ignored
    const unsigned int nbr_of_blocks = N / B;
    
    //Calculates the block averaged function F
    double *F = malloc(nbr_of_blocks * sizeof(double));
    unsigned int i;
    for (i = 0; i < nbr_of_blocks; i++) {
        F[i] = mean(x + i * B, B);
    }
    
    //Calculates s
    double s = B * var(F, nbr_of_blocks) / var(x, N);
    
    //Frees F
    free(F); F = NULL;
    
    //Returns s
    return s;
}
