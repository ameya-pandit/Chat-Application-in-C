




#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "ChessStruct.h"




//Prints out the main menu
void PrintMainMenu(void);

//gets the game color from the user
int GetGameColor(void);
	
//gets the game type from the user
int GetGameType(void);
	
//gets the board type from the user
int GetBoardType(void);

//gets the game level from the user
int GetGameLevel(void);

//gets the control for computer vs computer
int GetControl(void);

//prints out the move that was made at every point of the game
void printmove(GBOARD *board);

//prints out the move that was made at every point of the game
void printmovebest(GBOARD *board);

//prints out the menue for color selection
void PrintColorMenu(void);

//prints the menu for the user to select difficulty level
void PrintLevelMenu(void);

//prints out the menu for board layout selection
void PrintBoardMenu(void);

//prints out the menu to allow the user to advance AI game
void PrintControlMenu(void);

//print out a hint for the player
void printhint(GAME *game);

//prints the menu to select a move
void PrintFirstSelection(void);

//prints the menu to select where to move the piece
void PrintSecondMenu(void);
 
 
#endif
