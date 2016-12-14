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

#endif /* BodyCenteredCubicLattice_h */
