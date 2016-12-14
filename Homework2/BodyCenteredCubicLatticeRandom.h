//
//  BodyCenteredCubicLatticeRandom.h
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#ifndef BodyCenteredCubicLatticeRandom_h
#define BodyCenteredCubicLatticeRandom_h

#include <stdio.h>
#include <gsl/gsl_rng.h>
#include "BodyCenteredCubicLattice.h"

LatticeNode *bcc_get_node_random(BodyCenteredCubicLattice *l,
                                 const gsl_rng *rng);
#endif /* BodyCenteredCubicLatticeRandom_h */
