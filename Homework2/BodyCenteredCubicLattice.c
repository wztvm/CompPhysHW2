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

#pragma mark Life cycle
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
    sc_init(l->sc[0]);
    sc_init(l->sc[1]);
    
    LatticeNode * node;
    
    for(unsigned int i = 0; i < l->n_cells; i++){
        bcc_get_node(l, First_Lattice, i)->type = NodeTypeCopper;
        bcc_get_node(l, Second_Lattice, i)->type = NodeTypeZinc;
        for(unsigned int j = 0;j<8;j++){
            node = bcc_get_node_neighbor(l, First_Lattice, i, j);
            bcc_get_node(l, First_Lattice, i)->nearestNeighborList[j] = node;
            
            node = bcc_get_node_neighbor(l, Second_Lattice, i, j);
            bcc_get_node(l, Second_Lattice, i)->nearestNeighborList[j] = node;
            
        }
    }
    
}

#pragma mark Getters

LatticeNode *bcc_get_node(BodyCenteredCubicLattice *l, BCC_Sub_Lattice sub_lattice, unsigned int n){
    LatticeNode * node = (l->sc[sub_lattice]->nodes + n);
    return node;
}

LatticeNode *bcc_get_node_neighbor(BodyCenteredCubicLattice *l,
                                   BCC_Sub_Lattice sub_lattice,
                                   unsigned int i,unsigned int j){
    unsigned int dx,dy,dz;
    BCC_Sub_Lattice opposite;
    if(sub_lattice == First_Lattice){
        opposite = Second_Lattice;
        dx = j % 2;
        dy = (j/2)%2;
        dz = (j/4)%2;
    }else if(sub_lattice == Second_Lattice){
        opposite = First_Lattice;
        dx = (j % 2)-1;
        dy = ( (j / 2) % 2 ) - 1;
        dz = ( (j / 4) % 2 ) - 1;
    }
    unsigned int index = (i + dx + l->n * (dy + l->n * dz)) % l->n_cells;
    LatticeNode * node = bcc_get_node(l, opposite, index);
    return node;
}

#pragma mark Calculated properties

double bcc_long_range_order(BodyCenteredCubicLattice *l,NodeType A){
    double long_range_order = 0.0;
    double s = 0.0;
    for(unsigned int i = 0; i < l->n_cells; i++){
        if(bcc_get_node(l, First_Lattice, i)->type == A){
            s += 1.0;
        }
    }
    long_range_order = 2.0 * s / (double)l->n_cells - 1.0;
    return long_range_order;
}

double bcc_short_range_order(BodyCenteredCubicLattice *l,
                             BCC_Sub_Lattice sub_lattice,
                             unsigned int i){
    double r = 0.0;
    double q = 0.0;
    LatticeNode *node = bcc_get_node(l, First_Lattice, i);
    NodeType I,J;
    I = node->type;
    for(unsigned int j = 0; j < 8; j++){
        J = node->nearestNeighborList[j]->type;
        if(I != J){
            q += 1.0;
        }
    }
    r = (q-4.0)/4.0;
    return r;
}

double bcc_average_short_range_order(BodyCenteredCubicLattice *l){
    double average_short_range_order = 0.0;

    for(unsigned int i = 0; i < l->n_cells; i++){
        average_short_range_order += bcc_short_range_order(l,First_Lattice, i);
    }
    average_short_range_order /= l->n_cells;
    return average_short_range_order;
}

double bcc_energy(BodyCenteredCubicLattice *l,
                  NodeType A,
                  NodeType B,
                  double energy_AA,
                  double energy_BB,
                  double energy_AB){
    double energy = 0.0;
    double N_AA = 0.0;
    double N_BB = 0.0;
    double N_AB = 0.0;
    LatticeNode *node;
    NodeType I,J;
    for(unsigned int i = 0; i < l->n_cells; i++){
        node = bcc_get_node(l, First_Lattice, i);
        I = node->type;
        for(unsigned int j=0; j<8;j++){
            J = node->nearestNeighborList[j]->type;
            if(I == J){
                if(I == A){
                    N_AA += 1.0;
                }else if(I == B){
                    N_BB += 1.0;
                }
            }else{
                N_AB += 1.0;
            }
        }
    }
    energy = N_AA * energy_AA + N_BB * energy_BB + N_AB * energy_AB;
    return energy;
}

void bcc_type_count_prinf(BodyCenteredCubicLattice * l,NodeType A,NodeType B){
    unsigned int NA1 = 0;
    unsigned int NB1 = 0;
    unsigned int NA2 = 0;
    unsigned int NB2 = 0;
    for (int i=0;i< l->n_cells; i++){
        (bcc_get_node(l, First_Lattice, i)->type == A)?++NA1:++NB1;
        (bcc_get_node(l, Second_Lattice, i)->type == A)?++NA2:++NB2;
    }
    printf("SC1(NA: %d, NB: %d) SC2(NA: %d, NB: %d) \n",NA1,NB1,NA2,NB2);
}

void bcc_printf(BodyCenteredCubicLattice *l){
    for(int i=0;i<l->n_cells;i++){
        LatticeNode *node = bcc_get_node(l, First_Lattice, i);
        printf("Node(%i): ",i);
        if(node_get_type(node)== NodeTypeCopper){
            printf("A\n\t");
        }else{
            printf("B\n\t");
        }
        for(int j = 0;j<8;j++){
            node = bcc_get_node_neighbor(l, First_Lattice, i, j);
            if(node_get_type(node)== NodeTypeCopper){
                printf("A, ");
            }else{
                printf("B, ");
            }
        }
        printf("\n");
    }
}
