//
//  LatticeNode.h
//  Homework2
//
//  Created by David Dagson on 2016-12-14.
//  Copyright © 2016 David Dagson. All rights reserved.
//

#ifndef LatticeNode_h
#define LatticeNode_h

typedef enum {NodeTypeCopper,NodeTypeZinc} NodeType;

typedef struct LatticeNodeTag LatticeNode;
typedef struct LatticeNodeTag{
    NodeType type;
    LatticeNode **nearestNeighborList;
} LatticeNode;

LatticeNode *node_alloc();

void node_free(LatticeNode *node);

void node_init(LatticeNode *node);

void node_set_type(LatticeNode *node, NodeType type);

NodeType node_get_type(LatticeNode *node);

void node_swap_types(LatticeNode *n,LatticeNode *m);

#endif /* LatticeNode_h */
