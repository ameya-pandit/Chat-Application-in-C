//
//  ChessTree.h
//  
//
//  Created by Matthew Dunn on 1/12/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

//This file contains the functions that will return the best move

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "MovesList.h"
#include "ChessTree.h"
#include "Board.h"
#include "Ai.h"
#include "Moves.h"

#define DEPTH 3




//This will take the input of the best node and return a pointer to the board
//Made this for use with the DFS function it is no longer needed
GBOARD *ReturnBranchBoard(TNODE *tnode) {
    assert(tnode);
   
    if(tnode->depth > 0){
        TNODE *tnode1, *tnode2;
    
        tnode1 = tnode;
        while(tnode1->depth != 1) {
            tnode2 = tnode1->back;
            tnode1 = tnode2;
        }
        return tnode1->board;
    }
    return tnode->board;
}







//Minimax algorithm. Returns a pointer to the best treenode based on heuristics.
TNODE *minimax(TNODE *tree, int depth, int player) {
    assert(tree);
    bool playerVal;
 
    if(player == 1){
        playerVal = true;
    }
    if(player == 2){
        playerVal = false;
    }
 
    if(depth == 0){     
    return tree;
    }
    if(tree->list->first == NULL){
        checkmove(tree);
        if(tree->list->first == NULL){
            return tree;
        }
    } 
    if(playerVal){    
        int bestSoFar = -5000;
        TNODE *bestNode = NULL;
        TNODE *temp;

        LNODE *node1, *node2;
        assert(tree->board);
      
        node1 = tree->list->first;
        while(node1){
            node2 = node1->next;
            assert(node1->tnode);
            temp = minimax(node1->tnode,(depth -1),tree->board->playerflag);
            assert(temp->board);
            if(Score(temp->board) > bestSoFar){
                 bestSoFar = Score(temp->board);
                 bestNode = temp;
            }
            node1 = node2;
        } 
        return bestNode;               
    } else {     
    
        int bestSoFar = 5000;
        TNODE *bestNode = NULL;
        TNODE *temp;

        LNODE *node1, *node2;
        assert(tree->board);

        node1 = tree->list->first; 
        while(node1){
            node2 = node1->next;
            temp = minimax(node1->tnode,(depth -1),tree->board->playerflag);    
            if(Score(temp->board) < bestSoFar){
                 bestSoFar = Score(temp->board);
                 bestNode = temp;
            }
            node1 = node2;  
        }
        return bestNode;
    }           
}






//gets the best move and attaches it to the game struct
void GetBestMove(GAME *game) {
    assert(game);

    GBOARD *bestBoard;
    TNODE *tree;
    TNODE *bestNode;
    tree = CreateTree();
    assert(tree);
    tree->board = CopyBoard(game->currentBoard); 
    assert(tree->board);
    assert(tree->list);
    bestNode = minimax(tree,game->difficultyLevel,tree->board->playerflag);  
    bestBoard = ReturnBranchBoard(bestNode);
    DeleteBoard(game->currentBoard);
    assert(bestNode->board);
    game->currentBoard = CopyBoard(bestBoard);

    DeleteTree(tree);
    tree = NULL;
    return;
}




//EOF










