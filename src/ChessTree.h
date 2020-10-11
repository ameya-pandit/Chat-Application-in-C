//
//  ChessTree.h
//  
//
//  Created by Matthew Dunn on 1/12/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

//This file contains the functions that operate on the chess tree data structure.



#ifndef CHESSTREE_H
#define CHESSTREE_H

#include "ChessStruct.h"



/* Create a new node in the tree */
TNODE *CreateTreeNode(void);

//Deletes the tree node. The list in the node must be null.
void DeleteTreeNode(TNODE *node);

//Deletes the tree itself. Functions are called recursivly
void DeleteTree(TNODE *node);

//Append a list to the tree node
void AppendList(TNODE *node, MLIST *list);

//Creates a tree for the AI
TNODE *CreateTree(void);

//Test function this is not used in the final game
GBOARD *create(void);



#endif

//EOF
