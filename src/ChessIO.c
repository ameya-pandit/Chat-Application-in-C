/*This is the main module for ChessGame*/
/*Team 4                               */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ChessIO.h"
#include <assert.h>
#include "ChessTree.h"
#include "Board.h"
#include "Ai.h"

#define SLEN 8





//get the game colot selection from the user	
int GetGameColor(void){
	
    char gameType = '0';

    char GameString[SLEN];

    printf("              Enter your selection:");
    scanf("%1s", GameString);
    
    //input validation for gameType
    while((gameType != 'w') && (gameType != 'b')) {  
        if(strcmp(GameString,"w") == 0) {
            printf("\nPlayer one has chosen to play ""w"".\n");
            gameType = 'w';
        } else {
            if(strcmp(GameString,"b") == 0) {
            printf("\nPlayer one has chosen to play ""b"".\n");
            gameType = 'b';
        } else {
            while(getchar() != '\n');//clear the input stream
            printf("\nPlease enter a valid option:");
            scanf("%1s", GameString);
        }}
    }//end input validation
    return gameType;
}//end of main







//Get the type of game either PVP, CVC, or PVP
int GetGameType(void){
	
    int gameType = -1;

    char GameString[SLEN];

    printf("              Enter your selection:");
    scanf("%1s", GameString);
    
    //input validation for gameType
    while(gameType < 0) { 
        if(strcmp(GameString,"0") == 0) {
            printf("\nGame ended\n");
            exit(10);
        } else {
        if(strcmp(GameString, "1") == 0) {
            printf("\nPlayer vs Player selected\n");
            gameType = atoi(GameString);
        } else {
        if(strcmp(GameString, "2") == 0) {
            printf("\nPlayer vs Computer selected\n");
            gameType = atoi(GameString);
        } else { 
        if(strcmp(GameString, "3") == 0) {
            printf("\nComputer vs Computer selected\n");
            gameType = atoi(GameString);
        } else {
            while(getchar() != '\n');//clear the input stream
            printf("\nPlease enter a valid option:");
            scanf("%1s", GameString);
        }}}}
    }//end input validation
    return gameType;
}//end of main






//get the game lovel selection from the user
int GetGameLevel(void){
	
    int gameType = -1;

    char GameString[SLEN];

    printf("             Enter your selection:");
    scanf("%1s", GameString);
    
    //input validation for gameType
    while(gameType < 0) { 
        if(strcmp(GameString,"1") == 0) {
            printf("\nEasy mode selected\n");
            gameType = atoi(GameString);
        } else {
        if(strcmp(GameString, "2") == 0) {
            printf("\nMedium mode selected\n");
            gameType = atoi(GameString);
        } else {
        if(strcmp(GameString, "3") == 0) {
            printf("\nHard mode selected\n");
            gameType = atoi(GameString);
        } else {
            while(getchar() != '\n');//clear the input stream
            printf("\nPlease enter a valid option:");
            scanf("%1s", GameString);
        }}}
    }//end input validation
    return gameType;
}//end of main







//Get the input for the game board type (standard or custom)
int GetBoardType(void){
	
    int gameType = -1;

    char GameString[SLEN];

    printf("              Enter your selection:");
    scanf("%1s", GameString);
    
    //input validation for gameType
    while(gameType < 0){ 
        if(strcmp(GameString, "1") == 0) {
            printf("\nStandard game board layout selected\n\n");
            gameType = atoi(GameString);
        } else {
        if(strcmp(GameString, "2") == 0) {
            printf("\nCustom game board layout selected\n\n");
            gameType = atoi(GameString);
        } else {
            while(getchar() != '\n');//clear the input stream
            printf("\nPlease enter a valid option:");
            scanf("%1s", GameString);
        }}
       
    }//end input validation
    return gameType;
}//end of main






//get the control for computer vs computer game
int GetControl(void){
	
    int gameType = -1;

    char GameString[SLEN];

    printf("\nPlease enter your selection:");
    scanf("%1s", GameString);
    
    //input validation for gameType
    while(gameType < 0){ 
        if(strcmp(GameString, "1") == 0) {
            gameType = atoi(GameString);
        } else {
        if(strcmp(GameString, "0") == 0) {
            gameType = atoi(GameString);
        } else {
            while(getchar() != '\n');//clear the input stream
            printf("\nPlease enter a valid option:");
            scanf("%1s", GameString);
        }}
       
    }//end input validation
    return gameType;
}//end of main






//prints out main menu for the user to make a gametype selection
void PrintMainMenu(void) {
    printf("*****************************************************\n");
    printf("          ** Welcome to Computer Chess **\n");
    printf("                     Main Menu\n\n");
    printf(" 1: Press 1 to play against another player.\n");
    printf(" 2: Press 2 to play against the computer.\n");
    printf(" 3: Press 3 to let the computer play against itself.\n");
    printf(" 4: Press 0 to quit.\n\n");


}




//prints out the menu for the user to select difficulty level
void PrintLevelMenu(void){
            printf("\n\n");
            printf("******************************************************\n");
            printf("         Please select the difficulty level\n");
            printf("               Select 1 for easy\n");
            printf("               Select 2 for medium\n");
            printf("               Select 3 for hard\n\n");
} 



//prints the color menu for the user selection
void PrintColorMenu(void){
            printf("\n\n");
            printf("******************************************************\n");
            printf("                Select Player Color\n");     
            printf(" Please select the color that you would like to play:\n");
            printf("     (for white enter 'w', for black enter 'b'\n\n");
}





//prints out the menu for the user to make a board layout selection
void PrintBoardMenu(void){
        printf("\n\n");
        printf("******************************************************\n");
	printf("         Please select game board layout:\n"
	       "         1: Standard layout\n"
	       "         2: Choose layout manually\n\n");
}



//prints a menu that allows the user to advance the computer vs computer game
void PrintControlMenu(void){
                printf("*******************************************\n");	    
                printf("  Computer vs computer mode\n");
                printf("  Enter 1 to let computer make next move\n");
                printf("  Enter 0 to quit:");
}




//prints the menu to select a move
void PrintFirstSelection(void){
    printf("************************************************\n");
    printf("Select the player that you would like to move:\n"); 
    printf("Enter 'undo' to undo your last move\n");
    printf("Enter 'hint' to print out a hint\n\n");
    printf("Enter the game board coordinate\n");
    printf("(Column-Row) format for example 'a1':\n");
    printf("(Enter q to abort the game:\n");
    printf("Enter your selection:");
}






//prints the menu to select where to move the piece
void PrintSecondMenu(void){
        printf("Enter the destination coordinate for your piece: \n");
        printf("(Column-Row) format for example 'a1':\n");
        printf("Enter q to abort the game:\n");
        printf("Enter your selection:");
} 
 


//prints out the move that was taken by the user
void printmove(GBOARD *board){
		char previousColumn = board->pcolum;
		int previousRow = board->prow;
		char column = board->colum;
		int row = board->row;
	
		int pieceCol = 0;
		if (column == 'a')	{
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

		int pieceNumber = (((row - 1) * 8) + pieceCol);
      
		char pieceConversion = board->piece[pieceNumber];
                printf("\n");
                printf("\n");
                printf("*******************************************\n");
                printf("        The move that was made is:\n");
		printf("               %c %c%d to %c%d\n",pieceConversion, previousColumn, previousRow, column, row);

}



void printmovebest(GBOARD *board){
		char previousColumn = board->pcolum;
		int previousRow = board->prow;
		char column = board->colum;
		int row = board->row;
	
		int pieceCol = 0;
		if (column == 'a')	{
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

		int pieceNumber = (((row - 1) * 8) + pieceCol);
      
		char pieceConversion = board->piece[pieceNumber];
                printf("\n");
                printf("\n");
                printf("*******************************************\n");
                printf("        Here is your move hint:\n");
		printf("               %c %c%d to %c%d\n",pieceConversion, previousColumn, previousRow, column, row);

}




//prints out a hint for a move to the user
void printhint(GAME *game){
    GBOARD *bestBoard;
    TNODE *tree;
    TNODE *bestNode;
    tree = CreateTree();
    assert(tree);
    tree->board = CopyBoard(game->currentBoard); 
    assert(tree->board);
    assert(tree->list);
    bestNode = minimax(tree,game->difficultyLevel,tree->board->playerflag);  
    bestBoard = ReturnBranchBoard(bestNode);
    assert(bestNode->board);
    printmovebest(bestBoard);
    DeleteTree(tree);
    tree = NULL;
    return;
}











//EOF



