//
//  Board.h
//  GameBoard
//
//  Created by Matthew Dunn on 1/12/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

//This file contains the functions that handle the double linked list of moves






#include <stdio.h>
#include "ChessStruct.h"
#include "Ai.h"
#include "Board.h"
#include "ChessTree.h"
#include <stdlib.h>
#include "ChessIO.h"
#include <assert.h>
#include "GameLog.h"
#include "playersmove.h"
#include "Moves.h"



int main(void){

        int choi; //Player choice
        int lay;  //Layout of the game board 1 for standard and 2 for custom.
	char player1color;//color that the user would like to play
        int userFirst;//var that determines if AI or player is first

        GAME *game;
        game = malloc(sizeof(GAME));//creating a game 
        game->win = 0;//setting the initial win condition for the game
        game->currentBoard = CreateBoard(); //creating the initial board
        game->log = CreateTree(); //creating the log list
      
        PrintMainMenu();
        choi = GetGameType();
        
        game->gameType = choi;
	
        //get the color menu from the user if the user is going first
        if((game->gameType != 3) && (game->gameType != 1)){
            PrintColorMenu();
            player1color = GetGameColor();
        }
        //print out the menu for difficulty level
        if(game->gameType != 1){
            PrintLevelMenu();
            game->difficultyLevel = GetGameLevel();
        } 
        //set the control for which user is first   
        if(player1color == 'w'){
            game->currentBoard->playerflag = 1;
            userFirst = 1;
            game->currentBoard->aimove = 2;
        }
        if(player1color == 'b'){
            game->currentBoard->playerflag = 2;
            userFirst = 2;
            game->currentBoard->aimove = 1;
        }
        
        //git the board type from the user
        PrintBoardMenu();
	lay = GetBoardType();
        InitializeBoard((lay -1),game->currentBoard);
        
        //player vs player
        if(game->gameType == 1){
            int control = 0;
            game->difficultyLevel = 3;
            //White always goes first
            game->currentBoard->playerflag = 1;
            PrintBoard(game->currentBoard); 
            AddMoveToLog(game);
            //game loop. Ends when user quits (control) or win changes   
            while((game->win == 0) && (control == 0)){
                    control = playersmove(game);
                    assert(game->currentBoard);
                    if(control == 0){
                        PrintBoard(game->currentBoard);
                        checkpromote(game->currentBoard);
                        printmove(game->currentBoard);
                    }
                    //checks for checkmate or stalemate
                    checkwin(game);
                    //logs the moves
                    AddMoveToLog(game); 
            }
        }
        //PVC mode
        if(game->gameType == 2){
            int control = 0;
            PrintBoard(game->currentBoard); 
            AddMoveToLog(game);
            if(userFirst == 1){ 
                //game loop ends when player quits or win condition changes
                while((game->win == 0) && (control == 0)){
                    //human goes first if they are playing white
                    if(userFirst == 1){
                        game->currentBoard->aimove = 0;
                        control = playersmove(game);
                        assert(game->currentBoard);
                        if(control == 0){
                            PrintBoard(game->currentBoard);
                            checkpromote(game->currentBoard);
                            printmove(game->currentBoard);
                        }
                        checkwin(game);
                        AddMoveToLog(game);
                    }    
                    //Ai turn
                    if(control == 0){
                        game->currentBoard->aimove = 1;
                        GetBestMove(game);
                        assert(game->currentBoard);
                        PrintBoard(game->currentBoard);
                        printmove(game->currentBoard);
                        checkwin(game);
                        AddMoveToLog(game);  
                        userFirst = 1; 
                    }
                }
            }
            else{
                game->currentBoard->playerflag = 1;
                while((game->win == 0) && (control == 0)){
                    //human goes second
                    if(userFirst == 1){
                        game->currentBoard->aimove = 0;
                        control = playersmove(game);
                        assert(game->currentBoard);
                        if(control == 0){
                            PrintBoard(game->currentBoard);
                            checkpromote(game->currentBoard);
                            printmove(game->currentBoard);
                        }
                        checkwin(game);
                        AddMoveToLog(game);
                    }    //Ai turn
                    if(control == 0){
                        game->currentBoard->aimove = 1;
                        GetBestMove(game);
                        assert(game->currentBoard);
                        PrintBoard(game->currentBoard);
                        printmove(game->currentBoard);
                        checkwin(game);
                        AddMoveToLog(game);  
                        userFirst = 1; 
                    }
                }
            }
            logOfMoves(game->log);
        }
        //CVC mode
        if(game->gameType == 3){
            PrintBoard(game->currentBoard);
            AddMoveToLog(game);
            int control = 2;
               
            game->currentBoard->playerflag = 1;
            game->currentBoard->aimove = 1;
            while((game->win == 0) && (control != 0)){
                PrintControlMenu();
                control = GetControl();
                //run the AI move sequence as long as the user keeps allowing
                if(control == 1){
                    GetBestMove(game);
                    assert(game->currentBoard);
                    PrintBoard(game->currentBoard);
                    printmove(game->currentBoard);
                    checkwin(game);
                    //adding the move to the log
                    AddMoveToLog(game);
                }
            }
           
            //Save the move log to a file
            logOfMoves(game->log);           
       }
            //Memory cleanup      
       DeleteBoard(game->currentBoard);
       DeleteTree(game->log);
       free(game);
       game = NULL;
        
}




//EOF



