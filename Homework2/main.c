//
//  main.c
//  Homework2
//
//  Created by David Dagson on 2016-12-05.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "BodyCenteredCubicLattice.h"

int main(int argc, const char * argv[]) {
    
    BodyCenteredCubicLattice * l = bcc_alloc(10);
    bcc_init(l);
    
    
    
    bcc_free(l);
    return 0;
}
