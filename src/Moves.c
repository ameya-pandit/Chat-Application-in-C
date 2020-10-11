
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

//This is the definition for the functions that operate on the chess tree
#include <assert.h>
#include "ChessStruct.h" 
#include "MovesList.h"
#include "Board.h"
#include "ChessTree.h"
#include "Moves.h"
#include "playersmove.h"
#define WIDTH 8


//This is the function that will generate all of the possible moves that a peice can make
void checkmove(TNODE *allmoves){
    assert(allmoves);
    assert(allmoves->board);

    for(int y = 0; y < WIDTH; y++){
        for(int x = 0; x < WIDTH; x++){
            int flag;
            char piece;

            flag = 0;
            piece = GetPlayer(x,y,allmoves->board);       
 
             //Determines if piece is for the right player
            if(allmoves->board->playerflag==1){
                if((piece=='K')||(piece=='Q')||(piece=='R')||(piece=='B')||(piece=='N')||(piece=='P')){
                    flag = 1;
                }
            }
            if(allmoves->board->playerflag==2){
                if((piece=='k')||(piece=='q')||(piece=='r')||(piece=='b')||(piece=='n')||(piece=='p')){
                    flag = 1;
                }
            }
        
        if(flag == 1){
             if((piece=='K')||(piece=='k')){
                 kingmoves(allmoves->board,x,y, allmoves);
             }
             if((piece=='Q')||(piece=='q')){
                 queenmoves(allmoves->board,x,y, allmoves);
             }
             if((piece=='R')||(piece=='r')){
                 rookmoves(allmoves->board,x,y, allmoves);
             }
             if((piece=='B')||(piece=='b')){
                 bishopmoves(allmoves->board,x,y, allmoves);
             }
             if((piece=='N')||(piece=='n')){
                 knightmoves(allmoves->board,x,y, allmoves);
             }
             if((piece=='p')||(piece=='P')){
                 pawnmoves(allmoves->board, x,y, allmoves);
             }
       }
    }
    }
    return;
}//End of Checkmove



//Get the value in the array position
char GetPlayer(int column, int row, GBOARD *board){
    assert(board);
    char temp;
    assert(board);
    temp = board->piece[row*8 + column];
    return temp;         
}//End of GetPlayer





//Put the value of the player
void PutPlayer(int column, int row, GBOARD *board, char player){
    assert(board);
    board->piece[row*8 + column] = player;
    return;   
}//End of PutPlayer




//Set the players variables for the move
void SetVariables(GBOARD *board, int row, int prow, int column, int pcolumn){
    int temp;
    temp = board->playerflag;

    assert(board);
    board->row = row + 1;
    board->prow = prow + 1;
    board->colum = column + 97;
    board->pcolum = pcolumn + 97;
    if(temp == 1){
        board->playerflag = 2;
    }
    if(temp == 2){
        board->playerflag = 1;
    }
    return;
}//End of SetVariables







//check if player can make the move returns 1 if the spot is empty or has the opponents player;
int CheckIfValid(char move, int player){


    if(move == ' '){
        return 1;
    }
    if(player == 1){
        if((move=='k')||(move=='q')||(move=='r')||(move=='b')||(move=='n')||(move=='p')){
            return 2;
        }
    }
    if(player == 2){
        if((move=='K')||(move=='Q')||(move=='R')||(move=='B')||(move=='N')||(move=='P')){
            return 2;
        }
    }
    return 0;
}//End of CheckIfValid



//Rookmoves rules
void rookmoves(GBOARD *board, int column, int row, TNODE *tree){
    assert(board);
    assert(tree);
    IterateVertical(tree,board,column,row);
    IterateHorizontal(tree,board,column,row);
    return;
}//End of rookmoves


//Bishop rules
void bishopmoves(GBOARD *board, int column, int row, TNODE *tree){
    assert(board);
    assert(tree);
    IterateUpDiag(tree,board,column,row);
    IterateDownDiag(tree,board,column,row);

    return;
}//End of bishop


//Queen moves rules
void queenmoves(GBOARD *board, int column, int row, TNODE *tree){
    assert(board);
    assert(tree);
    IterateVertical(tree,board,column,row);
    IterateHorizontal(tree,board,column,row);
    IterateUpDiag(tree,board,column,row);
    IterateDownDiag(tree,board,column,row);
    return;
}//End of queenmoves


//King moves rules
void kingmoves(GBOARD *board, int column, int row, TNODE *tree){
    assert(board);
    assert(tree);
    IterateVertK(tree,board,column,row);
    IterateHorizK(tree,board,column,row);
    IterateUpDiagK(tree,board,column,row);
    IterateDownDiagK(tree,board,column,row);
    Castling(tree,board,column,row);
    return;
}//end of kingmoves


//Pawn moves rules
void pawnmoves(GBOARD *board, int column, int row, TNODE *tree){
    assert(board);
    assert(tree);
    IterateVertP(tree,board,column,row);
    IterateUpDiagP(tree,board,column,row);
    IterateDownDiagP(tree,board,column,row);
    Enpassant(tree,board,column,row);
    return;
}//End of pawnmoves



//Knight moves rules
void knightmoves(GBOARD *board, int column, int row, TNODE *tree){
    assert(board);
    assert(tree);
    IterateUpDiag2over(tree,board,column,row);
    IterateDownDiag2over(tree,board,column,row);
    IterateUpDiag2up(tree,board,column,row);
    IterateDownDiag2down(tree,board,column,row); 
    return;
}//End of knightmoves



//Iterates vertical and stops when it reaches players own piece or captures another players piece
void IterateVertical(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    while(i < ((WIDTH - 1) - row)){
        temp = GetPlayer(column,(row + i + 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
   //         SetVariables(newBoard,(row + i + 1),row,column,column);
            if (GetPlayer(column,row,newBoard)=='r'){
                if(column==0 && row==7){
                    newBoard->castling[3]=1;   
                }
                if (column==7 && row==7){
                    newBoard->castling[4]=1;
                }
            }
            else if(GetPlayer(column,row,newBoard)=='R'){
                if(column==0 && row==0){
                    newBoard->castling[0]=1;   
                }
                if (column==7 && row==0){
                    newBoard->castling[1]=1;
                }
            }
            PutPlayer(column,(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
        
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row + i + 1),row,column,column);
    
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        i++;
    }
    i = 0;
    while(i < row){
        temp = GetPlayer(column,(row - i - 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
 //           SetVariables(newBoard,(row - i - 1),row,column,column);
            if (GetPlayer(column,row,newBoard)=='r'){
                if(column==0 && row==7){
                    newBoard->castling[3]=1;   
                }
                if (column==7 && row==7){
                    newBoard->castling[4]=1;
                }
            }
            else if(GetPlayer(column,row,newBoard)=='R'){
                if(column==0 && row==0){
                    newBoard->castling[0]=1;   
                }
                if (column==7 && row==0){
                    newBoard->castling[1]=1;
                }
            }
            PutPlayer(column,(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
        
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row - i - 1),row,column,column);
       
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        i++;
    }
    return;
}//End of IterateVertical



//Iterates horizontal and stops when it reaches players own piece or captures another players piece
void IterateHorizontal(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    while(i < ((WIDTH - 1) - column)){
        temp = GetPlayer((column + i + 1),row,board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
   //         SetVariables(newBoard,row,row,(column + i + 1),column);
            if (GetPlayer(column,row,newBoard)=='r'){
                if(column==0 && row==7){
                    newBoard->castling[3]=1;   
                }
                if (column==7 && row==7){
                    newBoard->castling[4]=1;
                }
            }
            else if(GetPlayer(column,row,newBoard)=='R'){
                if(column==0 && row==0){
                    newBoard->castling[0]=1;   
                }
                if (column==7 && row==0){
                    newBoard->castling[1]=1;
                }
            }
            PutPlayer((column + i + 1),row,newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
        

            if(CheckCheck(newBoard,board->playerflag) == 0){
            SetVariables(newBoard,row,row,(column + i + 1),column);
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        i++;
    }
    i = 0;
    while(i < column){
        temp = GetPlayer((column - i - 1),row ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
 //           SetVariables(newBoard,row,row,(column - i - 1),column);
            if (GetPlayer(column,row,newBoard)=='r'){
                if(column==0 && row==7){
                    newBoard->castling[3]=1;   
                }
                if (column==7 && row==7){
                    newBoard->castling[4]=1;
                }
            }
            else if(GetPlayer(column,row,newBoard)=='R'){
                if(column==0 && row==0){
                    newBoard->castling[0]=1;   
                }
                if (column==7 && row==0){
                    newBoard->castling[1]=1;
                }
            }
            PutPlayer((column - i - 1),row,newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
        
            if(CheckCheck(newBoard,board->playerflag) == 0){
 
             SetVariables(newBoard,row,row,(column - i - 1),column);
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        i++;
    }
}//End of IterateHorizontal






//Iterates up diagonally and stops when it reaches players own piece or captures another players piece
void IterateUpDiag(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    while((i < ((WIDTH - 1) - row)) && (i < ((WIDTH - 1) - column))){
        temp = GetPlayer((column + i + 1),(row + i + 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
   //         SetVariables(newBoard,(row + i + 1),row,(column + i + 1),column);
            PutPlayer((column + i + 1),(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row + i + 1),row,(column + i + 1),column);
     
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        i++;
    }
    i = 0;
    while((i < row) && (i < column)){
        temp = GetPlayer((column - i - 1),(row - i - 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
 //           SetVariables(newBoard,(row - i - 1),row,(column - i - 1),column);
            PutPlayer((column - i - 1),(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row - i - 1),row,(column - i - 1),column);
  
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        i++;
    }
    return;
}//End of IterateUpDiag






//Iterates down diagonally and stops when it reaches players own piece or captures another players piece
void IterateDownDiag(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    while((i < ((WIDTH - 1) - column)) && (i < row)){
        temp = GetPlayer((column + i + 1),(row - i - 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
   //         SetVariables(newBoard,(row - i - 1),row,(column + i + 1),column);
            PutPlayer((column + i + 1),(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row - i - 1),row,(column + i + 1),column);
    
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        i++;
    }
    i = 0;
    while((i < column) && (i < ((WIDTH - 1) - row))){
        temp = GetPlayer((column - i - 1),(row + i + 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
 //           SetVariables(newBoard,(row + i + 1),row,(column - i - 1),column);
            PutPlayer((column - i - 1),(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row + i + 1),row,(column - i - 1),column);
 
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        i++;
    }
    return;
}//End of IterateDownDiag



int CheckCheck(GBOARD *board, int flag){
    assert(board);
    int row = 0;
    int column = 0;
    int check = 0;

    //find the king
    for(int y = 0; y < WIDTH; y++){
        for(int x = 0; x < WIDTH; x++){
            char piece;
            piece = GetPlayer(x,y,board);       
            if((flag == 1) && (piece == 'K')){
                row = y;
                column = x;
 
            }
            if((flag == 2) && (piece == 'k')){
                row = y;
                column = x;
            }  
        }
    }
    if(check == 0){
        check = IterateVerticalCheck(board,column,row); 
    }
    if(check == 0){
         check = IterateHorizontalCheck(board,column,row);
    }
    if(check == 0){
         check = IterateUpDiagCheck(board,column,row);
    }
    if(check == 0){ 
         check = IterateDownDiagCheck(board,column,row);
    }
    if(check == 0){
         check = IterateUpDiag2upCheck(board,column,row);
    }
    if(check == 0){
         check = IterateDownDiag2downCheck(board,column,row);
    }
    if(check == 0){
         check = IterateUpDiag2overCheck(board,column,row);
    }
    if(check == 0){
         check = IterateDownDiag2overCheck(board,column,row);
    }
    return check;
}//End of checkcheck








//Iterates vertical and stops when it reaches players own piece or captures another players piece
void IterateVertK(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    while(i < ((WIDTH - 1) - row)){
        temp = GetPlayer(column,(row + i + 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
   //         SetVariables(newBoard,(row + i + 1),row,column,column);
            PutPlayer(column,(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
            if(temp=='k'){
                newBoard->castling[5]=1;
            }
            else if(temp=='K'){
                newBoard->castling[2]=1;
            }
 
            if(CheckCheck(newBoard,board->playerflag) == 0){
    
             SetVariables(newBoard,(row + i + 1),row,column,column);
 
               AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    i = 0;
    while(i < row){
        temp = GetPlayer(column,(row - i - 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
 //           SetVariables(newBoard,(row - i - 1),row,column,column);
            PutPlayer(column,(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
            if(temp=='k'){
                newBoard->castling[5]=1;
            }
            else if(temp=='K'){
                newBoard->castling[2]=1;
            }
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row - i - 1),row,column,column);
  
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    return;
}//End of IterateVertk



//Iterates horizontal and stops when it reaches players own piece or captures another players piece
void IterateHorizK(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   
    while(i < ((WIDTH - 1) - column)){
        temp = GetPlayer((column + i + 1),row,board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
            PutPlayer((column + i + 1),row,newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
            if(temp=='k'){
                newBoard->castling[5]=1;
            }
            else if(temp=='K'){
                newBoard->castling[2]=1;
            }
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,row,row,(column + i + 1),column);
  
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    i = 0;
    while(i < column){
        temp = GetPlayer((column - i - 1),row ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
 //           SetVariables(newBoard,row,row,(column - i - 1),column);
            PutPlayer((column - i - 1),row,newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
            if(temp=='k'){
                newBoard->castling[5]=1;
            }
            else if(temp=='K'){
                newBoard->castling[2]=1;
            }
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,row,row,(column - i - 1),column);
  
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    return;
}//End of IterateHorizK





//Iterates up diagonally and stops when it reaches players own piece or captures another players piece
void IterateUpDiagK(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    while((i < ((WIDTH - 1) - row)) && (i < ((WIDTH - 1) - column))){
        temp = GetPlayer((column + i + 1),(row + i + 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
   //         SetVariables(newBoard,(row + i + 1),row,(column + i + 1),column);
            PutPlayer((column + i + 1),(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
            if(temp=='k'){
                newBoard->castling[5]=1;
            }
            else if(temp=='K'){
                newBoard->castling[2]=1;
            }
            if(CheckCheck(newBoard,board->playerflag) == 0){
    
             SetVariables(newBoard,(row + i + 1),row,(column + i + 1),column);
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    i = 0;
    while((i < row) && (i < column)){
        temp = GetPlayer((column - i - 1),(row - i - 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
 //           SetVariables(newBoard,(row - i - 1),row,(column - i - 1),column);
            PutPlayer((column - i - 1),(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
            if(temp=='k'){
                newBoard->castling[5]=1;
            }
            else if(temp=='K'){
                newBoard->castling[2]=1;
            }
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row - i - 1),row,(column - i - 1),column);
 
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    return;
}//End of IterateUpDiagK





//Iterates down diagonally and stops when it reaches players own piece or captures another players piece
void IterateDownDiagK(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    while((i < ((WIDTH - 1) - column)) && (i < row)){
        temp = GetPlayer((column + i + 1),(row - i - 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
   //         SetVariables(newBoard,(row - i - 1),row,(column + i + 1),column);
            PutPlayer((column + i + 1),(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
            if(temp=='k'){
                newBoard->castling[5]=1;
            }
            else if(temp=='K'){
                newBoard->castling[2]=1;
            }
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row - i - 1),row,(column + i + 1),column);
    
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    i = 0;
    while((i < column) && (i < ((WIDTH - 1) - row))){
        temp = GetPlayer((column - i - 1),(row + i + 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
 //           SetVariables(newBoard,(row + i + 1),row,(column - i - 1),column);
            PutPlayer((column - i - 1),(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
            if(temp=='k'){
                newBoard->castling[5]=1;
            }
            else if(temp=='K'){
                newBoard->castling[2]=1;
            }
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row + i + 1),row,(column - i - 1),column);
 
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    return;
}//End of IterateDownDiagK






//Iterates vertical and stops when it reaches players own piece or captures another players piece
void IterateVertP(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);
    int startingRow = row;

    if(board->playerflag == 1){
        while(i < ((WIDTH - 1) - row)){
            temp = GetPlayer(column,(row + i + 1),board);
            playerFlag = CheckIfValid(temp,board->playerflag);

            if(playerFlag == 1){
                GBOARD *newBoard;
                newBoard = CopyBoard(board);
                if((board->aimove == 1) && ((row + i + 1) == 7)){
                    if((GetPlayer(column,row,board) == 'P')){
                        PutPlayer(column,(row + i + 1),newBoard, 'Q');
                    } 
                } else {
                    PutPlayer(column,(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
                }
                PutPlayer(column,row,newBoard,' ');
 
                if(CheckCheck(newBoard,board->playerflag) == 0){
                    SetVariables(newBoard,(row + i + 1),row,column,column);
                    AppendListNode(tree,newBoard); 
                } else {
                    DeleteBoard(newBoard);
                }
            }
            if(playerFlag == 2){
                break;
            }
            if(playerFlag == 0){
                break;
            }
            if(startingRow == 1){
                i++;
                startingRow++;
            } else {
            break;
            }
        }
    }

    i = 0;

    if(board->playerflag == 2){
        while(i < row){
            temp = GetPlayer(column,(row - i - 1) ,board);
            playerFlag = CheckIfValid(temp,board->playerflag);
 
            if(playerFlag == 1){
                GBOARD *newBoard;
                newBoard = CopyBoard(board);
                if((board->aimove == 1) && ((row - i - 1) == 0)){
                    if((GetPlayer(column,row,board)  == 'p')){
                        PutPlayer(column,(row - i - 1),newBoard,'q');
                    } 
                } else {
                    PutPlayer(column,(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
                }
                PutPlayer(column,row,newBoard,' '); 
                if(CheckCheck(newBoard,board->playerflag) == 0){
                    SetVariables(newBoard,(row - i - 1),row,column,column);
                    AppendListNode(tree,newBoard); 
                } else {
                    DeleteBoard(newBoard);
                }
            }
            if(playerFlag == 2){
                break;
            }
            if(playerFlag == 0){
                break;
            }
            if(startingRow == 6){
                i++;
                startingRow++;
            } else {
                break;
            } 
        }
    }
    return;
}//End of IterateVertP





//Iterates up diagonally and stops when it reaches players own piece or captures another players piece
void IterateUpDiagP(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    if(board->playerflag == 1){
        while((i < ((WIDTH - 1) - row)) && (i < ((WIDTH - 1) - column))){
            temp = GetPlayer((column + i + 1),(row + i + 1),board);
            playerFlag = CheckIfValid(temp,board->playerflag);

            if(playerFlag == 2){
                GBOARD *newBoard;
                newBoard = CopyBoard(board);
                if((board->aimove == 1)  && ((row + i + 1) == 7)){
                    if((GetPlayer(column,row,board) == 'P')){
                        PutPlayer((column + i + 1),(row + i + 1),newBoard, 'Q');
                    } 
                } else {
                    PutPlayer((column + i + 1),(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
                }
                PutPlayer(column,row,newBoard,' ');
                if(CheckCheck(newBoard,board->playerflag) == 0){
                 SetVariables(newBoard,(row + i + 1),row,(column + i + 1),column);
 
 
                    AppendListNode(tree,newBoard); 
                } else {
                    DeleteBoard(newBoard);
                }
                break;
            }
            if(playerFlag == 0){
                break;
            }
            break;
        }
    }
    i = 0;
 
    if(board->playerflag == 2){
        while((i < row) && (i < column)){
            temp = GetPlayer((column - i - 1),(row - i - 1) ,board);
            playerFlag = CheckIfValid(temp,board->playerflag);
 
            if(playerFlag == 2){
                GBOARD *newBoard;
                newBoard = CopyBoard(board);
                if((board->aimove == 1) && ((row - i - 1) == 0)){
                    if((GetPlayer(column,row,board)  == 'p')){
                        PutPlayer((column - i - 1),(row - i - 1),newBoard,'q');
                    } 
                } else {
                    PutPlayer((column - i - 1),(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
                }
                PutPlayer(column,row,newBoard,' '); 
                if(CheckCheck(newBoard,board->playerflag) == 0){
                 SetVariables(newBoard,(row - i - 1),row,(column - i - 1),column);
  
                   AppendListNode(tree,newBoard); 
                } else {
                    DeleteBoard(newBoard);
                }
                break;
            }
            if(playerFlag == 0){
                break;
            }
            break;
        }
    }
    return;
}//End of IterateUpDiagP







//Iterates down diagonally and stops when it reaches players own piece or captures another players piece
void IterateDownDiagP(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    if(board->playerflag == 2){
        while((i < ((WIDTH - 1) - column)) && (i < row)){
            temp = GetPlayer((column + i + 1),(row - i - 1),board);
            playerFlag = CheckIfValid(temp,board->playerflag);

            if(playerFlag == 2){
                GBOARD *newBoard;
                newBoard = CopyBoard(board);
                if((board->aimove == 1) && ((row - i - 1) == 0)){
                    if((GetPlayer(column,row,board) == 'p')){
                        PutPlayer((column + i + 1),(row - i - 1),newBoard, 'q');
                    } 
                } else {
                    PutPlayer((column + i + 1),(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
                }
                PutPlayer(column,row,newBoard,' ');
                if(CheckCheck(newBoard,board->playerflag) == 0){
                    SetVariables(newBoard,(row - i - 1),row,(column + i + 1),column);
               
                    AppendListNode(tree,newBoard); 
                } else {
                    DeleteBoard(newBoard);
                }
                break;
            }
            if(playerFlag == 0){
                break;
            }
            break;
        }
    }

    i = 0;

    if(board->playerflag == 1){
        while((i < column) && (i < ((WIDTH - 1) - row))){
            temp = GetPlayer((column - i - 1),(row + i + 1) ,board);
            playerFlag = CheckIfValid(temp,board->playerflag);
 
            if(playerFlag == 2){
                GBOARD *newBoard;
                newBoard = CopyBoard(board);
                if((board->aimove == 1) && ((row + i + 1) == 7)){
                    if((GetPlayer(column,row,board)  == 'P')){
                        PutPlayer((column - i - 1),(row + i + 1),newBoard,'Q');
                    } 
                } else {
                    PutPlayer((column - i - 1),(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
                }
                PutPlayer(column,row,newBoard,' '); 
                if(CheckCheck(newBoard,board->playerflag) == 0){
                 SetVariables(newBoard,(row + i + 1),row,(column - i - 1),column);
                    AppendListNode(tree,newBoard);
                } else {
                    DeleteBoard(newBoard);
                }
                break;
            }
            if(playerFlag == 0){
                break;
            }
            break;
        }
    }
    return;
}//End of IterateDownDiagp








//Iterates up diagonally and stops when it reaches players own piece or captures another players piece
void IterateUpDiag2up(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    while((i < ((WIDTH - 1) - (row + 1))) && (i < ((WIDTH - 1) - column))){
        temp = GetPlayer((column + i + 1),(row + i + 2),board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
   //         SetVariables(newBoard,(row + i + 2),row,(column + i + 1),column);
            PutPlayer((column + i + 1),(row + i + 2),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row + i + 2),row,(column + i + 1),column);
    
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    i = 0;
    while((i < (row - 1)) && (i < column)){
        temp = GetPlayer((column - i - 1),(row - i - 2) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
 //           SetVariables(newBoard,(row - i - 2),row,(column - i - 1),column);
            PutPlayer((column - i - 1),(row - i - 2),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
            if(CheckCheck(newBoard,board->playerflag) == 0){
            SetVariables(newBoard,(row - i - 2),row,(column - i - 1),column);
 
                AppendListNode(tree,newBoard);
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    return;
}//End of IterateUpDiag2up







//Iterates up diagonally and stops when it reaches players own piece or captures another players piece
void IterateUpDiag2over(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    while((i < ((WIDTH - 1) - row)) && (i < ((WIDTH - 1) - (column + 1)))){
        temp = GetPlayer((column + i + 2),(row + i + 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
   //         SetVariables(newBoard,(row + i + 1),row,(column + i + 2),column);
            PutPlayer((column + i + 2),(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
            if(CheckCheck(newBoard,board->playerflag) == 0){
    
             SetVariables(newBoard,(row + i + 1),row,(column + i + 2),column);
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    i = 0;
    while((i < row) && (i < (column - 1))){
        temp = GetPlayer((column - i - 2),(row - i - 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
 //           SetVariables(newBoard,(row - i - 1),row,(column - i - 2),column);
            PutPlayer((column - i - 2),(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
            if(CheckCheck(newBoard,board->playerflag) == 0){

             SetVariables(newBoard,(row - i - 1),row,(column - i - 2),column);
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    return;
}//End of IterateUpDiag2over








//Iterates down diagonally and stops when it reaches players own piece or captures another players piece
void IterateDownDiag2down(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    assert(tree);   

    while((i < ((WIDTH - 1) - column)) && (i < (row - 1))){
        temp = GetPlayer((column + i + 1),(row - i - 2),board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
   //         SetVariables(newBoard,(row - i - 2),row,(column + i + 1),column);
            PutPlayer((column + i + 1),(row - i - 2),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
            if(CheckCheck(newBoard,board->playerflag) == 0){
    
             SetVariables(newBoard,(row - i - 2),row,(column + i + 1),column);
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    i = 0;
    while((i < column) && (i < ((WIDTH - 1) - (row + 1)))){
        temp = GetPlayer((column - i - 1),(row + i + 2) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);           
 //           SetVariables(newBoard,(row + i + 2),row,(column - i - 1),column);
            PutPlayer((column - i - 1),(row + i + 2),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
            if(CheckCheck(newBoard,board->playerflag) == 0){
             SetVariables(newBoard,(row + i + 2),row,(column - i - 1),column);
 
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    return;
}//End of IterateDownDiag2down






//Iterates down diagonally and stops when it reaches players own piece or captures another players piece
void IterateDownDiag2over(TNODE *tree,GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board); 
    assert(tree);

    while((i < ((WIDTH - 1) - (column + 1))) && (i < row)){
        temp = GetPlayer((column + i + 1),(row - i - 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);

        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
  //          SetVariables(newBoard,(row - i - 1),row,(column + i + 2),column);
            PutPlayer((column + i + 2),(row - i - 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' ');
            if(CheckCheck(newBoard,board->playerflag) == 0){
            SetVariables(newBoard,(row - i - 1),row,(column + i + 2),column);
 
                AppendListNode(tree,newBoard); 
           
            } else {
                DeleteBoard(newBoard);
            }
 
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    i = 0;
    while((i < (column - 1)) && (i < ((WIDTH - 1) - (row + 1)))){
        temp = GetPlayer((column - i - 2),(row + i + 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if((playerFlag == 1) || (playerFlag == 2)){
            GBOARD *newBoard;
            newBoard = CopyBoard(board);
//            SetVariables(newBoard,(row + i + 1),row,(column - i - 2),column);
            PutPlayer((column - i - 2),(row + i + 1),newBoard,GetPlayer(column,row,newBoard));
            PutPlayer(column,row,newBoard,' '); 
            if(CheckCheck(newBoard,board->playerflag) == 0){
            SetVariables(newBoard,(row + i + 1),row,(column - i - 2),column);
 
                AppendListNode(tree,newBoard); 
            } else {
                DeleteBoard(newBoard);
            }
            if(playerFlag == 2){
                break;
            }
        }
        if(playerFlag == 0){
            break;
        }
        break;
    }
    return;
}//End of IterateDownDiag2over






//Iterates vertical and stops when it reaches players own piece or captures another players piece
int IterateVerticalCheck(GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);  
    int inCheck;

    while(i < ((WIDTH - 1) - row)){
        temp = GetPlayer(column,(row + i + 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if(i == 0){
            if((playerFlag == 2) && ((temp == 'k') || (temp == 'K'))){
                inCheck = 1;
                return inCheck;
            }
        }
        if((playerFlag == 2) && ((temp == 'q') || (temp == 'Q'))){
            inCheck = 1;
            return inCheck;
        } else {
        if((playerFlag == 2) && ((temp == 'r') ||(temp == 'R'))){
            inCheck = 1;
            return inCheck;
        } else {
        if(playerFlag == 2){
            break;
        }}}        
        i++;
    }

    i = 0;

    while(i < row){
        temp = GetPlayer(column,(row - i - 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if(i == 0){
            if((playerFlag == 2) && ((temp == 'k') || (temp == 'K'))){
                inCheck = 1;
                return inCheck;
            }
        } 
        if((playerFlag == 2) && ((temp == 'q') || (temp == 'Q'))){
            inCheck = 1;
            return inCheck;
        } else {
        if((playerFlag == 2) && ((temp == 'r') ||(temp == 'R'))){
            inCheck = 1;
            return inCheck;
        } else {
        if(playerFlag == 2){
            break;
        }}}         
        i++;
    }
    return 0;
}//End of IterateVerticalCheck






//Iterates horizontal and stops when it reaches players own piece or captures another players piece
int IterateHorizontalCheck(GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board); 
    int inCheck;

    while(i < ((WIDTH - 1) - column)){
        temp = GetPlayer((column + i + 1),row,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if(i == 0){
            if((playerFlag == 2) && ((temp == 'k') || (temp == 'K'))){
                inCheck = 1;
                return inCheck;
            }
        } 
        if((playerFlag == 2) && ((temp == 'q') || (temp == 'Q'))){
            inCheck = 1;
            return inCheck;
        } else {
        if((playerFlag == 2) && ((temp == 'r') ||(temp == 'R'))){
            inCheck = 1;
            return inCheck;
        } else {
        if(playerFlag == 2){
            break;
        }}}         
        i++;
    }
    i = 0;
    while(i < column){
        temp = GetPlayer((column - i - 1),row ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if(i == 0){
            if((playerFlag == 2) && ((temp == 'k') || (temp == 'K'))){
                inCheck = 1;
                return inCheck;
            }
        } 
        if((playerFlag == 2) && ((temp == 'q') || (temp == 'Q'))){
            inCheck = 1;
            return inCheck;
        } else {
        if((playerFlag == 2) && ((temp == 'r') ||(temp == 'R'))){
            inCheck = 1;
            return inCheck;
        } else {
        if(playerFlag == 2){
            break;
        }}}           
        i++;
    }
    return 0;
}//End of IterateHorizontalCheck








//Iterates up diagonally and stops when it reaches players own piece or captures another players piece
int IterateUpDiagCheck(GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    int inCheck; 

    while((i < ((WIDTH - 1) - row)) && (i < ((WIDTH - 1) - column))){
        temp = GetPlayer((column + i + 1),(row + i + 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if(i == 0){
            if((board->playerflag == 1) && (temp == 'p')){
                inCheck = 1;
                return inCheck;
            }
        } 
        if(i == 0){
            if((playerFlag == 2) && ((temp == 'k') || (temp == 'K'))){
                inCheck = 1;
                return inCheck;
            }
        } 
        if((playerFlag == 2) && ((temp == 'q') || (temp == 'Q'))){
            inCheck = 1;
            return inCheck;
        } else {
        if((playerFlag == 2) && ((temp == 'b') ||(temp == 'B'))){
            inCheck = 1;
            return inCheck;
        } else {
        if(playerFlag == 2){
            break;
        }}}        
 
        i++;
    }
    i = 0;
    while((i < row) && (i < column)){
        temp = GetPlayer((column - i - 1),(row - i - 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if(i == 0){
            if((board->playerflag == 2) && (temp == 'P')){
                inCheck = 1;
                return inCheck;
            }
        }  
        if(i == 0){
            if((playerFlag == 2) && ((temp == 'k') || (temp == 'K'))){
                inCheck = 1;
                return inCheck;
            }
        } 
        if((playerFlag == 2) && ((temp == 'q') || (temp == 'Q'))){
            inCheck = 1;
            return inCheck;
        } else {
        if((playerFlag == 2) && ((temp == 'b') ||(temp == 'B'))){
            inCheck = 1;
            return inCheck;
        } else {
        if(playerFlag == 2){
            break;
        }}}        
 
        i++;
    }
    return 0;
}//End of IterateUpDiagCheck







//Iterates down diagonally and stops when it reaches players own piece or captures another players piece
int IterateDownDiagCheck(GBOARD *board,int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);
    int inCheck;   
    while((i < ((WIDTH - 1) - column)) && (i < row)){
        temp = GetPlayer((column + i + 1),(row - i - 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);
 
        if(playerFlag == 0){
            break;
        }
        if(i == 0){
            if((board->playerflag == 2) && (temp == 'P')){
                inCheck = 1;
                return inCheck;
            }
        }  
        if(i == 0){
            if((playerFlag == 2) && ((temp == 'k') || (temp == 'K'))){
                inCheck = 1;
                return inCheck;
            }
        } 
        if((playerFlag == 2) && ((temp == 'q') || (temp == 'Q'))){
            inCheck = 1;
            return inCheck;
        } else {
        if((playerFlag == 2) && ((temp == 'b') ||(temp == 'B'))){
            inCheck = 1;
            return inCheck;
        } else {
        if(playerFlag == 2){
            break;
        }}}        
 
        i++;
    }
    i = 0;
    while((i < column) && (i < ((WIDTH - 1) - row))){
        temp = GetPlayer((column - i - 1),(row + i + 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
  
       if(playerFlag == 0){
            break;
        }
        if(i == 0){
            if((board->playerflag == 1) && (temp == 'p')){
                inCheck = 1;
                return inCheck;
            }
        }  
        if(i == 0){
            if((playerFlag == 2) && ((temp == 'k') || (temp == 'K'))){
                inCheck = 1;
                return inCheck;
            }
        } 
        if((playerFlag == 2) && ((temp == 'q') || (temp == 'Q'))){
            inCheck = 1;
            return inCheck;
        } else {
        if((playerFlag == 2) && ((temp == 'b') ||(temp == 'B'))){
            inCheck = 1;
            return inCheck;
        } else {
        if(playerFlag == 2){
            break;
        }}}        
 
        i++;
    }
    return 0;
}//End of IterateDownDiagCheck








//Iterates up diagonally and stops when it reaches players own piece or captures another players piece
int IterateUpDiag2upCheck(GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board); 
    int inCheck; 

    while((i < ((WIDTH - 1) - (row + 1))) && (i < ((WIDTH - 1) - column))){
        temp = GetPlayer((column + i + 1),(row + i + 2),board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if((playerFlag == 2) && ((temp == 'n') || (temp == 'N'))){
            inCheck = 1;
            return inCheck;
        } else {
            if(playerFlag == 2){
                break;
        }}         
        break;
    }
    i = 0;
    while((i < (row - 1)) && (i < column)){
        temp = GetPlayer((column - i - 1),(row - i - 2) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if((playerFlag == 2) && ((temp == 'n') || (temp == 'N'))){
            inCheck = 1;
            return inCheck;
        } else {
            if(playerFlag == 2){
                break;
        }}         
        break;
    }
    return 0;
}//End of IterateUpDiag2upCheck 






//Iterates up diagonally and stops when it reaches players own piece or captures another players piece
int IterateUpDiag2overCheck(GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);  
    int inCheck;

    while((i < ((WIDTH - 1) - row)) && (i < ((WIDTH - 1) - (column + 1)))){
        temp = GetPlayer((column + i + 2),(row + i + 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if((playerFlag == 2) && ((temp == 'n') || (temp == 'N'))){
            inCheck = 1;
            return inCheck;
        } else {
            if(playerFlag == 2){
                break;
        }}         
        
        break;
    }
    i = 0;
    while((i < row) && (i < (column - 1))){
        temp = GetPlayer((column - i - 2),(row - i - 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if((playerFlag == 2) && ((temp == 'n') || (temp == 'N'))){
            inCheck = 1;
            return inCheck;
        } else {
            if(playerFlag == 2){
                break;
        }}         
 
        break;
    }
    return 0;
}//End of IterateUpDiag2overCheck







//Iterates down diagonally and stops when it reaches players own piece or captures another players piece
int IterateDownDiag2downCheck(GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board);   
    int inCheck;

    while((i < ((WIDTH - 1) - column)) && (i < (row - 1))){
        temp = GetPlayer((column + i + 1),(row - i - 2),board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if((playerFlag == 2) && ((temp == 'n') || (temp == 'N'))){
            inCheck = 1;
            return inCheck;
        } else {
            if(playerFlag == 2){
                break;
        }}         
        break;
    }
    i = 0;
    while((i < column) && (i < ((WIDTH - 1) - (row + 1)))){
        temp = GetPlayer((column - i - 1),(row + i + 2) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if((playerFlag == 2) && ((temp == 'n') || (temp == 'N'))){
            inCheck = 1;
            return inCheck;
        } else {
            if(playerFlag == 2){
                break;
        }}          
        break;
    }
    return 0;
}//End of IterateDownDiag2downCheck





//Iterates down diagonally and stops when it reaches players own piece or captures another players piece
int IterateDownDiag2overCheck(GBOARD *board, int column, int row){
    int i = 0;
    char temp;
    int playerFlag;
    assert(board); 
    int inCheck;

    while((i < ((WIDTH - 1) - (column + 1))) && (i < row)){
        temp = GetPlayer((column + i + 1),(row - i - 1),board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if((playerFlag == 2) && ((temp == 'n') || (temp == 'N'))){
            inCheck = 1;
            return inCheck;
        } else {
            if(playerFlag == 2){
                break;
        }}          
 
        break;
    }
    i = 0;
    while((i < (column - 1)) && (i < ((WIDTH - 1) - (row + 1)))){
        temp = GetPlayer((column - i - 2),(row + i + 1) ,board);
        playerFlag = CheckIfValid(temp,board->playerflag);
        if(playerFlag == 0){
            break;
        }
        if((playerFlag == 2) && ((temp == 'n') || (temp == 'N'))){
            inCheck = 1;
            return inCheck;
        } else {
            if(playerFlag == 2){
                break;
        }}          
 
        break;
    }
    return 0;
}//End of IterateDownDiag2overCheck






int checkmate(GBOARD *board){
    TNODE *tree;
    int flag = 0;
 
    flag = CheckCheck(board,board->playerflag);
    if(flag == 1){
        tree = CreateTree();
        tree->board = CopyBoard(board);
        checkmove(tree);
        if(tree->list->first == NULL){
            DeleteTree(tree);
            return 1;
        } else {
            DeleteTree(tree);
            return 0;
        }
    }
    return 0;
}//End of checkmate
        
       
int stalemate(GBOARD *board){
    TNODE *tree;

    tree = CreateTree();
    tree->board = CopyBoard(board);
    checkmove(tree);
    if(tree->list->first == NULL){
        DeleteTree(tree);
        return 1;
    } else {
        DeleteTree(tree);
        return 0;
    }
}//End of stalemate
 



void checkwin(GAME *game){
    int win;

    win = checkmate(game->currentBoard);
    if(win == 1){
        game->win = 1;
        if(game->currentBoard->playerflag == 1){
            game->win = 1;
            printf("Checkmate! Player 2 wins!\n");
            return;
        }
        if(game->currentBoard->playerflag == 2){
            game->win = 1;
            printf("Checkmate! Player 1 wins!\n");
            return;
        }
    }
    win = stalemate(game->currentBoard);         
 
    if(win == 1){
        game->win = 1;
        if(game->currentBoard->playerflag == 1){
            game->win = 1;
            printf("Stalemate! Player 2 wins!\n");
            return;
        }
        if(game->currentBoard->playerflag == 2){
            game->win = 1;
            printf("Stalemate! Player 1 wins!\n");
            return;
        }
 
    }
}//End of check win



//Function for enpassant
void Enpassant(TNODE *tree,GBOARD *board, int column, int row){
    //Checks if player 1 can do an enpassant
    if (board->playerflag==1){
        //checks if the pawns are in the same row and if the pawn moved 2 spaces in the last move
        if (4==board->prow-3){
            GBOARD *enpassant;
            //checks the pawn to the right
            if(column+1<8  && GetPlayer(column+1, row, board)=='p' && GetPlayer(column+1,row+1,board)==' '){
                enpassant=CopyBoard(board);
                PutPlayer(column+1,row+1,enpassant,GetPlayer(column,row,enpassant));
                PutPlayer(column,row,enpassant,' '); 
                PutPlayer(column+1,row,enpassant,' '); 
                //checks if it puts player 1's king in check
                if(enpassant!=NULL && CheckCheck(enpassant,enpassant->playerflag) == 0){
                    SetVariables(enpassant,row+1,row,column+1,column);
                    AppendListNode(tree,enpassant); 
                } else if(enpassant!=NULL){
                    DeleteBoard(enpassant);
                }
            }
            //checks the pawn to the left
            else if(column-1>=0 && GetPlayer(column-1, row, board)=='p' && GetPlayer(column-1,row+1,board)==' '){
                enpassant=CopyBoard(board);
                PutPlayer(column-1,row+1,enpassant,GetPlayer(column,row,enpassant));
                PutPlayer(column,row,enpassant,' '); 
                PutPlayer(column-1,row,enpassant,' '); 
                //checks if it puts player 1's king in check
                if(enpassant!=NULL && CheckCheck(enpassant,enpassant->playerflag) == 0){
                    SetVariables(enpassant,row+1,row,column-1,column);
                    AppendListNode(tree,enpassant); 
                } else if(enpassant!=NULL){
                    DeleteBoard(enpassant);
                }
            }
        }
    }
    //Player 2
    else if (board->playerflag==2){
        //checks if the pawns are in the same row and if the pawn moved 2 spaces in the last move
        if (3==board->prow+1){
            GBOARD *enpassant;
            //checks the pawn to the right
            if(column+1<8 && GetPlayer(column+1, row, board)=='P' && GetPlayer(column+1,row-1,board)==' '){
                enpassant=CopyBoard(board);
                PutPlayer(column+1,row-1,enpassant,GetPlayer(column,row,enpassant));
                PutPlayer(column,row,enpassant,' '); 
                PutPlayer(column+1,row,enpassant,' '); 
                //checks if it puts player 2's king in check
                if(enpassant!=NULL && CheckCheck(enpassant, enpassant->playerflag) == 0){
                    SetVariables(enpassant,row-1,row,column+1,column);
                    AppendListNode(tree,enpassant); 
                } else if(enpassant!=NULL){
                    DeleteBoard(enpassant);
                }
                
            }
            //checks the pawn to the left
            else if(column-1>=0 && GetPlayer(column-1, row, board)=='P' && GetPlayer(column-1,row-1,board)==' '){
                enpassant=CopyBoard(board);
                PutPlayer(column-1,row-1,enpassant,GetPlayer(column,row,enpassant));
                PutPlayer(column,row,enpassant,' ');                 
                PutPlayer(column-1,row,enpassant,' '); 
                //checks if it puts player 2's king in check
                if(enpassant!=NULL && CheckCheck(enpassant, enpassant->playerflag) == 0){
                    SetVariables(enpassant,row-1,row,column-1,column);
                    AppendListNode(tree,enpassant); 
                } else if(enpassant!=NULL){
                    DeleteBoard(enpassant);
                }
            }
        }
    }   
}//End of Enpassant function



//Function to check for castling
void Castling(TNODE *tree,GBOARD *board, int column, int row){
    int empty=0,castle=0;
    int position;
    //Player 1
    if(board->playerflag==1){
        //Checks if the white king has moved
        if(board->castling[2]==0){
            //checks if the left white rook has moved
            if(board->castling[0]==0){
                position=column+row*8;
                //checks if the spaces to the left of the king are empty
                for(int i=1;i<=3;i++){
                    if(board->piece[position-i]!=' '){
                        empty=0;
                        break;
                    }
                    else{
                        empty=1;
                    }
                }
                if(empty==1){
                    GBOARD *king;
                    //checks if any of the spaces the kings moves through are not in check
                    for(int i=1;i<3;i++){
                        king=CopyBoard(board);
                        PutPlayer(column-i,row,king,GetPlayer(column,row,king));
                        PutPlayer(column,row,king,' ');                 
                        if(CheckCheck(king, king->playerflag) == 0){
                            DeleteBoard(king);
                            castle=1; 
                        }
                        else{
                            DeleteBoard(king);
                            castle=0;
                            break;
                        }
                    }
                    //performs queens side castle
                    if(castle==1){
                        king=CopyBoard(board);
                        PutPlayer(column-2,row,king,GetPlayer(column,row,king));
                        PutPlayer(column,row,king,' ');
                        PutPlayer(column-1,row,king,'R');
                        PutPlayer(column-4,row,king,' ');
                        king->castling[2]=1;
                        king->castling[0]=1;
                        if(CheckCheck(king,king->playerflag) == 0){
                            SetVariables(king,row,row,column-2,column);
                            AppendListNode(tree,king); 
                        } else {
                            DeleteBoard(king);
                        }   
                    } 
                }     
            }
            castle=0;
            //checks if right white rook moved
            if(board->castling[1]==0){
                position=column+row*8;
                //checks if the spaces to the right of king are empty
                for(int i=1;i<3;i++){
                    if(board->piece[position+i]!=' '){
                        empty=0;
                        break;
                    }
                    else{
                        empty=1;
                    }
                }
                //checks if the spaces to the right of the king are not in check
                if(empty==1){
                    GBOARD *king;
                    for(int i=1;i<3;i++){
                        king=CopyBoard(board);
                        PutPlayer(column+i,row,king,GetPlayer(column,row,king));
                        PutPlayer(column,row,king,' ');                 
                        if(CheckCheck(king,king->playerflag) == 0){
                            DeleteBoard(king);
                            castle=1; 
                        }
                        else{
                            DeleteBoard(king);
                            castle=0;
                            break;
                        }
                    }
                    //performs king side castle
                    if(castle==1){
                        king=CopyBoard(board);
                        PutPlayer(column+2,row,king,GetPlayer(column,row,king));
                        PutPlayer(column,row,king,' ');
                        PutPlayer(column+1,row,king,'R');
                        PutPlayer(column+3,row,king,' ');
                        king->castling[2]=1;
                        king->castling[1]=1;
                        if(CheckCheck(king,king->playerflag) == 0){
                            SetVariables(king,row,row,column+2,column);
                            AppendListNode(tree,king); 
                        } else {
                            DeleteBoard(king);
                        }   
                    } 
                }     
            }
        }
    }
    //player 2
    else if(board->playerflag==2){
        //checks if the black king has mvoed
        if(board->castling[5]==0){
            //checks if the left black rook has moved
            if(board->castling[3]==0){
                position=column+row*8;
                //check if the spaces to the left of the king are empty
                for(int i=1;i<=3;i++){
                    if(board->piece[position-i]!=' '){
                        empty=0;
                        break;
                    }
                    else{
                        empty=1;
                    }
                }
                if(empty==1){
                    GBOARD *king;
                    //checks if the spaces the king moves through are in check
                    for(int i=1;i<3;i++){
                        king=CopyBoard(board);
                        PutPlayer(column-i,row,king,GetPlayer(column,row,king));
                        PutPlayer(column,row,king,' ');                 
                        if(CheckCheck(king,king->playerflag) == 0){
                            DeleteBoard(king);
                            castle=1; 
                        }
                        else{
                            DeleteBoard(king);
                            castle=0;
                            break;
                        }
                    }
                    //performs queen side castle
                    if(castle==1){
                        king=CopyBoard(board);
                        PutPlayer(column-2,row,king,GetPlayer(column,row,king));
                        PutPlayer(column,row,king,' ');
                        PutPlayer(column-1,row,king,'r');
                        PutPlayer(column-4,row,king,' ');
                        king->castling[5]=1;
                        king->castling[3]=1;
                        if(CheckCheck(king,king->playerflag) == 0){
                            SetVariables(king,row,row,column-2,column);
                            AppendListNode(tree,king); 
                        } else {
                            DeleteBoard(king);
                        }   
                    } 
                }     
            }
            castle=0;
            //checks if the right black rook has moved
            if(board->castling[4]==0){
                position=column+row*8;
                //checks if the spaces to the right of the king are empty
                for(int i=1;i<3;i++){
                    if(board->piece[position+i]!=' '){
                        empty=0;
                        break;
                    }
                    else{
                        empty=1;
                    }
                }
                if(empty==1){
                    GBOARD *king;
                    //checks if the spaces the king moves through are in check
                    for(int i=1;i<3;i++){
                        king=CopyBoard(board);
                        PutPlayer(column+i,row,king,GetPlayer(column,row,king));
                        PutPlayer(column,row,king,' ');                 
                        if(CheckCheck(king,king->playerflag) == 0){
                            DeleteBoard(king);
                            castle=1; 
                        }
                        else{
                            DeleteBoard(king);
                            castle=0;
                            break;
                        }
                    }
                    //performs the king side castle
                    if(castle==1){
                        king=CopyBoard(board);
                        PutPlayer(column+2,row,king,GetPlayer(column,row,king));
                        PutPlayer(column,row,king,' ');
                        PutPlayer(column+1,row,king,'r');
                        PutPlayer(column+3,row,king,' ');
                        king->castling[5]=1;
                        king->castling[4]=1;
                        if(CheckCheck(king,king->playerflag) == 0){
                            SetVariables(king,row,row,column+2,column);
                            AppendListNode(tree,king); 
                        } else {
                            DeleteBoard(king);
                        }   
                    } 
                }     
            }
        }
    }
}//End of the castling function


//EOF
