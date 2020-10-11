//
//  Board.c
//  BoardGame
//
//  Created  by 邵云鹤 on 1/17/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.00
//
#include "Board.h"
#include <assert.h>
#include <stdlib.h>
#define KWHT  "\x1B[31m"
#define KRED  "\x1B[37m"
#include <string.h>
#include "ChessTree.h"
#include "Moves.h"

GBOARD *CreateBoard(){
    int i;
    GBOARD *board = (GBOARD *)malloc(sizeof(GBOARD));
    for (i = 0; i < 64; i++) {
        board -> piece[i] = ' ';
    }
    board->colum = '0';
    board->pcolum = '0';
    board->row = 0;
    board->prow = 0;
    board->playerflag = 0;
    board->aimove = 0;
    for (i=0; i<6; i++){
        board->castling[i]=0;
    }

    //board -> color = (char *)malloc(sizeof(2));
    if (board == NULL) {
        return NULL;
    }
    return board;
}

int GetUserInput(){
    int NumRow;
    int Location;
    char Input[4];
    int NumColumn;

    while (1) {
        printf("\nLocation format: a1 \nType end to move to the next piece type\nPlease make your entry:");
        scanf("%s", Input);                                         //get user input
        if ((Input[0]>='a')&&(Input[0]<='h')&&(Input[1]>='1')&&(Input[1]<='8')&&(Input[2] == '\0')) {
            NumRow = Input[0] - 97;
           // printf("Row is %d", NumRow);
            NumColumn= Input[1] - 49;
           // printf("Col is %d", NumColumn);
            Location = NumRow + NumColumn*8;
           // printf("The location is %d\n", Location);
            return Location;
        }
     //   if (Input[0] == 'q'&&Input[1] == 'u'&&Input[2] == 'i'&&Input[3] == 't') {
     //       return 600;//600 is the retrun code for quit
     //   }
        if (Input[0] == 'e'&&Input[1] == 'n'&&Input[2] == 'd') {
            return 601;//601 is the return code for ending the custom initialization
        }
     // if (Input[0] == 'u'&&Input[1] == 'u'&&Input[2] == 'd'&&Input[3] == 'o') {
     //     return 602;//600 is the retrun code for undo
     //    }
     //    if (Input[0] == 'c'&&Input[1] == 'o'&&Input[2] == 's') {
     //      return 603;//600 is the retrun code for costomerization
     //  }
        else {
            printf("invalid!!! Please check your input number or input expression");
            continue;
        }
    }
}

void PrintBoard(GBOARD *board)
{
    int i,j;
    int HoriIndex = 8;
    int PieceFlag = 56;
    int Capiflag;




    printf("                Player Two\n");
    for(j=0;j<17;j++)
    {
        //printf("%d", j);
        if (j % 2 == 1 && HoriIndex >= 0) {
            printf("%d |", HoriIndex);
            for (i = 0; i < 8; i++) {
                Capiflag = board -> piece[PieceFlag + i];
                if (Capiflag >= 97) {
                    printf(" %s%c%s  |", KWHT, board -> piece[PieceFlag + i], KNRM);
                } else {
                    printf(" %s%c%s  |", KRED, board -> piece[PieceFlag + i], KNRM);
                }



                if (i == 7) {
                    printf("\n");
                }

            }

            /*printf("%d | %c  | %c  | %c  | %c  | %c  | %c  | %c  | %c  |\n", HoriIndex, board -> piece[PieceFlag], board -> piece[PieceFlag+1], board -> piece[PieceFlag+2], board -> piece[PieceFlag+3], board -> piece[PieceFlag+4], board -> piece[PieceFlag+5], board -> piece[PieceFlag+6], board -> piece[PieceFlag+7]);*/
            HoriIndex--;
            PieceFlag = PieceFlag - 8;
            //printf("%d", HoriIndex);
        }
        else{
            printf("  ");
            for (i = 0; i < 8; i++) {
                if (i == 7) {
                    printf("+----+\n");
                } else {
                    printf("+----");
                }
            }
        }
    }
    printf("    a    b    c    d    e    f    g    h   \n");
    printf(KRED);
    printf("                Player One\n");
    printf(KNRM);
}

int InitializeBoard(int CosFlag, GBOARD *board){
    int i, j;
    for (i = 0; i < 64; i++) {
        board -> piece[i] = ' ';
    }
    if (CosFlag == 0) {
        board -> piece[56] = 'r';
        board -> piece[63] = 'r';
        board -> piece[0] = 'R';
        board -> piece[7] = 'R';
        board -> piece[57] = 'n';
        board -> piece[62] = 'n';
        board -> piece[1] = 'N';
        board -> piece[6] = 'N';
        board -> piece[58] = 'b';
        board -> piece[61] = 'b';
        board -> piece[2] = 'B';
        board -> piece[5] = 'B';
        board -> piece[3] = 'Q';
        board -> piece[59] = 'q';
        board -> piece[60] = 'k';
        board -> piece[4] = 'K';
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 8; j++) {
                if (i == 1) {
                    board -> piece[j + 8 + 5*8*i] = 'p';
                } else {
                    board -> piece[j + 8 + 5*8*i] = 'P';
                }
            }
        }
        for (i=0; i<6; i++){
            board->castling[i]=0;
        }
    }
    else {
        int playerflag;
        //int PFlag = 8;
        //int RFlag = 2;
        //int NFlag = 2;
        //int BFlag = 2;
        //int ColumNum;
        //char RowNum;
        int Location;
        int PlayerSwitch;
        for (int i=0; i<6; i++){
            board->castling[i]=0;
        }
        printf("*****************************************************\n");
        printf("Which side would you want to choose to start placing?\nEnter 1 for player 1:\nEnter 2 for player 2:");
        scanf("%d", &playerflag);
        playerflag = playerflag -1;
        for (PlayerSwitch = 0; PlayerSwitch < 2; PlayerSwitch++){
        printf("Player %d: Please put your custom initialization:\n",playerflag + 1);
        //printf("Where would you like to place your Plawn. type 'end' when you put all the plawns");
        while (1) {
            PrintBoard(board);
            printf("Please start to place your Pawns:");
            Location = GetUserInput();
            //printf("\nThe content is:%c\n", board->piece[Location]);
            if (Location == 601) {
                break;
            }
            else if (Location >= 0 && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 0){
                board -> piece[Location] = 'P';
            }
            else if (Location >= 0 && Location <= 63 && board -> piece[Location] == ' ' && playerflag == 1){
                board -> piece[Location] = 'p';
            }
            else{
                printf("Invalid Input");
            }
            PrintBoard(board);
        }
        while (1) {
            printf("Please start to place your rooks:");
            Location = GetUserInput();
            if (Location == 601) {
                break;
            }
            else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 0){
                board -> piece[Location] = 'R';
            }
            else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 1){
                board -> piece[Location] = 'r';
            }

            else{
                printf("Invalid Input");
            }
            PrintBoard(board);
        }
        while (1) {
            printf("Please start to place your Knights:");
            Location = GetUserInput();
            if (Location == 601) {
                break;
            }
            else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 0){
                board -> piece[Location] = 'N';
            }
            else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 1){
                board -> piece[Location] = 'n';
            }

            else{
                printf("Invalid Input");
            }
            PrintBoard(board);
        }
        while (1) {
            printf("Please start to place your Bishops:");
            Location = GetUserInput();
            if (Location == 601) {
                break;
            }
            else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 0){
                board -> piece[Location] = 'B';
            }
            else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 1){
                board -> piece[Location] = 'b';
            }

            else{
                printf("Invalid Input");
            }
            PrintBoard(board);
        }

        while (1) {
          printf("Please start to place your Queen:");
          Location = GetUserInput();
          if (Location == 601) {
              break;
              }
          else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 0){
                  board -> piece[Location] = 'Q';
              }
          else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 1){
                  board -> piece[Location] = 'q';
              }
          PrintBoard(board);
        }

        while (1) {
        printf("Please start to place your King:");
        Location = GetUserInput();
        if (Location == 601) {
            PrintBoard(board);
            printf("******************************************\n");
            printf("     Each player must have a king\n");
            printf("******************************************\n");
 
            }
         /*Location = GetUserInput();
            if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 0){
                board -> piece[Location] = 'K';
            }
            else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 1){
                board -> piece[Location] = 'k';
            }
          }*/
        if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 0){
            board -> piece[Location] = 'K';
            board->castling[2] = 1;
            PrintBoard(board);
            break;
            }
        else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 1){
            board -> piece[Location] = 'k';
            board->castling[5] = 1;
            PrintBoard(board);
            break;
            }
        }


            if (playerflag == 1) {
                playerflag -= 1;
            } else {
                playerflag += 1;
            }
          }
    }
    return 1;
}

int Testing(GBOARD *board){
    char test;
    test = board->piece[63];
    printf("%c", test);
    return 1;
}

GBOARD *CopyBoard(GBOARD *board){
    int i = 0;
    GBOARD *prev = CreateBoard();
    prev -> colum = board -> colum;
    prev -> pcolum = board -> pcolum;
    prev -> row = board -> row;
    prev -> prow = board -> prow;
    prev -> playerflag = board -> playerflag;
    prev -> aimove = board -> aimove;
    for (i = 0; i < 64; i++) {
        prev -> piece[i] = board -> piece[i];
    }
    for (i=0; i<6;i++)
        prev->castling[i]= board->castling[i];
    return prev;
}

int Score(GBOARD *board){
    int score = 0;
    int i;
    int P = 10, R = 50, N = 40, B = 30,Q = 250, K = 900; //the score for Knight is higher than Bishop
    int p = -P, r = -R, n = -N, b = -B,q = -Q,k = -K;
    TNODE *tree = CreateTree();
    tree->board = CopyBoard(board);
    int length;



    for (i = 0; i < 64; i++) {
        if (board -> piece[i] == 'P') {
            score = score + P;
        }
        else if (board -> piece[i] == 'p'){
            score = score + p;
        }
        else if (board -> piece[i] == 'R') {
            score = score + R;
        }
        else if (board -> piece[i] == 'r'){
            score = score + r;
        }
        else if (board -> piece[i] == 'N') {
            score = score + N;
        }
        else if (board -> piece[i] == 'n'){
            score = score + n;
        }
        else if (board -> piece[i] == 'B') {
            score = score + B;
        }
        else if (board -> piece[i] == 'b'){
            score = score + b;
        }
        else if (board -> piece[i] == 'Q') {
            score = score + Q;
        }
        else if (board -> piece[i] == 'q'){
            score = score + q;
        }
        else if (board -> piece[i] == 'K') {
            score = score + K;
        }
        else if (board -> piece[i] == 'k'){
            score = score + k;
        }
        else
            score += 0;

    }
    checkmove(tree);
    length = tree->list->length;

    DeleteTree(tree);
    if(board->playerflag == 1){
        score = score + (length*3);
    }
    if(board->playerflag == 2){
        score = score - (length*3);
    }

    return score;
}

int DeleteBoard(GBOARD *board){
    assert(board);
    free(board);
    return 1;
    }

/*void PrintBoard(GBOARD *board)
{
    int i,j;
    int HoriIndex = 8;
    int PieceFlag = 56;
    printf("                Player Two\n");
    for(j=0;j<17;j++)
    {
        //printf("%d", j);
        if (j % 2 == 1 && HoriIndex >= 0) {

            printf("%d | %c  | %c  | %c  | %c  | %c  | %c  | %c  | %c  |\n", HoriIndex, board -> piece[PieceFlag], board -> piece[PieceFlag+1], board -> piece[PieceFlag+2], board -> piece[PieceFlag+3], board -> piece[PieceFlag+4], board -> piece[PieceFlag+5], board -> piece[PieceFlag+6], board -> piece[PieceFlag+7]);
            HoriIndex--;
            PieceFlag = PieceFlag - 8;
            //printf("%d", HoriIndex);
        }
        else{
            printf("  ");
            for (i = 0; i < 8; i++) {
                if (i == 7) {
                    printf("+----+\n");
                } else {
                    printf("+----");
                }
            }
        }
    }
    printf("    a    b    c    d    e    f    g    h   \n");
    printf("                Player One\n");
}*/
