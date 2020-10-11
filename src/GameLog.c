//
//  GameLog.h
//  
//
//  Created by Ameya Pandit on 1/23/19.
//

#include <stdio.h>
#include "GameLog.h"
#include <stdlib.h>
#include "ChessTree.h"
#include "Board.h"
#include "MovesList.h"
#include "Moves.h"


void undoComputer(GAME *game)	{	//undoing a move while playing computer client
	GBOARD *desiredBoard;	
	
	DeleteLastNode(game->log);	//delete the previous two boards. Previous board is to delete computer's turn, the board preceding the previous board is the user's former turn (which is to be undone)
	DeleteLastNode(game->log);

        if(game->log->list->last){	
	    desiredBoard = CopyBoard(game->log->list->last->tnode->board);	//copy last board
            DeleteBoard(game->currentBoard);	//delete last board
	    game->currentBoard = desiredBoard;	//set current board equal to copied board
        }
}

void undoPlayer(GAME *game)	{	//undoing a move if playing another human player
	GBOARD *desiredBoard;
	desiredBoard = CopyBoard(game->log->list->last->prev->tnode->board); //copy last board that you want to revert to

	DeleteLastNode(game->log);

	game->currentBoard = desiredBoard;	//set the current game board to the desired game board
}

void logOfMoves(TNODE *tree) {	//from the header file
	FILE *fp;		//file initialization
	fp = fopen("GameLog.txt", "w");
	
	int movesCounter = 0;	//counter for the number of nodes, corresponding to number of moves
	
	LNODE *node, *node1;	//two list nodes initialized, used to iterate through the list
	node = tree->list->first->next;	//just syntax to make next loop look better

	while (node != NULL)	{	//while there is a node in the linked list (not empty)
		node1 = node->next;	//used to iterate through linked list
		movesCounter++;		//increment moves counter for everytime there is a node
		
		char previousColumn = node->tnode->board->pcolum;	//retrieves the previous column from the gameboard struct.
		int previousRow = node->tnode->board->prow;	//retrieves previous row from gameboard struct
		char column = node->tnode->board->colum;	//retrieves current column from gameboard struct
		int row = node->tnode->board->row;	//retrieves current row from gameboard struct
	//	char player = node->tnode->board->color;
	
		int pieceCol = 0;	//variable used to locate piece in question (from 64 squares on the board)
		if (column == 'a')	{	//converting column value to numeric value to aid in finding piece in the 1D array
			pieceCol = 0;
		} else if (column == 'b')	{
			pieceCol = 1;
		} else if (column == 'c')	{
			pieceCol = 2;
		} else if (column == 'd')	{
			pieceCol = 3;
		} else if (column == 'e')	{
			pieceCol = 4;
		} else if (column == 'f')	{
			pieceCol = 5;
		} else if (column == 'g')	{
			pieceCol = 6;
		} else if (column == 'h')       {
                        pieceCol = 7;
                }

		int pieceNumber = (((row - 1) * 8) + pieceCol);	//the logic to retrieve the piece in question in the 64 index 1D array
      
		char pieceConversion = node->tnode->board->piece[pieceNumber];	//assigning piece in question to local variable used to print piece
		node = node1;	//used to iterate through nodes in the list
		fprintf(fp, "%d: %c %c%d to %c%d\n",movesCounter,pieceConversion, previousColumn, previousRow, column, row);	//printing to file
	}
  	fclose(fp);	//close file functionality
}


//adds the current board to the list for undo and log
void AddMoveToLog(GAME *game){
    GBOARD *temp;	//initialize new gameboard
    temp = CopyBoard(game->currentBoard);	//copy current game board to the initialized game board
    AppendListNode(game->log,temp);	//add new game board to the linked list
}












