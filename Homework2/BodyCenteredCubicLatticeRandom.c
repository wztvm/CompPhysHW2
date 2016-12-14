//
//  BodyCenteredCubicLatticeRandom.c
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#include "BodyCenteredCubicLatticeRandom.h"

LatticeNode *bcc_get_node_random(BodyCenteredCubicLattice *l,const gsl_rng *rng){
    LatticeNode *node;
    unsigned long sub_lattice = gsl_rng_uniform_int(rng,2);
    BCC_Sub_Lattice sc = (sub_lattice==0)? First_Lattice : Second_Lattice;
    unsigned int index = (unsigned int)gsl_rng_uniform_int(rng,l->n_cells);
    node = bcc_get_node(l, sc, index);
    return node;
}
