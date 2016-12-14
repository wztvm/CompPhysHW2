//
//  BodyCenteredCubicLattice.c
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#include "BodyCenteredCubicLattice.h"

#include <stdio.h>
#include <stdlib.h>
#include "SimpleCubicLattice.h"

BodyCenteredCubicLattice * bcc_alloc(unsigned int n){
    BodyCenteredCubicLattice * l = malloc(sizeof(BodyCenteredCubicLattice));
    l->sc[0] = sc_alloc(n);
    l->sc[1] = sc_alloc(n);
    l->n = n;
    l->n_cells = n * n * n;
    
    for(unsigned int i = 0; i < l->n_cells; i++){
        l->sc[0]->nodes[i].nearestNeighborList = malloc(8*sizeof(LatticeNode*));
        l->sc[1]->nodes[i].nearestNeighborList = malloc(8*sizeof(LatticeNode*));
    }
    
    return l;
}

void bcc_free(BodyCenteredCubicLattice *l){
    for(unsigned int i = 0; i < l->n_cells; i++){
        l->sc[0]->nodes[i].nearestNeighborList = malloc(8*sizeof(LatticeNode*));
        l->sc[1]->nodes[i].nearestNeighborList = malloc(8*sizeof(LatticeNode*));
    }
    for(unsigned int i = 0; i < l->n_cells; i++){
        free(l->sc[0]->nodes[i].nearestNeighborList);
        free(l->sc[1]->nodes[i].nearestNeighborList);
    }
    sc_free(l->sc[0]);
    sc_free(l->sc[1]);
    free(l);
}



void bcc_init(BodyCenteredCubicLattice *l){
    SimpleCubicLattice * sc1 = l->sc[0];
    SimpleCubicLattice * sc2 = l->sc[1];
    sc_init(sc1);
    sc_init(sc2);
    
    LatticeNode * node;
    
    unsigned int dx,dy,dz;
    for(unsigned int i = 0; i < l->n_cells; i++){
        sc1->nodes->type = NodeTypeCopper;
        sc2->nodes->type = NodeTypeZinc;
        for(unsigned int j = 0;j<8;j++){
            dx = j % 2; dy = (j/2)%2; dz = (j/4)%2;
            node = sc_get_node_relative(sc1, i, dx-1, dy-1, dz-1);
            sc1->nodes[i].nearestNeighborList[j] = node;
            
            node = sc_get_node_relative(sc1, i, dx, dy, dz);
            sc2->nodes[i].nearestNeighborList[j] = node;
            
        }
    }
    
}
