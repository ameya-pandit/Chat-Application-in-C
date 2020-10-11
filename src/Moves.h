
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//
//


#ifndef MOVES_H
#define MOVES_H

//Generates all of the possible moves from one board position
void checkmove(TNODE *allmoves);

//Gets the type of player that is at the current game piece
char GetPlayer(int column, int row, GBOARD *board);

//Puts the value of the player at the specified postion in row column format
void PutPlayer(int column, int row, GBOARD *board, char player);

//Sets the variables for the board including the previous location, current location and the player 
void SetVariables(GBOARD *board, int row, int prow, int column, int pcolumn);

//check if player can make the move returns 1 if the spot is empty or has the opponents player;
int CheckIfValid(char move, int player);

//Checks if the location specified is for the correct player
int CheckIfValid(char move, int player);

//Gets the moves for the rook player
void rookmoves(GBOARD *board, int column, int row, TNODE *tree);

//Gets the moves for the bishop player
void bishopmoves(GBOARD *board, int column, int row, TNODE *tree);
 
//Gets the moves for the queen player
void queenmoves(GBOARD *board, int column, int row, TNODE *tree);

//Gets the moves for the king player
void kingmoves(GBOARD *board, int column, int row, TNODE *tree);

//Gets the moves for the king player
void pawnmoves(GBOARD *board, int column, int row, TNODE *tree);

//Gets the moves for the king player
void knightmoves(GBOARD *board, int column, int row, TNODE *tree);
 
//Iterates vertically up the board and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateVertical(TNODE *tree,GBOARD *board, int column, int row);

//Iterates horizontally up the board and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateHorizontal(TNODE *tree,GBOARD *board, int column, int row);

//Iterates upwards diagonally across the board and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateUpDiag(TNODE *tree,GBOARD *board, int column, int row);
 
//Iterates downwards diagonally across the board and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateDownDiag(TNODE *tree,GBOARD *board, int column, int row);

//Iterates vertically up the board one step and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateVertK(TNODE *tree,GBOARD *board, int column, int row);

//Iterates horizontally up the board one step and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateHorizK(TNODE *tree,GBOARD *board, int column, int row);

//Iterates upwards diagonally across the board one step and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateUpDiagK(TNODE *tree,GBOARD *board, int column, int row);
 
//Iterates downwards diagonally across the board one step  and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateDownDiagK(TNODE *tree,GBOARD *board, int column, int row);

//Iterates vertically up the board two steps if a move has not been taken or one step and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateVertP(TNODE *tree,GBOARD *board, int column, int row);

//Iterates upwards diagonally across the board one step if there is an opponents  player to take. Also generates the tree nodes
void IterateUpDiagP(TNODE *tree,GBOARD *board, int column, int row);
 
//Iterates downwards diagonally across the board one step if there is an opponents player to take. Also generates the tree nodes
void IterateDownDiagP(TNODE *tree,GBOARD *board, int column, int row);

//Check for check condition
int CheckCheck(GBOARD *board, int flag);

//Check for checkmate
int checkmate(GBOARD *board);


int stalemate(GBOARD *board);
 

void checkwin(GAME *game); 
 
//Iterates upwards diagonally across the board one step and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateUpDiag2up(TNODE *tree,GBOARD *board, int column, int row);
 
//Iterates downwards diagonally across the board one step  and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateDownDiag2down(TNODE *tree,GBOARD *board, int column, int row);
 
//Iterates upwards diagonally across the board one step and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateUpDiag2over(TNODE *tree,GBOARD *board, int column, int row);
 
//Iterates downwards diagonally across the board one step  and stops when a player is taken or own player is reached. Also generates the tree nodes
void IterateDownDiag2over(TNODE *tree,GBOARD *board, int column, int row);

//Iterates vertically up the board and stops when a player is taken or own player is reached. Also generates the tree nodes
int IterateVerticalCheck(GBOARD *board, int column, int row);

//Iterates horizontally up the board and stops when a player is taken or own player is reached. Also generates the tree nodes
int IterateHorizontalCheck(GBOARD *board, int column, int row);

//Iterates upwards diagonally across the board and stops when a player is taken or own player is reached. Also generates the tree nodes
int IterateUpDiagCheck(GBOARD *board, int column, int row);
 
//Iterates downwards diagonally across the board and stops when a player is taken or own player is reached. Also generates the tree nodes
int IterateDownDiagCheck(GBOARD *board, int column, int row);
 
//Iterates upwards diagonally across the board one step and stops when a player is taken or own player is reached. Also generates the tree nodes
int IterateUpDiag2upCheck(GBOARD *board, int column, int row);

//Iterates downwards diagonally across the board one step  and stops when a player is taken or own player is reached. Also generates the tree nodes
int IterateDownDiag2downCheck(GBOARD *board, int column, int row);
 
//Iterates upwards diagonally across the board one step and stops when a player is taken or own player is reached. Also generates the tree nodes
int IterateUpDiag2overCheck(GBOARD *board, int column, int row);
 
//Iterates downwards diagonally across the board one step  and stops when a player is taken or own player is reached. Also generates the tree nodes
int IterateDownDiag2overCheck(GBOARD *board, int column, int row);

void Enpassant(TNODE *tree, GBOARD *board, int column, int row);

void Castling(TNODE *tree, GBOARD *board, int column, int row);
#endif
