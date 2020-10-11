//Checkmove.h file
//this is the header file for the function that checks the valid moves of a piece
//Team04

#ifndef CHECKMOVE_H
#define CHECKMOVE_H

#include "Board.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "MovesList.h"
#include <stdio.h>
#include "ChessStruct.h"
#include <assert.h>
#include "ChessTree.h"

void checkmove(TNODE *allmoves);

void pawnmoves(GBOARD *currentBoard, int position, TNODE *allmoves);

void rookmoves(GBOARD *currentBoard, int position, TNODE *allmoves);

void queenmoves(GBOARD *currentBoard, int position, TNODE *allmoves);

void kingmoves(GBOARD *currentBoard, int position, TNODE *allmoves);

void bishopmoves(GBOARD *currentBoard, int position, TNODE *allmoves);

void knightmoves(GBOARD *currentBoard, int position, TNODE *allmoves);

bool check(GBOARD *currentBoard);

int checkmate(GBOARD *currentBoard);

#endif
