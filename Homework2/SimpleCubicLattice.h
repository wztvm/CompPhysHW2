//
//  SimpleCubicLattice.h
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#ifndef SimpleCubicLattice_h
#define SimpleCubicLattice_h

#include <stdlib.h>
#include "LatticeNode.h"

typedef struct{
    LatticeNode * nodes;
    unsigned int n_cells;
    unsigned int n;
} SimpleCubicLattice;

SimpleCubicLattice * sc_alloc(unsigned int n);

void sc_free(SimpleCubicLattice * l);

void sc_init(SimpleCubicLattice * l);

LatticeNode* sc_get_node(SimpleCubicLattice *l,
                         unsigned int i,
                         unsigned int j,
                         unsigned int k);

LatticeNode * sc_get_node_relative(SimpleCubicLattice *l,
                                   unsigned int node_index,
                                   unsigned int i,
                                   unsigned int j,
                                   unsigned int k);

#endif /* SimpleCubicLattice_h */
