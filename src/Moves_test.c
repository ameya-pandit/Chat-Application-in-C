
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

//This is the definition for the functions that operate on the chess tree
#include <assert.h>
#include "ChessStruct.h" 
#include "MovesList.h"
#include "Board.h"
#include "ChessTree.h"
#include "Moves.h"
#include "ChessIO.h"

int main(void){
    int boardType;
    TNODE *tree;
    tree = CreateTree();
    GBOARD *board;
    board = CreateBoard();


    PrintBoardMenu();
    boardType = GetBoardType();

    InitializeBoard((boardType - 1),board);
    board->playerflag = 1;
    tree->board = board;
 

    checkmove(tree);

    LNODE *node, *node1;

    node = tree->list->first;
    while(node){
        node1 = node->next;
        PrintBoard(node->tnode->board);
        printf("prow %d\n",node->tnode->board->prow);
        printf("row %d\n",node->tnode->board->row);
        printf("pcolumn %c\n",node->tnode->board->pcolum);
        printf("column %c\n",node->tnode->board->colum);
        printf("playerflag %d\n",node->tnode->board->playerflag);
        printf("check %d\n",CheckCheck(node->tnode->board,node->tnode->board->playerflag)); 
        node = node1;
    }
}



