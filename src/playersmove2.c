//playersmove.c file
//this is the file for the function that asks for player input and moves the piece
//Team04

#include "playersmove.h"
#include <string.h>
#include "Board.h"
#include "GameLog.h"
#include "ChessIO.h"

int playersmove(GAME *game){
            
    int control = 0;
    char curcol, newcol;
    char currow, newrow;
    char Input[4];
    TNODE *tree = NULL;

    while(control == 0){
        while(control == 0){
            PrintFirstSelection();
            scanf("%s", Input);        
    
            if(Input[0] == 'q'){
                if(tree){
                    DeleteTree(tree);
                }
                return 1;
            }   
            if(strcmp(Input, "undo") == 0) {
                if(game->log->list->first->next){
                    undoComputer(game);
                    PrintBoard(game->currentBoard);                                
                } else {
                    PrintBoard(game->currentBoard);
                    printf("\nNo moves to undo!\n"); 
                }    
                continue;              
            }
            if(strcmp(Input, "hint") == 0) {
                PrintBoard(game->currentBoard);
                printhint(game);    
                continue;              
            }
 

            if(((Input[0]>= 97)&&(Input[0]<= 104))&&((Input[1]>='1')&&(Input[1]<='8'))){
                curcol = Input[0];
                currow = Input[1] - 48;
                break;
            }
            PrintBoard(game->currentBoard); 
            printf("\nPlease enter a valid input\n\n");
        }
        control = 0;
        while(control == 0){
            PrintSecondMenu();
            scanf("%s", Input);

            if(Input[0] == 'q'){
                if(tree){
                    DeleteTree(tree);
                }
                return 1;
            }

            if(((Input[0]>= 97)&&(Input[0]<= 104))&&((Input[1]>='1')&&(Input[1]<='8'))){
                newcol = Input[0];
                newrow = Input[1] - 48;
                break;
            }    
            PrintBoard(game->currentBoard);
            printf("\nPlease enter a valid input\n\n");
        }
        //check if the move is a possible valid move
        tree = CreateTree();
        tree->board = CopyBoard(game->currentBoard);
        checkmove(tree);
       




 

 
        //loop the list and check the row and column
        LNODE *node1, *node2;
        if(tree->list->first) {
            node1 = tree->list->first; 
            while(node1){
                node2 = node1->next;
                GBOARD *temp;
                temp = node1->tnode->board;   
                if((temp->row == newrow) && (temp->prow == currow)
                    && (temp->colum == newcol) && (temp->pcolum == curcol)) {  
                    DeleteBoard(game->currentBoard);
                    game->currentBoard = CopyBoard(temp);
                    if(tree){
                        DeleteTree(tree);
                    }
                    return 0;
                }
                node1 = node2;  
            }
        }
        if(tree){
            DeleteTree(tree);
            tree = NULL;
        }
        PrintBoard(game->currentBoard); 
        printf("The selected move is not allowed.\n");
        printf("Please enter a valid move\n");
     }
     return 0;
}//end of players move







//checks if it is possible to promote to a hight player
void checkpromote(GBOARD *board){
	
    char gameType;

    char GameString[6];


        for(int i=55; i<64; i++){
            if (board->piece[i]== 'P'){
                printf("Which piece would you like to promote to?");
                scanf("%1s", GameString);
    
                //input validation for gameType
                while((gameType != 'Q') && (gameType != 'R') && (gameType != 'B') && (gameType != 'N')) {  
                    if(strcmp(GameString,"Q") == 0) {
                        gameType = 'Q';
                        board->piece[i] = gameType;
                    } else {
                    if(strcmp(GameString,"R") == 0) {
                        gameType = 'R';
                        board->piece[i] = gameType;
                    } else {
                    if(strcmp(GameString,"B") == 0) {
                        gameType = 'B';
                        board->piece[i] = gameType;
                    } else {
                    if(strcmp(GameString,"N") == 0) {
                        gameType = 'N';
                        board->piece[i] = gameType; 
                    } else {
                    while(getchar() != '\n');//clear the input stream
                        printf("Please enter a valid option:");
                        scanf("%1s", GameString);
                    }}}}
               }//end input validation
            }
        }
        
 
        for(int i=0; i<8; i++){
            if (board->piece[i]=='p'){
                printf("Which piece would you like to promote to?");
                scanf("%1s", GameString);
 
                while((gameType != 'q') && (gameType != 'r') && (gameType != 'b') && (gameType != 'n')) {  
                    if(strcmp(GameString,"q") == 0) {
                        gameType = 'q';
                        board->piece[i] = gameType;
                    } else {
                    if(strcmp(GameString,"r") == 0) {
                        gameType = 'r';
                        board->piece[i] = gameType;
                    } else {
                    if(strcmp(GameString,"b") == 0) {
                        gameType = 'b';
                        board->piece[i] = gameType;
                    } else {
                    if(strcmp(GameString,"n") == 0) {
                        gameType = 'n';
                        board->piece[i] = gameType; 
                    } else {
                    while(getchar() != '\n');//clear the input stream
                        printf("Please enter a valid option:");
                        scanf("%1s", GameString);
                    }}}}
                }         
            }
        }
    PrintBoard(board);
    return;
}//End of checkpromote


//EOF
