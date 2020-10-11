
//
//  ChessTree.h
//  
//
//  Created by Matthew Dunn on 1/12/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

//This file contains the functions that operate on the chess tree data structure.


#include "ChessStruct.h"

#ifndef AI_H
#define AI_H



//Returns the board at the head of the branch where the best move was chosen
GBOARD *ReturnBranchBoard(TNODE *tnode);


//This is the minimax evaluation function
TNODE *minimax(TNODE *tree, int depth, int player);
 

//returns the best board at the top of the tree
void GetBestMove(GAME *game);



 
#endif

//EOF
