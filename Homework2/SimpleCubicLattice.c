//
//  SimpleCubicLattice.c
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#include "SimpleCubicLattice.h"


SimpleCubicLattice * sc_alloc(unsigned int n){
    SimpleCubicLattice * l = malloc(sizeof(SimpleCubicLattice));
    l->n = n;
    l->n_cells = n * n * n;
    l->nodes = node_alloc(l->n_cells);
    return l;
}

void sc_free(SimpleCubicLattice * l){
    node_free(l->nodes);
    free(l);
}

void sc_init(SimpleCubicLattice * l){
    
}
/*
LatticeNode* sc_get_node(SimpleCubicLattice *l,unsigned int i, unsigned int j, unsigned int k){
    unsigned int n = l->n;
    return (l->nodes + (i % n) + n * (j % n) + n * n * (k % n));
}

LatticeNode * sc_get_node_relative(SimpleCubicLattice *l,
                                   unsigned int node_index,
                                   unsigned int i,
                                   unsigned int j,
                                   unsigned int k){
    unsigned int index = node_index + i + j * l->n + k * l->n * l->n;
    return (l->nodes + (index % l->n_cells));
}
 */
