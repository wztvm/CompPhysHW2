//
//  BodyCenteredCubicLattice.h
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#ifndef BodyCenteredCubicLattice_h
#define BodyCenteredCubicLattice_h

#include "SimpleCubicLattice.h"
#include <stdio.h>

typedef struct{
    SimpleCubicLattice * sc[2];
    unsigned int n_cells;
    unsigned int n;
} BodyCenteredCubicLattice;

SimpleCubicLattice * bcc_first_sc(BodyCenteredCubicLattice *l);

SimpleCubicLattice * bcc_second_sc(BodyCenteredCubicLattice *l);

BodyCenteredCubicLattice * bcc_alloc(unsigned int n);

void bcc_free(BodyCenteredCubicLattice *l);

void bcc_init(BodyCenteredCubicLattice *l);

typedef enum{First_Lattice = 0,Second_Lattice = 1} BCC_Sub_Lattice;

LatticeNode *bcc_get_node(BodyCenteredCubicLattice *l,
                          BCC_Sub_Lattice sub_lattice,
                          unsigned int n);

LatticeNode *bcc_get_node_neighbor(BodyCenteredCubicLattice *l,
                                   BCC_Sub_Lattice sub_lattice,
                                   unsigned int n,
                                   unsigned int j);

double bcc_long_range_order(BodyCenteredCubicLattice *l,NodeType A);

double bcc_short_range_order(LatticeNode *node);

double bcc_average_short_range_order(BodyCenteredCubicLattice *l);

double bcc_energy(BodyCenteredCubicLattice *l,
                  NodeType A,
                  NodeType B,
                  double energy_AA,
                  double energy_BB,
                  double energy_AB);

void bcc_type_count_prinf(BodyCenteredCubicLattice * l,
                           NodeType A,NodeType B);

#endif /* BodyCenteredCubicLattice_h */
