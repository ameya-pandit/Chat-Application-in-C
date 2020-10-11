/*This is the main module for ChessGame*/
/*Team 4                               */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SLEN 8

//Function headers for the funcitons that are included in the main module
void PrintMainMenu(void);




//main function


int main(void) {
	
    int gameType = -1;
    PrintMainMenu();

    char GameString[SLEN];

    printf("Please enter your selection:");
    scanf("%1s", GameString);
    
    //input validation for gameType
    while(gameType < 0) { 
        if(strcmp(GameString,"0") == 0) {
            printf("Game ended\n");
            exit(10);
        } else {
        if(strcmp(GameString, "1") == 0) {
            printf("Player vs Player selected\n");
            gameType = atoi(GameString);
        } else {
        if(strcmp(GameString, "2") == 0) {
            printf("Player vs Computer selected\n");
            gameType = atoi(GameString);
        } else { 
        if(strcmp(GameString, "3") == 0) {
            printf("Computer vs Computer selected\n");
            gameType = atoi(GameString);
        } else {
            while(getchar() != '\n');//clear the input stream
            printf("Please enter a valid option:");
            scanf("%1s", GameString);
        }}}}
    }//end input validation








}//end of main


void PrintMainMenu(void) {

    printf("*****************************************************\n");
    printf("          ** Welcome to Computer Chess **\n");
    printf("                     Main Menu\n\n");
    printf(" 1: Press 1 to play against another player.\n");
    printf(" 2: Press 2 to play against the computer.\n");
    printf(" 3: Press 3 to let the computer play against itself.\n");
    printf(" 4: Press 0 to quit.\n");


}
















