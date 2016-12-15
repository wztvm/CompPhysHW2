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
        .n_iterations = 1500000,
        .equilibration_skip = 300000,
        .auto_corr_n_k = 400,
        .auto_corr_k_step = 300,
        .block_avg_block_size = 200000,
        .temperature = temperature
    };
    return options;
}

void MetropolisDataElement_short_fprintf(FILE * file,
                                         double temperature,
                                         MetropolisDataElement e){
    fprintf(file, "%e\t%e\t%e\t%e\t%e\t%e\n",
            temperature,
            e.mean,
            e.s_autocorrelation,
            e.std_autocorrelation,
            e.s_block_average,
            e.std_block_average);
}

int main(int argc, const char * argv[]) {
    BodyCenteredCubicLattice * l = bcc_alloc(10);
    bcc_init(l);
    
    FILE * file = fopen("metropolis.dat","w");
    fprintf(file, "");
    fclose(file);
    
    FILE * energy_file = fopen("energy_averages.dat","w");
    FILE * long_range_order_file = fopen("long_range_order_averages.dat","w");
    FILE * short_range_order_file = fopen("short_range_order_averages.dat","w");
    FILE * heat_capacity_file = fopen("heat_capacity_averages.dat","w");
    
    MetropolisOutput *output = malloc(sizeof(*output));
    
#define n_temp 15
    double temperature[n_temp] = {
        100.0, 200.0, 300.0,
        400.0, 450.0, 500.0,
        550.0, 600.0, 650.0,
        700.0, 725.0, 750.0,
        800.0, 900.0, 1000.0};
    for(int i=0; i<n_temp; i++){
        double temp = temperature[i];
        printf("- Metropolis - \nTemp: %0.0f\n",temp);
        double E = bcc_energy(l, NodeTypeCopper, NodeTypeZinc, -436.0, -113.0, -294.0);
        printf("Start Energy: %0.5f\n",E);
        bcc_type_count_prinf(l,NodeTypeCopper,NodeTypeZinc);
        
        MetropolisOptions options = getMetropolisOptions(temp);
        metropolis(l,options,output);
        bcc_type_count_prinf(l,NodeTypeCopper,NodeTypeZinc);
    
        MetropolisDataElement_short_fprintf(energy_file,temp,output->energy);
        MetropolisDataElement_short_fprintf(long_range_order_file,
                                            temp,output->long_range_order);
        MetropolisDataElement_short_fprintf(short_range_order_file,temp,
                                            output->energy);
        MetropolisDataElement_short_fprintf(heat_capacity_file,temp,
                                            output->heat_capacity);
    
        MetropolisDataElement_fprintf(stdout, output->energy, "Energy");
        MetropolisDataElement_fprintf(stdout, output->long_range_order, "Long range order");
        MetropolisDataElement_fprintf(stdout, output->short_range_order, "Short range order");
        MetropolisDataElement_fprintf(stdout, output->heat_capacity, "Heat Capacity");
    }
    fclose(energy_file);
    fclose(long_range_order_file);
    fclose(short_range_order_file);
    fclose(heat_capacity_file);
    
    free(output);
    bcc_free(l);
    return 0;
}
