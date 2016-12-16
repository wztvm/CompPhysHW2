//
//  statistical_util.h
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#ifndef statistical_util_h
#define statistical_util_h

#include <stdio.h>

#define k_B 0.08617330 //Boltzmann constant in meV / K

//Returns the mean of an input array x of size N
double mean(double* x, int N);

//Calculates the variance of an array x of size N
double var(double* x, int N);

//Returns the fraction of two Boltzmann distributions with the same partition function and energy difference delta_E with temperature T
double get_boltzmann_dist_frac(double delta_E, double T);

//Returns the heat capacity using the average of an energy array E of size N and a temperature T
double get_C(double* E, int N, double T);

//Calculates the autocorrelation function for an array x of length N, for values of k = 0,...,k_max and inserts them into acorr
void calc_autocorr(double* acorr, double* x, int N,int k_step, int n_k);

//Finds the index i of a zero starting from index x_0 in an array x of size N. When found either i or i + 1 is returned depending on if x[i] or x[i + 1] lies closest to 0. If no zero is found it returns -1 and prints this to stdout
int find_zero(double* x, int N, int x_0);

//Uses the autocorrelation function of the arrax x of size N with k_max + 1 points to calculate the statistical inefficiency s
double get_s_autocorr(double* x, int N, unsigned int k_step,unsigned int n_k);

//Returns an estimate of the statistical inefficiency s from an array x of size N using block-averaging with block size B
double get_s_block_averaging(double* x, int N, int B);

#endif /* statistical_util_h */
