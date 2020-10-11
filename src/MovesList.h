//
//  MovesList.h
//  GameBoard
//
//  Created by Matthew Dunn on 1/12/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

//This file contains the functions that handle the double linked list of moves




#ifndef IMAGELIST_H
#define IMAGELIST_H

#include <stdio.h>
#include "ChessStruct.h"

//Create a new list node
LNODE *CreateListNode(void);

//Delete a list node and all its entries
void DeleteListNode(LNODE *node);

//Create a list for moves
MLIST *CreateMoveList(void);

//Delete a list and all its entries
void DeleteMoveList(MLIST *list);

//Append a list node onto the list
void AppendListNode(TNODE *tnode, GBOARD *gboard);

//Delete the last node on the list
void DeleteLastNode(TNODE *tnode);

#endif
