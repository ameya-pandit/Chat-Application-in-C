//
//  GameLog.h
//  
//
//  Created by Ameya Pandit on 1/23/19.
//

#ifndef GameLog_h
#define GameLog_h

#include "ChessStruct.h"

void AddMoveToLog(GAME *game);
 
void undoComputer(GAME *game);

void undoPlayer(GAME *game);

void logOfMoves(TNODE *tree);

#endif /* GameLog_h */
