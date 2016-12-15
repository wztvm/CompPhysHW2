//
//  LatticeNode.c
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#include "LatticeNode.h"
#include <stdlib.h>

const unsigned int node_get_n_nearest_neighbors(){
    return 8;
}

LatticeNode *node_alloc(unsigned int n){
    LatticeNode * node = malloc(n * sizeof(LatticeNode));
    return node;
}

void node_free(LatticeNode *node){
    free(node);
}

void node_init(LatticeNode *node){
    
}

void node_set_type(LatticeNode *node, NodeType type){
    node->type = type;
}

NodeType node_get_type(LatticeNode *node){
    return node->type;
}

void node_swap_types(LatticeNode *n,LatticeNode *m){
    NodeType t = n->type;
    n->type = m->type;
    m->type = t;
}
