//
//  Board.h
//  GameBoard
//
//  Created by 邵云鹤 on 1/17/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include <stdio.h>
#include <stdlib.h>
#include "ChessStruct.h"
#define KRED  "\x1B[37m"
#define KNRM  "\x1B[0m"
#define KWHT  "\x1B[31m"


void PrintBoard(GBOARD *board);

int InitializeBoard(int CosFlag, GBOARD *board);

int Testing(GBOARD *board);

int GetUserInput();

GBOARD *CopyBoard(GBOARD *board);

GBOARD *CreateBoard();

int Score(GBOARD *board);

int DeleteBoard(GBOARD *board);
#endif /* Board_h */

