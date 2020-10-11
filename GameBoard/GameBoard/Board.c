//
//  Board.c
//  BoardGame
//
//  Created by 邵云鹤 on 1/17/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.00
//
#include "Board.h"
#include <assert.h>



GBOARD *CreateBoard(){
    int i;
    GBOARD *board = (GBOARD *)malloc(sizeof(GBOARD));
    for (i = 0; i < 64; i++) {
        board -> piece[i] = ' ';
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
        printf("\nlocation format: a1\n type quit to quit\n type end to stop placeing the piece during setup \n type undo to withdraw during game\n");
        scanf("%s", Input);                                         //get user input
        if ((Input[0]>='a')&&(Input[0]<='h')&&(Input[1]>='1')&&(Input[1]<='8')&&(Input[2] == '\0')) {
            NumRow = Input[0] - 97;
            printf("Row is %d", NumRow);
            NumColumn= Input[1] - 49;
            printf("Col is %d", NumColumn);
            Location = NumRow + NumColumn*8;
            printf("The lcoation is %d\n", Location);
            return Location;
        }
        if (Input[0] == 'q'&&Input[1] == 'u'&&Input[2] == 'i'&&Input[3] == 't') {
            return 600;//600 is the retrun code for quit
        }
        if (Input[0] == 'e'&&Input[1] == 'n'&&Input[2] == 'd') {
            return 601;//601 is the return code for ending the custom initialization
        }
        if (Input[0] == 'u'&&Input[1] == 'u'&&Input[2] == 'd'&&Input[3] == 'o') {
            return 602;//600 is the retrun code for undo
        }
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
                Capiflag = board -> piece[PieceFlag + i] - 32;
                if (Capiflag >= 0) {
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
    printf("                Player One\n");
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
    }
    else {
        int playerflag;
        int PFlag = 8;
        int RFlag = 2;
        int NFlag = 2;
        int BFlag = 2;
        //int ColumNum;
        //char RowNum;
        int Location;
        int PlayerSwitch;
        printf("Which side would you want to choose to start placing? Enter 1 for player 1 and 2 for player 2");
        scanf("%d", &playerflag);
        playerflag = playerflag -1;
        for (PlayerSwitch = 0; PlayerSwitch < 2; PlayerSwitch++){
        printf("Player %d: plese put your custom initialization! ", playerflag+1);
        //printf("Where would you like to place your Plawn. type 'end' when you put all the plawns");
        for (PFlag = 8; PFlag > 0; PFlag--) {
            printf("Please start to place your Plawns:");
            Location = GetUserInput();
            printf("\nThe content is:%c", board->piece[Location]);
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
        }
        for (RFlag = 2; RFlag > 0; RFlag--) {
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
        }
        for (NFlag = 2; NFlag > 0; NFlag--) {
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
        }
        for (BFlag = 2; BFlag > 0; BFlag--) {
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
        }
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
        
        printf("Please start to place your King:");
        Location = GetUserInput();
        if (Location == 601) {
            printf("You must place a king on the board");
            printf("Please start to place your King:");
            Location = GetUserInput();
            if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 0){
                board -> piece[Location] = 'K';
            }
            else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 1){
                board -> piece[Location] = 'k';
            }
            }
        else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 0){
            board -> piece[Location] = 'K';
            }
        else if (0 <= Location && Location <= 63 && board -> piece[Location] == ' '&& playerflag == 1){
            board -> piece[Location] = 'k';
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
    prev -> color = board -> color;
    prev -> colum = board -> colum;
    prev -> pcolum = board -> pcolum;
    prev -> row = board -> row;
    prev -> prow = board -> prow;
    prev -> bscore = board -> bscore;
    prev -> wscore = board -> wscore;
    prev -> playerflag = board -> playerflag;
    for (i = 0; i < 64; i++) {
        prev -> piece[i] = board -> piece[i];
    }
    return prev;
}

int Score(GBOARD *board){
    int score = 0;
    int i;
    int P = 10, R = 50, N = 40, B = 30,Q = 100, K = 900; //the score for Knight is higher than Bishop
    int p = -P, r = -R, n = -N, b = -B,q = -Q,k = -K;
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
