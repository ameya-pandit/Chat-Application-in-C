/***********************************************************
*
*A simple GTK example
*simple.h: show a 2x2 board and move the king by clicking
*author: Weiwei Chen
*initial version: 01/22/13 EECS22L Winter 2013
*
***********************************************************/

#ifndef _SIMPLE_H
#define _SIMPLE_H


#define MAX_MSGLEN  100 
#define SQUARE_SIZE 50  
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH  (2*SQUARE_SIZE)
#define BOARD_HEIGHT (2*SQUARE_SIZE)
#define WINDOW_WIDTH  (BOARD_WIDTH + 2*BOARD_BORDER)
#define WINDOW_HEIGHT (BOARD_HEIGHT + 2*BOARD_BORDER)

enum GRID
{
	BLACK = 0,
	WHITE = 1,
	KING
};


#endif
