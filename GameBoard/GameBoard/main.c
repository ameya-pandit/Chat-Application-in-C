//
//  main.c
//  BoardGame
//
//  Created by 邵云鹤 on 1/17/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

#include <stdio.h>
#include "Board.h"


int main(int argc, const char * argv[]) {
    GBOARD *board;
    // insert code here... test
    int TestFlag;//This is a variable for testing
    //GBOARD *board = (GBOARD *)malloc(sizeof(GBOARD));
    printf("Hello, World!\n");
    board = CreateBoard();
    PrintBoard(board);
    board -> playerflag = 0;
    InitializeBoard(1, board);
    PrintBoard(board);
    CreateBoard(0, board);
    Testing(board);
    TestFlag = GetUserInput();
    printf("Tesing result is %d", TestFlag);
    return 0;
}

