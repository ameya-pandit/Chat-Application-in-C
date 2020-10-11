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

#define KWHT  "\x1B[37m"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"

typedef struct  {
    char color;
    char colum;
    char pcolum;
    int row;
    int prow;
    int bscore;
    int wscore;
    int playerflag;
    char piece[64];
} GBOARD;

void PrintBoard(GBOARD *board);

int InitializeBoard(int CosFlag, GBOARD *board);

int Testing(GBOARD *board);

int GetUserInput();

GBOARD *CopyBoard(GBOARD *board);

GBOARD *CreateBoard();

int Score(GBOARD *board);

int DeleteBoard(GBOARD *board);
#endif /* Board_h */

