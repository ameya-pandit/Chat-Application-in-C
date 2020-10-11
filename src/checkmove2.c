//Checkmove.c file
//this is the file for the function that checks the valid moves of a piece
//Team 04
#include "checkmove.h"

void checkmove(TNODE *allmoves){
    assert(allmoves);
    assert(allmoves->board);

    char piece;

printf("the flag%d\n",allmoves->board->playerflag);
    for(int i=0;i<64;i++){
            int flag;
            flag = 0;
            piece=allmoves->board->piece[i];
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
             kingmoves(allmoves->board, i, allmoves);
         }
         if((piece=='Q')||(piece=='q')){
             queenmoves(allmoves->board, i, allmoves);
         }
         if((piece=='R')||(piece=='r')){
           // rookmoves(allmoves->board, i, allmoves);
         }
         if((piece=='B')||(piece=='b')){
         //   bishopmoves(allmoves->board, i, allmoves);
         }
         if((piece=='N')||(piece=='n')){
         //   knightmoves(allmoves->board, , allmoves);
         }
         if((piece=='p')||(piece=='P')){
            pawnmoves(allmoves->board, i, allmoves);
        }
      }
    }
    return;
}

void pawnmoves(GBOARD *currentBoard, int position, TNODE *allmoves){
    char  temp;
    bool flag1=false, flag2=false, flag3=false, flag4=false;

    //First Player
    if (currentBoard->playerflag==1){
        //Take a piece
        if((currentBoard->piece[position+7]!=' ')||(currentBoard->piece[position+9]!=' ')){ 
            temp=currentBoard->piece[position+7];
            if((temp!=' ')&&((temp!='K')||(temp!='Q')||(temp!='R')||(temp!='B')||(temp!='N')||(temp!='P'))){
                if((position/8)!=((position+7)/8)){
                     flag3=true;
                }
            }
            temp=currentBoard->piece[position+9];
            if((temp!=' ')&&((temp!='K')||(temp!='Q')||(temp!='R')||(temp!='B')||(temp!='N')||(temp!='P'))){
                if(((position/8)+1)!=((position+9)/8)){
                    flag4=true;
                }
            }
        }
        //move two
        if ((position>7) || (position<16)){
            if((currentBoard->piece[position+8]==' ')||(currentBoard->piece[position+16]==' ')){
                if(currentBoard->piece[position+8]==' '){
                    flag1=true;
                }
                if(currentBoard->piece[position+8]==' ' && currentBoard->piece[position+16]==' '){
                    flag2=true;
                }
            } 
        }
        //move one
        else if(currentBoard->piece[position+8]==' '){
            flag1=true;
        }
    
        //EN PASSANT
        if (position>31 && position<41){
            if (currentBoard->piece[position-1]=='p' && ((position/8)==((position-1)/8))){
                if (currentBoard->prow*8+currentBoard->pcolum-97==position-1+16){
                    GBOARD *Enpassant1=CopyBoard(currentBoard);
                    Enpassant1->prow = position/8;
                    Enpassant1->pcolum = position%8+97;
                    Enpassant1->piece[position-1]=' ';
                    Enpassant1->piece[position-1+8]='P';
                    Enpassant1->row = (position-1+8)/8;
                    Enpassant1->colum = (position-1+8)%8+97;
                    AppendListNode(allmoves, Enpassant1);
                }
            }
            else if (currentBoard->piece[position+1]=='p' && ((position/8)==((position+1)/8))){
                if (currentBoard->prow*8+currentBoard->pcolum-97==position+1+16){
                    GBOARD *Enpassant2=CopyBoard(currentBoard);
                    Enpassant2->prow = position/8;
                    Enpassant2->pcolum = position%8+97;
                    Enpassant2->piece[position+1]=' ';
                    Enpassant2->piece[position+1+8]='P';
                    Enpassant2->row = (position+1+8)/8;
                    Enpassant2->colum = (position+1+8)%8+97;
                    AppendListNode(allmoves, Enpassant2);
                }

            }
        }
        

        //Making boards and concatenating them
        if(flag1==true){
            GBOARD *pawn1=CopyBoard(currentBoard);
            pawn1->piece[position]=' ';
            pawn1->piece[position+8]='P';
            pawn1->prow=position/8;
            pawn1->pcolum=position%8+97;
            pawn1->row=(position+8)/8;
            pawn1->colum=(position+8)%8+97;
            AppendListNode(allmoves, pawn1);
        }
        if(flag2==true){
            GBOARD *pawn2=CopyBoard(currentBoard);
            pawn2->piece[position]=' ';
            pawn2->piece[position+16]='P';
            pawn2->prow=position/8;
            pawn2->pcolum=position%8+97;
            pawn2->row=(position+16)/8;
            pawn2->colum=(position+16)%8+97;
            AppendListNode(allmoves, pawn2);
        }
        if(flag3==true){
            GBOARD *pawn3=CopyBoard(currentBoard);
            pawn3->piece[position]=' ';
            pawn3->piece[position+7]='P';
            pawn3->prow=position/8;
            pawn3->pcolum=position%8+97;
            pawn3->row=(position+7)/8;
            pawn3->colum=(position+7)%8+97;
            AppendListNode(allmoves, pawn3);
        }
        if(flag4==true){
            GBOARD *pawn4=CopyBoard(currentBoard);
            pawn4->piece[position]=' ';
            pawn4->piece[position+9]='P';
            pawn4->prow=position/8;
            pawn4->pcolum=position%8+97;
            pawn4->row=(position+9)/8;
            pawn4->colum=(position+9)%8+97;
            AppendListNode(allmoves, pawn4);
        }    
    }

    //Second Player
    else{
        //Take a piece
        if((currentBoard->piece[position-7]!=' ')||(currentBoard->piece[position-9]!=' ')){
            temp=currentBoard->piece[position-7];
            if((temp!=' ')&&((temp!='k')||(temp!='q')||(temp!='r')||(temp!='b')||(temp!='n')||(temp!='p'))){
                if((position/8)!=((position-7)/8)){
                     flag3=true;
                }
            }
            temp=currentBoard->piece[position-9];
            if((temp!=' ')&&((temp!='k')||(temp!='q')||(temp!='r')||(temp!='b')||(temp!='n')||(temp!='p'))){
                if(((position/8)-1)!=((position-9)/8)){
                    flag4=true;
                }
            }
        }
        //move two
        if ((position>47) || (position<56)){
            if((currentBoard->piece[position-8]==' ')||(currentBoard->piece[position-16]==' ')){
                if(currentBoard->piece[position-8]==' '){
                    flag1=true;
                }
                if(currentBoard->piece[position-8]==' ' && currentBoard->piece[position-16]==' '){
                    flag2=true;
                }
            } 
        }
        //move one
        else if(currentBoard->piece[position-8]==' '){
            flag1=true;
        }
        
        //EN PASSANT
        if (position>23 && position<33){
            if (currentBoard->piece[position-1]=='P' && ((position/8)==((position-1)/8))){
                if (currentBoard->prow*8+currentBoard->pcolum-97==position-1-16){
                    GBOARD *Enpassant1=CopyBoard(currentBoard);
                    Enpassant1->piece[position-1]=' ';
                    Enpassant1->piece[position-1-8]='p';
                    AppendListNode(allmoves, Enpassant1);
                }
            }
            else if (currentBoard->piece[position+1]=='P' && ((position/8)==((position+1)/8))){
                if (currentBoard->prow*8+currentBoard->pcolum-97==position+1-16){
                    GBOARD *Enpassant2=CopyBoard(currentBoard);
                    Enpassant2->piece[position+1]=' ';
                    Enpassant2->piece[position+1-8]='p';
                    AppendListNode(allmoves, Enpassant2);
                }
            }
        }


        //Making boards and concatenating them
        if(flag1==true){
            GBOARD *pawn1=CopyBoard(currentBoard);
            pawn1->piece[position]=' ';
            pawn1->piece[position-8]='p';
            pawn1->prow=position/8;
            pawn1->pcolum=position%8+97;
            pawn1->row=(position-8)/8;
            pawn1->colum=(position-8)%8+97;
            AppendListNode(allmoves, pawn1);
        }
        if(flag2==true){
            GBOARD *pawn2=CopyBoard(currentBoard);
            pawn2->piece[position]=' ';
            pawn2->piece[position-16]='p';
            pawn2->prow=position/8;
            pawn2->pcolum=position%8+97;
            pawn2->row=(position-16)/8;
            pawn2->colum=(position-16)%8+97;
            AppendListNode(allmoves, pawn2);
        }
        if(flag3==true){
            GBOARD *pawn3=CopyBoard(currentBoard);
            pawn3->piece[position]=' ';
            pawn3->piece[position-7]='p';
            pawn3->prow=position/8;
            pawn3->pcolum=position%8+97;
            pawn3->row=(position-7)/8;
            pawn3->colum=(position-7)%8+97;
            AppendListNode(allmoves, pawn3);
        }
        if(flag4==true){
            GBOARD *pawn4=CopyBoard(currentBoard);
            pawn4->piece[position]=' ';
            pawn4->piece[position-9]='p';
            pawn4->prow=position/8;
            pawn4->pcolum=position%8+97;
            pawn4->row=(position-9)/8;
            pawn4->colum=(position-9)%8+97;
            AppendListNode(allmoves, pawn4);
        } 
    }
}//End of pawnmoves






void rookmoves(GBOARD *currentBoard,int position, TNODE *allmoves){
    if (currentBoard->playerflag==1){
        int times,number, l, r, up, bo;
        int a;
        times = position/8;
        number = position %8;
        l = number;
        r = 7-l;
        bo = times;
        up = 7-bo;
        char temp;
        for (a = 1; a <=l; a++){
        //counting the hor - left one
            temp=currentBoard->piece[position-a]; 
            if (temp==' '){
                GBOARD *rook1=CopyBoard(currentBoard);
                rook1->piece[position]=' ';
                rook1->piece[position-a]='R';
                AppendListNode(allmoves, rook1);
                rook1->prow = (position)/8;
                rook1->pcolum = (position %8)+97;
                rook1->row = (position-a)/8;
                rook1->colum = (position-a)%8+97;
            }
            else if((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *rook2=CopyBoard(currentBoard);
                rook2->piece[position]=' ';
                rook2->piece[position-a]='R';
                AppendListNode(allmoves, rook2);
                rook2->prow = (position)/8;
                rook2->pcolum = (position %8)+97;
                rook2->row = (position-a)/8;
                rook2->colum = (position-a)%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                break;
            }
        }
        for (a = 1; a <=r; a++){
        //counting the hori - right one
            temp=currentBoard->piece[position+a];
            if (temp==' '){
                GBOARD *rook3=CopyBoard(currentBoard);
                rook3->piece[position]=' ';
                rook3->piece[position+a]='r';
                AppendListNode(allmoves, rook3);
                rook3->prow = (position)/8;
                rook3->pcolum = (position %8)+97;
                rook3->row = (position+a)/8;
                rook3->colum = (position+a)%8+97;
            }      
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *rook4=CopyBoard(currentBoard);
                rook4->piece[position]=' ';
                rook4->piece[position+a]='r';
                AppendListNode(allmoves, rook4);
                rook4->prow = (position)/8;
                rook4->pcolum = (position %8)+97;
                rook4->row = (position+a)/8;
                rook4->colum = (position+a)%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                break;
            }
        }
        for(a =1; a<=bo;a++){
        //counting the ver | bottom one
            temp=currentBoard->piece[position-8*a];       
            if (temp==' '){
                GBOARD *rook5=CopyBoard(currentBoard);
                rook5->piece[position]=' ';
                rook5->piece[position-(8*a)]='r';
                AppendListNode(allmoves, rook5);
                rook5->prow = (position/8);
                rook5->pcolum = (position %8)+97;
                rook5->row = (position-(8*a))/8;
                rook5->colum = (position-(8*a))%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *rook6=CopyBoard(currentBoard);
                rook6->piece[position]=' ';
                rook6->piece[position-(8*a)]='r';
                AppendListNode(allmoves, rook6);
                rook6->prow = (position)/8;
                rook6->pcolum = (position %8)+97;
                rook6->row = (position-(8*a))/8;
                rook6->colum = (position-(8*a))%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                break;
            }
        }
        for (a = 1;a <=up; a++){
        //counting the ver | the upper one
            temp=currentBoard->piece[position+8*a];
            if (temp==' '){
                GBOARD *rook7=CopyBoard(currentBoard);
                rook7->piece[position]=' ';
                rook7->piece[position+(8*a)]='r';
                AppendListNode(allmoves, rook7);
                rook7->prow = (position)/8;
                rook7->pcolum = (position %8)+97;
                rook7->row = (position+(8*a))/8;
                rook7->colum = (position+(8*a))%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *rook8=CopyBoard(currentBoard);
                rook8->piece[position]=' ';
                rook8->piece[position+(8*a)]='r';
                AppendListNode(allmoves, rook8);
                rook8->prow = (position)/8;
                rook8->pcolum = (position %8)+97;
                rook8->row = (position+(8*a))/8;
                rook8->colum = (position+(8*a))%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
            break;
            }
        }
    }
    //above is for player 1
    else{
        int times,number, l, r, up, bo;
        int a;
        times = position/8;
        number = position %8;
        l = number;
        r = 7-l;
        bo = times;
        up = 7-bo;
        char temp;
        for (a = 1; a <=l; a++){
        //counting the hor - left one
            temp=currentBoard->piece[position-a]; 
            if (temp==' '){
                GBOARD *rook1=CopyBoard(currentBoard);
                rook1->piece[position]=' ';
                rook1->piece[position-a]='R';
                AppendListNode(allmoves, rook1);
                rook1->prow = (position/8);
                rook1->pcolum = (position %8)+97;
                rook1->row = (position-a)/8;
                rook1->colum = (position-a)%8+97;
            }
            else if((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *rook2=CopyBoard(currentBoard);
                rook2->piece[position]=' ';
                rook2->piece[position-a]='R';
                AppendListNode(allmoves, rook2);
                rook2->prow = (position/8);
                rook2->pcolum = (position %8)+97;
                rook2->row = (position-a)/8;
                rook2->colum = (position-a)%8+97;
                break;
            }
            else if((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }      
        }
        for (a = 1; a <=r; a++){
        //counting the hori - right one
            temp=currentBoard->piece[position+a];
            if (temp==' '){
                GBOARD *rook3=CopyBoard(currentBoard);
                rook3->piece[position]=' ';
                rook3->piece[position+a]='R';
                AppendListNode(allmoves, rook3);
                rook3->prow = (position/8);
                rook3->pcolum = (position %8)+97;
                rook3->row = (position+a)/8;
                rook3->colum = (position+a)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *rook4=CopyBoard(currentBoard);
                rook4->piece[position]=' ';
                rook4->piece[position+a]='R';
                AppendListNode(allmoves, rook4);
                rook4->prow = (position/8);
                rook4->pcolum = (position %8)+97;
                rook4->row = (position+a)/8;
                rook4->colum = (position+a)%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }
        for(a =1; a<=bo;a++){
        //counting the ver | bottom one
            temp=currentBoard->piece[(position-8*a)]; 
            if (temp==' '){
                GBOARD *rook5=CopyBoard(currentBoard);
                rook5->piece[position]=' ';
                rook5->piece[position-(8*a)]='R';
                AppendListNode(allmoves, rook5);
                rook5->prow = (position/8);
                rook5->pcolum = (position %8)+97;
                rook5->row = (position-(8*a))/8;
                rook5->colum = (position-(8*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *rook6=CopyBoard(currentBoard);
                rook6->piece[position]=' ';
                rook6->piece[position-(8*a)]='R';
                AppendListNode(allmoves, rook6);
                rook6->prow = (position/8);
                rook6->pcolum = (position %8)+97;
                rook6->row = (position-(8*a))/8;
                rook6->colum = (position-(8*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }
        for (a = 1;a <=up; a++){
        //counting the ver | the upper one
            temp=currentBoard->piece[position+8*a]; 
            if (currentBoard->piece[position+(8*a)]==' '){
                GBOARD *rook7=CopyBoard(currentBoard);
                rook7->piece[position]=' ';
                rook7->piece[position+(8*a)]='R';
                AppendListNode(allmoves, rook7);
                rook7->prow = (position/8);
                rook7->pcolum = (position %8)+97;
                rook7->row = (position+(8*a))/8;
                rook7->colum = (position+(8*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *rook8=CopyBoard(currentBoard);
                rook8->piece[position]=' ';
                rook8->piece[position+(8*a)]='R';
                AppendListNode(allmoves, rook8);
                rook8->prow = (position/8);
                rook8->pcolum = (position %8)+97;
                rook8->row = (position+(8*a))/8;
                rook8->colum = (position+(8*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }
    }
}//this is the rook


void kingmoves(GBOARD *currentBoard, int position, TNODE *allmoves){
    //Player 1
    if (currentBoard->playerflag==1){
        position = position +1;
        int right, left, up, bo;
        left = position%8;
        right = 8- left;
        bo = position /8;
        up = 8 - bo;
        char temp;
         
        //this is the left side, -1
        if (left >=2){
            temp=currentBoard->piece[position-2];
            if ((temp==' ')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *left=CopyBoard(currentBoard);
                left->piece[position-1]=' ';
                left->piece[position-2]='K';
                if (check(left)==true){
                    DeleteBoard(left);
                }
                else{
                    left->prow=(position-1)/8;
                    left->pcolum=(position-1)%8+97;
                    left->row=(position-2)/8;
                    left->colum=(position-2)%8+97;
                    AppendListNode(allmoves, left);
                } 
            }
        }
         
        //this is the right side, +1
        if (right >=1){
            temp=currentBoard->piece[position];
            if ((temp==' ')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *right=CopyBoard(currentBoard);
                right->piece[position-1]=' ';
                right->piece[position]='K';
                if (check(right)==true){
                    DeleteBoard(right);
                }
                else{
                    right->prow=(position-1)/8;
                    right->pcolum=(position-1)%8+97;
                    right->row=(position)/8;
                    right->colum=(position)%8+97;
                    AppendListNode(allmoves, right);
                } 
            }
        }
         
        //this is the upper side, +8
        if (up >=2){
            temp=currentBoard->piece[position+7];
            if ((temp==' ')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){ 
                GBOARD *top=CopyBoard(currentBoard);
                top->piece[position-1]=' ';
                top->piece[position+7]='K';
                if (check(top)==true){
                    DeleteBoard(top);
                }
                else{
                    top->prow=(position-1)/8;
                    top->pcolum=(position-1)%8+97;
                    top->row=(position+7)/8;
                    top->colum=(position+7)%8+97;
                    AppendListNode(allmoves, top);
                } 
            }
        }
         
        //this is the bottom side, -8
        if (bo >=1){
            temp=currentBoard->piece[position-9];
            if ((temp==' ')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *bot=CopyBoard(currentBoard);
                bot->piece[position-1]=' ';
                bot->piece[position-9]='K';
                if (check(bot)==true){
                    DeleteBoard(bot);
                }
                else{
                    bot->prow=(position-1)/8;
                    bot->pcolum=(position-1)%8+97;
                    bot->row=(position-9)/8;
                    bot->colum=(position-9)%8+97;
                    AppendListNode(allmoves, bot);
                } 
                
            }
        }
         
        //this is the left upper, +7
        if (up >=2&&left>=2){
            temp=currentBoard->piece[position+6];
            if ((temp==' ')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *topleft=CopyBoard(currentBoard);
                topleft->piece[position-1]=' ';
                topleft->piece[position+6]='K';
                if (check(topleft)==true){
                    DeleteBoard(topleft);
                }
                else{
                    topleft->prow=(position-1)/8;
                    topleft->pcolum=(position-1)%8+97;
                    topleft->row=(position+6)/8;
                    topleft->colum=(position+6)%8+97;
                    AppendListNode(allmoves, topleft);
                } 
            }
        }
         
        //this is the right upper, +9
        if (up >=2&&right >=1){
            temp=currentBoard->piece[position+8];
            if ((temp==' ')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *topright=CopyBoard(currentBoard);
                topright->piece[position-1]=' ';
                topright->piece[position+8]='K';
                if (check(topright)==true){
                    DeleteBoard(topright);
                }
                else{
                    topright->prow=(position-1)/8;
                    topright->pcolum=(position-1)%8+97;
                    topright->row=(position+8)/8;
                    topright->colum=(position+8)%8+97;
                    AppendListNode(allmoves, topright);
                } 
            }
        }
         
        //this is the left bottom, -9
        if (bo >=1&&left >=2){
            temp=currentBoard->piece[position-10];
            if ((temp==' ')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *botleft=CopyBoard(currentBoard);
                botleft->piece[position-1]=' ';
                botleft->piece[position-10]='K';
                if (check(botleft)==true){
                    DeleteBoard(botleft);
                }
                else{
                    botleft->prow=(position-1)/8;
                    botleft->pcolum=(position-1)%8+97;
                    botleft->row=(position-10)/8;
                    botleft->colum=(position-10)%8+97;
                    AppendListNode(allmoves, botleft);
                } 
            }
        }
         
        //this is the right bottom, -7
        if (bo >=1&&right >=1){
            temp=currentBoard->piece[position-8];
            if ((temp==' ')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *botright=CopyBoard(currentBoard);
                botright->piece[position-1]=' ';
                botright->piece[position-8]='K';
                if (check(botright)==true){
                    DeleteBoard(botright);
                }
                else{
                    botright->prow=(position-1)/8;
                    botright->pcolum=(position-1)%8+97;
                    botright->row=(position-8)/8;
                    botright->colum=(position-8)%8+97;
                    AppendListNode(allmoves, botright);
                } 
            }
        } 
    }
    //Player 2
    else{
        position = position +1;
        int right, left, up, bo;
        left = position%8;
        right = 8- left;
        bo = position /8;
        up = 8 - bo;
        char temp;
         
        //this is the left side, -1
        if (left >=2){
            temp=currentBoard->piece[position-2];
            if ((temp==' ')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *left=CopyBoard(currentBoard);
                left->piece[position-1]=' ';
                left->piece[position-2]='k';
                if (check(left)==true){
                    DeleteBoard(left);
                }
                else{
                    left->prow=(position-1)/8;
                    left->pcolum=(position-1)%8+97;
                    left->row=(position-2)/8;
                    left->colum=(position-2)%8+97;
                    AppendListNode(allmoves, left);
                } 
            }
        }
         
        //this is the right side, +1
        if (right >=1){
            temp=currentBoard->piece[position];
            if ((temp==' ')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *right=CopyBoard(currentBoard);
                right->piece[position-1]=' ';
                right->piece[position]='k';
                if (check(right)==true){
                    DeleteBoard(right);
                }
                else{
                    right->prow=(position-1)/8;
                    right->pcolum=(position-1)%8+97;
                    right->row=(position)/8;
                    right->colum=(position)%8+97;
                    AppendListNode(allmoves, right);
                } 
            }
        }
         
        //this is the upper side, +8
        if (up >=2){
            temp=currentBoard->piece[position+7];
            if ((temp==' ')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){ 
                GBOARD *top=CopyBoard(currentBoard);
                top->piece[position-1]=' ';
                top->piece[position+7]='k';
                if (check(top)==true){
                    DeleteBoard(top);
                }
                else{
                    top->prow=(position-1)/8;
                    top->pcolum=(position-1)%8+97;
                    top->row=(position+7)/8;
                    top->colum=(position+7)%8+97;
                    AppendListNode(allmoves, top);
                } 
            }
        }
         
        //this is the bottom side, -8
        if (bo >=1){
            temp=currentBoard->piece[position-9];
            if ((temp==' ')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bot=CopyBoard(currentBoard);
                bot->piece[position-1]=' ';
                bot->piece[position-9]='k';
                if (check(bot)==true){
                    DeleteBoard(bot);
                }
                else{
                    bot->prow=(position-1)/8;
                    bot->pcolum=(position-1)%8+97;
                    bot->row=(position-9)/8;
                    bot->colum=(position-9)%8+97;
                    AppendListNode(allmoves, bot);
                } 
                
            }
        }
         
        //this is the left upper, +7
        if (up >=2&&left>=2){
            temp=currentBoard->piece[position+6];
            if ((temp==' ')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *topleft=CopyBoard(currentBoard);
                topleft->piece[position-1]=' ';
                topleft->piece[position+6]='k';
                if (check(topleft)==true){
                    DeleteBoard(topleft);
                }
                else{
                    topleft->prow=(position-1)/8;
                    topleft->pcolum=(position-1)%8+97;
                    topleft->row=(position+6)/8;
                    topleft->colum=(position+6)%8+97;
                    AppendListNode(allmoves, topleft);
                } 
            }
        }
         
        //this is the right upper, +9
        if (up >=2&&right >=1){
            temp=currentBoard->piece[position+8];
            if ((temp==' ')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *topright=CopyBoard(currentBoard);
                topright->piece[position-1]=' ';
                topright->piece[position+8]='k';
                if (check(topright)==true){
                    DeleteBoard(topright);
                }
                else{
                    topright->prow=(position-1)/8;
                    topright->pcolum=(position-1)%8+97;
                    topright->row=(position+8)/8;
                    topright->colum=(position+8)%8+97;
                    AppendListNode(allmoves, topright);
                } 
            }
        }
         
        //this is the left bottom, -9
        if (bo >=1&&left >=2){
            temp=currentBoard->piece[position-10];
            if ((temp==' ')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *botleft=CopyBoard(currentBoard);
                botleft->piece[position-1]=' ';
                botleft->piece[position-10]='k';
                if (check(botleft)==true){
                    DeleteBoard(botleft);
                }
                else{
                    botleft->prow=(position-1)/8;
                    botleft->pcolum=(position-1)%8+97;
                    botleft->row=(position-10)/8;
                    botleft->colum=(position-10)%8+97;
                    AppendListNode(allmoves, botleft);
                } 
            }
        }
         
        //this is the right bottom, -7
        if (bo >=1&&right >=1){
            temp=currentBoard->piece[position-8];
            if ((temp==' ')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *botright=CopyBoard(currentBoard);
                botright->piece[position-1]=' ';
                botright->piece[position-8]='k';
                if (check(botright)==true){
                    DeleteBoard(botright);
                }
                else{
                    botright->prow=(position-1)/8;
                    botright->pcolum=(position-1)%8+97;
                    botright->row=(position-8)/8;
                    botright->colum=(position-8)%8+97;
                    AppendListNode(allmoves, botright);
                } 
            }
        }
   } 
}//END OF KINGMOVE

void bishopmoves(GBOARD *currentBoard, int position,TNODE *allmoves){
    if (currentBoard->playerflag==1){
        int msev=0, psev=0, mnin=0, pnin=0;
        int temp_p7=0, temp_m7=0, temp_p9=0,temp_m9=0;
        int a=0;
        char temp;
        temp_p7 = temp_m7 = temp_p9 = temp_m9 = position;
        for (;;){
            //determine how many times should we do the +7
            if ((temp_p7 >= 56) && (temp_p7 <= 63)){
                break;
                //if the position ==56-63, break
            } 
            temp_p7 = temp_p7+7;
            psev = psev+1;
            if ((temp_p7 >= 56) && (temp_p7 <= 63)){
                break;
                //we get the plus seve times
            } 
            if (temp_p7==0||temp_p7==8||temp_p7==16||temp_p7==24||temp_p7==32||temp_p7==40||temp_p7||48||temp_p7==56){
              break;
            }
        }
        for (;;){
            //determine how many times should we do the -7
            if ((temp_m7>=0)&&(temp_m7<=7)){
              break;
            }
            temp_m7 = temp_m7-7;
            msev = msev+1;
            if (temp_m7==7||temp_m7==15||temp_m7==23||temp_m7==31||temp_m7==39||temp_m7==47||temp_m7==55||temp_m7==63){
                break;
                //we get the - seve times
            }
            if ((temp_m7>=0)&&(temp_m7<=7)){
              break;
            }
        } 
        for (;;){
            //determine how many times should we do the +9
            if ((temp_p9 >= 56) && (temp_p9 <=63)){
                break;
                //we get the plus nine times
            }
            temp_p9 = temp_p9+9;
            pnin = pnin+1;
            if ((temp_p9 >= 56) && (temp_p9 <=63)){
                break;
                //we get the plus nine times
            } 
            if(temp_p9==7||temp_p9==15||temp_p9==23||temp_p9==31||temp_p9==39||temp_p9==47||temp_p9==55||temp_p9==63){
              break;
            }
        }
        for (;;){
            //determine how many times should we do the -9
             if ((temp_m9>=0)&&(temp_m9<=7)){
              break;
            }
            temp_m9 = temp_m9-9;
            mnin = mnin+1;
            if (temp_m9==0||temp_m9==8||temp_m9==16||temp_m9==24||temp_m9==32||temp_m9==40||temp_m9==48||temp_m9==56){
                break;
                //we get the - nine times
            }
            if ((temp_m9>=0)&&(temp_m9<=7)){
              break;
            }
        }

        for (a= 1; a <=psev; a++){
            //check for the +7 one
            temp=currentBoard->piece[position+(7*a)]; 
            if (temp==' '){
                GBOARD *bis1=CopyBoard(currentBoard);
                bis1->piece[position]=' ';
                bis1->piece[position+(7*a)]='B';
                AppendListNode(allmoves, bis1);
                bis1->prow = position /8;
                bis1->pcolum = position %8+97;
                bis1->row = (position+(7*a))/8;
                bis1->colum = (position+(7*a))%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *bis2=CopyBoard(currentBoard);
                bis2->piece[position]=' ';
                bis2->piece[position+(7*a)]='B';
                AppendListNode(allmoves, bis2);
                bis2->prow = position /8;
                bis2->pcolum = position %8+97;
                bis2->row = (position+(7*a))/8;
                bis2->colum = (position+(7*a))%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                break;
            }
        
        }   
        for (a= 1; a <=msev; a++){
            //check for the -7 one 
            temp=currentBoard->piece[position-(7*a)];
            if (temp==' '){
                GBOARD *bis3=CopyBoard(currentBoard);
                bis3->piece[position]=' ';
                bis3->piece[position-(7*a)]='B';
                AppendListNode(allmoves, bis3);
                bis3->prow = position /8;
                bis3->pcolum = position %8+97;
                bis3->row = (position-(7*a))/8;
                bis3->colum = (position-(7*a))%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *bis4=CopyBoard(currentBoard);
                position = position -1;
                bis4->piece[position]=' ';
                bis4->piece[position-(7*a)]='B';
                AppendListNode(allmoves, bis4);
                bis4->prow = (position /8);
                bis4->pcolum = (position %8)+97;
                bis4->row = (position-(7*a))/8;
                bis4->colum = (position-(7*a))%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                break;
            }
        }   
        for (a= 1; a <=pnin; a++){
        //check for the +9 one
            temp=currentBoard->piece[position+(9*a)]; 
            if (temp==' '){
                GBOARD *bis5=CopyBoard(currentBoard);
                bis5->piece[position]=' ';
                bis5->piece[position+(9*a)]='B';
                AppendListNode(allmoves, bis5);
                bis5->prow = (position /8);
                bis5->pcolum = (position %8)+97;
                bis5->row = (position+(9*a))/8;
                bis5->colum = (position+(9*a))%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *bis6=CopyBoard(currentBoard);
                bis6->piece[position]=' ';
                bis6->piece[position+(9*a)]='B';
                AppendListNode(allmoves, bis6);
                bis6->prow = (position /8);
                bis6->pcolum = (position %8)+97;
                bis6->row = (position+(9*a))/8;
                bis6->colum = (position+(9*a))%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                break;
            }
        }
    
        for (a= 1; a <=mnin; a++){
        //check for the -9 one
            temp=currentBoard->piece[position-(9*a)]; 
            if (temp==' '){
                GBOARD *bis7=CopyBoard(currentBoard);
                bis7->piece[position]=' ';
                bis7->piece[position-(9*a)]='B';
                AppendListNode(allmoves, bis7);
                bis7->prow = (position /8);
                bis7->pcolum = (position %8)+97;
                bis7->row = (position-(9*a))/8;
                bis7->colum = (position-(9*a))%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *bis8=CopyBoard(currentBoard);
                bis8->piece[position]=' ';
                bis8->piece[position-(9*a)]='B';
                AppendListNode(allmoves, bis8);
                bis8->prow = (position /8);
                bis8->pcolum = (position %8)+97;
                bis8->row = (position-(9*a))/8;
                bis8->colum = (position-(9*a))%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                break;
            }
        }
    }
    else{
        int msev=0, psev=0, mnin=0, pnin=0;
        int temp_p7, temp_m7, temp_p9,temp_m9;
        int a=0;
        temp_p7 = temp_m7 = temp_p9 = temp_m9 = position;
        char temp;
        for (;;){
            //determine how many times should we do the +7
            if ((temp_p7 >= 56) && (temp_p7 <= 63)){
                break;
                //if the position ==56-63, break
            } 
            temp_p7 = temp_p7+7;
            psev = psev+1;
            if ((temp_p7 >= 56) && (temp_p7 <= 63)){
                break;
                //we get the plus seve times
            } 
            if (temp_p7==0||temp_p7==8||temp_p7==16||temp_p7==24||temp_p7==32||temp_p7==40||temp_p7||48||temp_p7==56){
              break;
            }
        }
        for (;;){
            //determine how many times should we do the -7
            if ((temp_m7>=0)&&(temp_m7<=7)){
              break;
            }
            temp_m7 = temp_m7-7;
            msev = msev+1;
            if (temp_m7==7||temp_m7==15||temp_m7==23||temp_m7==31||temp_m7==39||temp_m7==47||temp_m7==55||temp_m7==63){
                break;
                //we get the - seve times
            }
            if ((temp_m7>=0)&&(temp_m7<=7)){
              break;
            }
        } 
        for (;;){
            //determine how many times should we do the +9
            if ((temp_p9 >= 56) && (temp_p9 <=63)){
                break;
                //we get the plus nine times
            }
            temp_p9 = temp_p9+9;
            pnin = pnin+1;
            if ((temp_p9 >= 56) && (temp_p9 <=63)){
                break;
                //we get the plus nine times
            } 
            if(temp_p9==7||temp_p9==15||temp_p9==23||temp_p9==31||temp_p9==39||temp_p9==47||temp_p9==55||temp_p9==63){
              break;
            }
        }
        for (;;){
            //determine how many times should we do the -9
             if ((temp_m9>=0)&&(temp_m9<=7)){
              break;
            }
            temp_m9 = temp_m9-9;
            mnin = mnin+1;
            if (temp_m9==0||temp_m9==8||temp_m9==16||temp_m9==24||temp_m9==32||temp_m9==40||temp_m9==48||temp_m9==56){
                break;
                //we get the - nine times
            }
            if ((temp_m9>=0)&&(temp_m9<=7)){
              break;
            }
        }
        for (a= 1; a <=psev; a++){
            //check for the +7 one
            temp=currentBoard->piece[position+(7*a)]; 
            if (temp==' '){
                GBOARD *bis1=CopyBoard(currentBoard);
                bis1->piece[position]=' ';
                bis1->piece[position+(7*a)]='b';
                AppendListNode(allmoves, bis1);
                bis1->prow = position /8;
                bis1->pcolum = position %8+97;
                bis1->row = (position+(7*a))/8;
                bis1->colum = (position+(7*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis2=CopyBoard(currentBoard);
                bis2->piece[position]=' ';
                bis2->piece[position+(7*a)]='b';
                AppendListNode(allmoves, bis2);
                bis2->prow = position /8;
                bis2->pcolum = position %8+97;
                bis2->row = (position+(7*a))/8;
                bis2->colum = (position+(7*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        
        }   
        for (a= 1; a <=msev; a++){
            //check for the -7 one 
            temp=currentBoard->piece[position-(7*a)];
            if (temp==' '){
                GBOARD *bis3=CopyBoard(currentBoard);
                bis3->piece[position]=' ';
                bis3->piece[position-(7*a)]='b';
                AppendListNode(allmoves, bis3);
                bis3->prow = position /8;
                bis3->pcolum = position %8+97;
                bis3->row = (position-(7*a))/8;
                bis3->colum = (position-(7*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis4=CopyBoard(currentBoard);
                position = position -1;
                bis4->piece[position]=' ';
                bis4->piece[position-(7*a)]='b';
                AppendListNode(allmoves, bis4);
                bis4->prow = (position /8);
                bis4->pcolum = (position %8)+97;
                bis4->row = (position-(7*a))/8;
                bis4->colum = (position-(7*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }   
        for (a= 1; a <=pnin; a++){
        //check for the +9 one
            temp=currentBoard->piece[position+(9*a)]; 
            if (temp==' '){
                GBOARD *bis5=CopyBoard(currentBoard);
                bis5->piece[position]=' ';
                bis5->piece[position+(9*a)]='b';
                AppendListNode(allmoves, bis5);
                bis5->prow = (position /8);
                bis5->pcolum = (position %8)+97;
                bis5->row = (position+(9*a))/8;
                bis5->colum = (position+(9*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis6=CopyBoard(currentBoard);
                bis6->piece[position]=' ';
                bis6->piece[position+(9*a)]='b';
                AppendListNode(allmoves, bis6);
                bis6->prow = (position /8);
                bis6->pcolum = (position %8)+97;
                bis6->row = (position+(9*a))/8;
                bis6->colum = (position+(9*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }
    
        for (a= 1; a <=mnin; a++){
        //check for the -9 one
            temp=currentBoard->piece[position-(9*a)]; 
            if (temp==' '){
                GBOARD *bis7=CopyBoard(currentBoard);
                bis7->piece[position]=' ';
                bis7->piece[position-(9*a)]='b';
                AppendListNode(allmoves, bis7);
                bis7->prow = (position /8);
                bis7->pcolum = (position %8)+97;
                bis7->row = (position-(9*a))/8;
                bis7->colum = (position-(9*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis8=CopyBoard(currentBoard);
                bis8->piece[position]=' ';
                bis8->piece[position-(9*a)]='b';
                AppendListNode(allmoves, bis8);
                bis8->prow = (position /8);
                bis8->pcolum = (position %8)+97;
                bis8->row = (position-(9*a))/8;
                bis8->colum = (position-(9*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }
    }
}//this is the bishop




void knightmoves(GBOARD *currentBoard, int position, TNODE *allmoves){
    if (currentBoard->playerflag==1){
        int left, right, up, bo;
        left = position%8;
        right =  7- left;
        bo = position/8;
        up = 7-bo;
        char temp;
        //the first one is the one upper- one. +6 one 
        if ((left >=2)&&(up >=1)){
            temp=currentBoard->piece[position+6];
            if (temp==' '){
                GBOARD *knight1=CopyBoard(currentBoard);
                knight1->piece[position]=' ';
                knight1->piece[position+6]='N';
                AppendListNode(allmoves, knight1);
                knight1->prow = (position /8);
                knight1->pcolum = (position %8)+97;
                knight1->row = (position+6)/8;
                knight1->colum = (position+6)%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *knight2=CopyBoard(currentBoard);
                knight2->piece[position]=' ';
                knight2->piece[position+6]='N';
                AppendListNode(allmoves, knight2);
                knight2->prow = (position /8);
                knight2->pcolum = (position %8)+97;
                knight2->row = (position+6)/8;
                knight2->colum = (position+6)%8+97;
                
        }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                
            }
        }   
    
        //this is the one bottom- one, -10
        if ((left >=2)&&(bo>=1)){
            temp=currentBoard->piece[position-10];
            if (temp==' '){
                GBOARD *knight3=CopyBoard(currentBoard);
                knight3->piece[position]=' ';
                knight3->piece[position-10]='N';
                AppendListNode(allmoves, knight3);
                knight3->prow = (position /8);
                knight3->pcolum = (position %8)+97;
                knight3->row = (position-10)/8;
                knight3->colum = (position-10)%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *knight4=CopyBoard(currentBoard);
                knight4->piece[position]=' ';
                knight4->piece[position-10]='N';
                AppendListNode(allmoves, knight4);
                knight4->prow = (position /8);
                knight4->pcolum = (position %8)+97;
                knight4->row = (position-10)/8;
                knight4->colum = (position-10)%8+97;
                
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
               
            }
        }
    
        //this is the one -upper one, +10
        if ((right >=2)&&(up >=1)){
            temp=currentBoard->piece[position+10];
            if (temp==' '){
                GBOARD *knight5=CopyBoard(currentBoard);
                knight5->piece[position]=' ';
                knight5->piece[position+10]='N';
                AppendListNode(allmoves, knight5);
                knight5->prow = (position /8);
                knight5->pcolum = (position %8)+97;
                knight5->row = (position+10)/8;
                knight5->colum = (position+10)%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *knight6=CopyBoard(currentBoard);
                knight6->piece[position]=' ';
                knight6->piece[position+10]='N';
                AppendListNode(allmoves, knight6);
                knight6->prow = (position /8);
                knight6->pcolum = (position %8)+97;
                knight6->row = (position+10)/8;
                knight6->colum = (position+10)%8+97;
               
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
              
            }
        }
    
        //this is the one -bottom one, -6
        if ((right >=2)&&(bo >=1)){
            temp=currentBoard->piece[position-6];
            if (temp==' '){
                GBOARD *knight7=CopyBoard(currentBoard);
                knight7->piece[position]=' ';
                knight7->piece[position-6]='N';
                AppendListNode(allmoves, knight7);
                knight7->prow = (position /8);
                knight7->pcolum = (position %8)+97;
                knight7->row = (position-6)/8;
                knight7->colum = (position-6)%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *knight8=CopyBoard(currentBoard);
                knight8->piece[position]=' ';
                knight8->piece[position-6]='N';
                AppendListNode(allmoves, knight8);
                knight8->prow = (position /8);
                knight8->pcolum = (position %8)+97;
                knight8->row = (position-6)/8;
                knight8->colum = (position-6)%8+97;
                
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
               
            }
        }
    
        //this is the one upper -|, +15
        if ((left >=1)&&(up >=2)){
            temp=currentBoard->piece[position+15];
            if (temp==' '){
                GBOARD *knight9=CopyBoard(currentBoard);
                knight9->piece[position]=' ';
                knight9->piece[position+15]='N';
                AppendListNode(allmoves, knight9);
                knight9->prow = (position /8);
                knight9->pcolum = (position %8)+97;
                knight9->row = (position+15)/8;
                knight9->colum = (position+15)%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *knight10=CopyBoard(currentBoard);
                knight10->piece[position]=' ';
                knight10->piece[position+15]='N';
                AppendListNode(allmoves, knight10);
                knight10->prow = (position /8);
                knight10->pcolum = (position %8)+97;
                knight10->row = (position+15)/8;
                knight10->colum = (position+15)%8+97;
              
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
              
            }
        }
    
        //this is the one upper |-, +17
        if ((right >=1)&&(up >=2)){
            temp=currentBoard->piece[position+17];
            if (temp==' '){
                GBOARD *knight11=CopyBoard(currentBoard);
                knight11->piece[position]=' ';
                knight11->piece[position+17]='N';
                AppendListNode(allmoves, knight11);
                knight11->prow = (position /8);
                knight11->pcolum = (position %8)+97;
                knight11->row = (position+17)/8;
                knight11->colum = (position+17)%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *knight12=CopyBoard(currentBoard);
                knight12->piece[position]=' ';
                knight12->piece[position+17]='N';
                AppendListNode(allmoves, knight12);
                knight12->prow = (position /8);
                knight12->pcolum = (position %8)+97;
                knight12->row = (position+17)/8;
                knight12->colum = (position+17)%8+97;
              
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
               
            }
        }
    
        //this is the one bottom -|, -17
        if ((left >=1)&&(bo >=2)){
            temp=currentBoard->piece[position-17];
            if (temp==' '){
                GBOARD *knight13=CopyBoard(currentBoard);
                knight13->piece[position]=' ';
                knight13->piece[position-17]='N';
                AppendListNode(allmoves, knight13);
                knight13->prow = (position /8);
                knight13->pcolum = (position %8)+97;
                knight13->row = (position-17)/8;
                knight13->colum = (position-17)%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *knight14=CopyBoard(currentBoard);
                knight14->piece[position]=' ';
                knight14->piece[position-17]='N';
                AppendListNode(allmoves, knight14);
                knight14->prow = (position /8);
                knight14->pcolum = (position %8)+97;
                knight14->row = (position-17)/8;
                knight14->colum = (position-17)%8+97;
               
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
             
            }
        }
    
        //this is the one bottom |-, -15
        if ((right >=1)&&(bo >=2)){
            temp=currentBoard->piece[position-15];
            if (temp==' '){
                GBOARD *knight15=CopyBoard(currentBoard);
                knight15->piece[position]=' ';
                knight15->piece[position-15]='N';
                AppendListNode(allmoves, knight15);
                knight15->prow = (position /8);
                knight15->pcolum = (position %8)+97;
                knight15->row = (position-15)/8;
                knight15->colum = (position-15)%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *knight16=CopyBoard(currentBoard);
                knight16->piece[position]=' ';
                knight16->piece[position-15]='N';
                AppendListNode(allmoves, knight16);
                knight16->prow = (position /8);
                knight16->pcolum = (position %8)+97;
                knight16->row = (position-15)/8;
                knight16->colum = (position-15)%8+97;
               
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
               
            }
        }
    }
    else{
        int left, right, up, bo;
        left = position%8;
        right= 7- left;
        bo = position/8;
        up = 7-bo;
        char temp;
        //the first one is the one upper- one. +6 one 
        if ((left >=1)&&(up >=2)){
            temp=currentBoard->piece[position+6];
            if (temp==' '){
                GBOARD *knight1=CopyBoard(currentBoard);
                knight1->piece[position]=' ';
                knight1->piece[position+6]='N';
                AppendListNode(allmoves, knight1);
                knight1->prow = (position /8);
                knight1->pcolum = (position %8)+97;
                knight1->row = (position+6)/8;
                knight1->colum = (position+6)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *knight2=CopyBoard(currentBoard);
                knight2->piece[position]=' ';
                knight2->piece[position+6]='N';
                AppendListNode(allmoves, knight2);
                knight2->prow = (position /8);
                knight2->pcolum = (position %8)+97;
                knight2->row = (position+6)/8;
                knight2->colum = (position+6)%8+97;
               
        }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
              
            }
        }   
    
        //this is the one bottom- one, -10
        if ((left >=2)&&(bo>=1)){
            temp=currentBoard->piece[position-10];
            if (temp==' '){
                GBOARD *knight3=CopyBoard(currentBoard);
                knight3->piece[position]=' ';
                knight3->piece[position-10]='N';
                AppendListNode(allmoves, knight3);
                knight3->prow = (position /8);
                knight3->pcolum = (position %8)+97;
                knight3->row = (position-10)/8;
                knight3->colum = (position-10)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *knight4=CopyBoard(currentBoard);
                knight4->piece[position]=' ';
                knight4->piece[position-10]='N';
                AppendListNode(allmoves, knight4);
                knight4->prow = (position /8);
                knight4->pcolum = (position %8)+97;
                knight4->row = (position-10)/8;
                knight4->colum = (position-10)%8+97;
                
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
              
            }
        }
    
        //this is the one -upper one, +10
        if ((right >=2)&&(up >=1)){
            temp=currentBoard->piece[position+10];
            if (temp==' '){
                GBOARD *knight5=CopyBoard(currentBoard);
                knight5->piece[position]=' ';
                knight5->piece[position+10]='N';
                AppendListNode(allmoves, knight5);
                knight5->prow = (position /8);
                knight5->pcolum = (position %8)+97;
                knight5->row = (position+10)/8;
                knight5->colum = (position+10)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *knight6=CopyBoard(currentBoard);
                knight6->piece[position]=' ';
                knight6->piece[position+10]='N';
                AppendListNode(allmoves, knight6);
                knight6->prow = (position /8);
                knight6->pcolum = (position %8)+97;
                knight6->row = (position+10)/8;
                knight6->colum = (position+10)%8+97;
              
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
             
            }
        }
    
        //this is the one -bottom one, -6
        if ((right >=2)&&(bo >=1)){
            temp=currentBoard->piece[position-6];
            if (temp==' '){
                GBOARD *knight7=CopyBoard(currentBoard);
                knight7->piece[position]=' ';
                knight7->piece[position-6]='N';
                AppendListNode(allmoves, knight7);
                knight7->prow = (position /8);
                knight7->pcolum = (position %8)+97;
                knight7->row = (position-6)/8;
                knight7->colum = (position-6)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *knight8=CopyBoard(currentBoard);
                knight8->piece[position]=' ';
                knight8->piece[position-6]='N';
                AppendListNode(allmoves, knight8);
                knight8->prow = (position /8);
                knight8->pcolum = (position %8)+97;
                knight8->row = (position-6)/8;
                knight8->colum = (position-6)%8+97;
              
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
              
            }
        }
    
        //this is the one upper -|, +15
        if ((left >=1)&&(up >=2)){
            temp=currentBoard->piece[position+15];
            if (temp==' '){
                GBOARD *knight9=CopyBoard(currentBoard);
                knight9->piece[position]=' ';
                knight9->piece[position+15]='N';
                AppendListNode(allmoves, knight9);
                knight9->prow = (position /8);
                knight9->pcolum = (position %8)+97;
                knight9->row = (position+15)/8;
                knight9->colum = (position+15)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *knight10=CopyBoard(currentBoard);
                knight10->piece[position]=' ';
                knight10->piece[position+15]='N';
                AppendListNode(allmoves, knight10);
                knight10->prow = (position /8);
                knight10->pcolum = (position %8)+97;
                knight10->row = (position+15)/8;
                knight10->colum = (position+15)%8+97;
               
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
             
            }
        }
    
        //this is the one upper |-, +17
        if ((right >=1)&&(up >=2)){
            temp=currentBoard->piece[position+17];
            if (temp==' '){
                GBOARD *knight11=CopyBoard(currentBoard);
                knight11->piece[position]=' ';
                knight11->piece[position+17]='N';
                AppendListNode(allmoves, knight11);
                knight11->prow = (position /8);
                knight11->pcolum = (position %8)+97;
                knight11->row = (position+17)/8;
                knight11->colum = (position+17)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *knight12=CopyBoard(currentBoard);
                knight12->piece[position]=' ';
                knight12->piece[position+17]='N';
                AppendListNode(allmoves, knight12);
                knight12->prow = (position /8);
                knight12->pcolum = (position %8)+97;
                knight12->row = (position+17)/8;
                knight12->colum = (position+17)%8+97;
                
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
              
            }
        }
    
        //this is the one bottom -|, -17
        if ((left >=1)&&(bo >=2)){
            temp=currentBoard->piece[position-17];
            if (temp==' '){
                GBOARD *knight13=CopyBoard(currentBoard);
                knight13->piece[position]=' ';
                knight13->piece[position-17]='N';
                AppendListNode(allmoves, knight13);
                knight13->prow = (position /8);
                knight13->pcolum = (position %8)+97;
                knight13->row = (position-17)/8;
                knight13->colum = (position-17)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *knight14=CopyBoard(currentBoard);
                knight14->piece[position]=' ';
                knight14->piece[position-17]='N';
                AppendListNode(allmoves, knight14);
                knight14->prow = (position /8);
                knight14->pcolum = (position %8)+97;
                knight14->row = (position-17)/8;
                knight14->colum = (position-17)%8+97;
            
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
               
            }
        }
    
        //this is the one bottom |-, -15
        if ((right >=1)&&(bo >=2)){
            temp=currentBoard->piece[position-15];
            if (temp==' '){
                GBOARD *knight15=CopyBoard(currentBoard);
                knight15->piece[position]=' ';
                knight15->piece[position-15]='N';
                AppendListNode(allmoves, knight15);
                knight15->prow = (position /8);
                knight15->pcolum = (position %8)+97;
                knight15->row = (position-15)/8;
                knight15->colum = (position-15)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *knight16=CopyBoard(currentBoard);
                knight16->piece[position]=' ';
                knight16->piece[position-15]='N';
                AppendListNode(allmoves, knight16);
                knight16->prow = (position /8);
                knight16->pcolum = (position %8)+97;
                knight16->row = (position-15)/8;
                knight16->colum = (position-15)%8+97;
                
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
               
            }
        }
    }
}//this is the knight 

void queenmoves(GBOARD *currentBoard, int position, TNODE *allmoves){
    if (currentBoard->playerflag==1){
        int times,number, l, r, up, bo;
        int a;
        int msev=0, psev=0, mnin=0, pnin=0;
        int temp_p7, temp_m7, temp_p9,temp_m9;
        temp_p7 = temp_m7 = temp_p9 = temp_m9 = position;
        times = position/8;
        number = position %8;
        l = number;
        r = 7-l;
        bo = times;
        up = 7-bo;
        char temp;
        for (a = 1; a <=l; a++){
        //counting the hor - left one
            temp=currentBoard->piece[position-a]; 
            if (temp==' '){
                GBOARD *rook1=CopyBoard(currentBoard);
                rook1->piece[position]=' ';
                rook1->piece[position-a]='R';
                AppendListNode(allmoves, rook1);
                rook1->prow = (position)/8;
                rook1->pcolum = (position %8)+97;
                rook1->row = (position-a)/8;
                rook1->colum = (position-a)%8+97;
            }
            else if((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *rook2=CopyBoard(currentBoard);
                rook2->piece[position]=' ';
                rook2->piece[position-a]='R';
                AppendListNode(allmoves, rook2);
                rook2->prow = (position)/8;
                rook2->pcolum = (position %8)+97;
                rook2->row = (position-a)/8;
                rook2->colum = (position-a)%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                break;
            }
        }
        for (a = 1; a <=r; a++){
        //counting the hori - right one
            temp=currentBoard->piece[position+a];
            if (temp==' '){
                GBOARD *rook3=CopyBoard(currentBoard);
                rook3->piece[position]=' ';
                rook3->piece[position+a]='r';
                AppendListNode(allmoves, rook3);
                rook3->prow = (position)/8;
                rook3->pcolum = (position %8)+97;
                rook3->row = (position+a)/8;
                rook3->colum = (position+a)%8+97;
            }      
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *rook4=CopyBoard(currentBoard);
                rook4->piece[position]=' ';
                rook4->piece[position+a]='r';
                AppendListNode(allmoves, rook4);
                rook4->prow = (position)/8;
                rook4->pcolum = (position %8)+97;
                rook4->row = (position+a)/8;
                rook4->colum = (position+a)%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                break;
            }
        }
        for(a =1; a<=bo;a++){
        //counting the ver | bottom one
            temp=currentBoard->piece[position-8*a];       
            if (temp==' '){
                GBOARD *rook5=CopyBoard(currentBoard);
                rook5->piece[position]=' ';
                rook5->piece[position-(8*a)]='r';
                AppendListNode(allmoves, rook5);
                rook5->prow = (position/8);
                rook5->pcolum = (position %8)+97;
                rook5->row = (position-(8*a))/8;
                rook5->colum = (position-(8*a))%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *rook6=CopyBoard(currentBoard);
                rook6->piece[position]=' ';
                rook6->piece[position-(8*a)]='r';
                AppendListNode(allmoves, rook6);
                rook6->prow = (position)/8;
                rook6->pcolum = (position %8)+97;
                rook6->row = (position-(8*a))/8;
                rook6->colum = (position-(8*a))%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                break;
            }
        }
        for (a = 1;a <=up; a++){
        //counting the ver | the upper one
            temp=currentBoard->piece[position+8*a];
            if (temp==' '){
                GBOARD *rook7=CopyBoard(currentBoard);
                rook7->piece[position]=' ';
                rook7->piece[position+(8*a)]='r';
                AppendListNode(allmoves, rook7);
                rook7->prow = (position)/8;
                rook7->pcolum = (position %8)+97;
                rook7->row = (position+(8*a))/8;
                rook7->colum = (position+(8*a))%8+97;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                GBOARD *rook8=CopyBoard(currentBoard);
                rook8->piece[position]=' ';
                rook8->piece[position+(8*a)]='r';
                AppendListNode(allmoves, rook8);
                rook8->prow = (position)/8;
                rook8->pcolum = (position %8)+97;
                rook8->row = (position+(8*a))/8;
                rook8->colum = (position+(8*a))%8+97;
                break;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
            break;
            }
        }//this is for the rook one
        for (;;){
            //determine how many times should we do the +7
            if ((temp_p7 >= 56) && (temp_p7 <= 63)){
                break;
                //if the position ==56-63, break
            } 
            temp_p7 = temp_p7+7;
            psev = psev+1;
            if ((temp_p7 >= 56) && (temp_p7 <= 63)){
                break;
                //we get the plus seve times
            } 
            if (temp_p7==0||temp_p7==8||temp_p7==16||temp_p7==24||temp_p7==32||temp_p7==40||temp_p7||48||temp_p7==56){
              break;
            }
        }
        for (;;){
            //determine how many times should we do the -7
            if ((temp_m7>=0)&&(temp_m7<=7)){
              break;
            }
            temp_m7 = temp_m7-7;
            msev = msev+1;
            if (temp_m7==7||temp_m7==15||temp_m7==23||temp_m7==31||temp_m7==39||temp_m7==47||temp_m7==55||temp_m7==63){
                break;
                //we get the - seve times
            }
            if ((temp_m7>=0)&&(temp_m7<=7)){
              break;
            }
        } 
        for (;;){
            //determine how many times should we do the +9
            if ((temp_p9 >= 56) && (temp_p9 <=63)){
                break;
                //we get the plus nine times
            }
            temp_p9 = temp_p9+9;
            pnin = pnin+1;
            if ((temp_p9 >= 56) && (temp_p9 <=63)){
                break;
                //we get the plus nine times
            } 
            if(temp_p9==7||temp_p9==15||temp_p9==23||temp_p9==31||temp_p9==39||temp_p9==47||temp_p9==55||temp_p9==63){
              break;
            }
        }
        for (;;){
            //determine how many times should we do the -9
             if ((temp_m9>=0)&&(temp_m9<=7)){
              break;
            }
            temp_m9 = temp_m9-9;
            mnin = mnin+1;
            if (temp_m9==0||temp_m9==8||temp_m9==16||temp_m9==24||temp_m9==32||temp_m9==40||temp_m9==48||temp_m9==56){
                break;
                //we get the - nine times
            }
            if ((temp_m9>=0)&&(temp_m9<=7)){
              break;
            }
        }
        for (a= 1; a <=psev; a++){
            //check for the +7 one
            temp=currentBoard->piece[position+(7*a)]; 
            if (temp==' '){
                GBOARD *bis1=CopyBoard(currentBoard);
                bis1->piece[position]=' ';
                bis1->piece[position+(7*a)]='b';
                AppendListNode(allmoves, bis1);
                bis1->prow = position /8;
                bis1->pcolum = position %8+97;
                bis1->row = (position+(7*a))/8;
                bis1->colum = (position+(7*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis2=CopyBoard(currentBoard);
                bis2->piece[position]=' ';
                bis2->piece[position+(7*a)]='b';
                AppendListNode(allmoves, bis2);
                bis2->prow = position /8;
                bis2->pcolum = position %8+97;
                bis2->row = (position+(7*a))/8;
                bis2->colum = (position+(7*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        
        }   
        for (a= 1; a <=msev; a++){
            //check for the -7 one 
            temp=currentBoard->piece[position-(7*a)];
            if (temp==' '){
                GBOARD *bis3=CopyBoard(currentBoard);
                bis3->piece[position]=' ';
                bis3->piece[position-(7*a)]='b';
                AppendListNode(allmoves, bis3);
                bis3->prow = position /8;
                bis3->pcolum = position %8+97;
                bis3->row = (position-(7*a))/8;
                bis3->colum = (position-(7*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis4=CopyBoard(currentBoard);
                position = position -1;
                bis4->piece[position]=' ';
                bis4->piece[position-(7*a)]='b';
                AppendListNode(allmoves, bis4);
                bis4->prow = (position /8);
                bis4->pcolum = (position %8)+97;
                bis4->row = (position-(7*a))/8;
                bis4->colum = (position-(7*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }   
        for (a= 1; a <=pnin; a++){
        //check for the +9 one
            temp=currentBoard->piece[position+(9*a)]; 
            if (temp==' '){
                GBOARD *bis5=CopyBoard(currentBoard);
                bis5->piece[position]=' ';
                bis5->piece[position+(9*a)]='b';
                AppendListNode(allmoves, bis5);
                bis5->prow = (position /8);
                bis5->pcolum = (position %8)+97;
                bis5->row = (position+(9*a))/8;
                bis5->colum = (position+(9*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis6=CopyBoard(currentBoard);
                bis6->piece[position]=' ';
                bis6->piece[position+(9*a)]='b';
                AppendListNode(allmoves, bis6);
                bis6->prow = (position /8);
                bis6->pcolum = (position %8)+97;
                bis6->row = (position+(9*a))/8;
                bis6->colum = (position+(9*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }
    
        for (a= 1; a <=mnin; a++){
        //check for the -9 one
            temp=currentBoard->piece[position-(9*a)]; 
            if (temp==' '){
                GBOARD *bis7=CopyBoard(currentBoard);
                bis7->piece[position]=' ';
                bis7->piece[position-(9*a)]='b';
                AppendListNode(allmoves, bis7);
                bis7->prow = (position /8);
                bis7->pcolum = (position %8)+97;
                bis7->row = (position-(9*a))/8;
                bis7->colum = (position-(9*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis8=CopyBoard(currentBoard);
                bis8->piece[position]=' ';
                bis8->piece[position-(9*a)]='b';
                AppendListNode(allmoves, bis8);
                bis8->prow = (position /8);
                bis8->pcolum = (position %8)+97;
                bis8->row = (position-(9*a))/8;
                bis8->colum = (position-(9*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }
    }//above is for player 1

    else{
        int times,number, l, r, up, bo;
        int a;
        int msev=0, psev=0, mnin=0, pnin=0;
        int temp_p7, temp_m7, temp_p9,temp_m9;
        temp_p7 = temp_m7 = temp_p9 = temp_m9 = position;
        times = position/8;
        number = position %8;
        l = number;
        r = 7-l;
        bo = times;
        up = 7-bo;
        char temp;
        for (a = 1; a <=l; a++){
        //counting the hor - left one
            temp=currentBoard->piece[position-a]; 
            if (temp==' '){
                GBOARD *rook1=CopyBoard(currentBoard);
                rook1->piece[position]=' ';
                rook1->piece[position-a]='R';
                AppendListNode(allmoves, rook1);
                rook1->prow = (position/8);
                rook1->pcolum = (position %8)+97;
                rook1->row = (position-a)/8;
                rook1->colum = (position-a)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *rook2=CopyBoard(currentBoard);
                rook2->piece[position]=' ';
                rook2->piece[position-a]='R';
                AppendListNode(allmoves, rook2);
                rook2->prow = (position/8);
                rook2->pcolum = (position %8)+97;
                rook2->row = (position-a)/8;
                rook2->colum = (position-a)%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }      
        }
        for (a = 1; a <=r; a++){
        //counting the hori - right one
            temp=currentBoard->piece[position+a];
            if (temp==' '){
                GBOARD *rook3=CopyBoard(currentBoard);
                rook3->piece[position]=' ';
                rook3->piece[position+a]='R';
                AppendListNode(allmoves, rook3);
                rook3->prow = (position/8);
                rook3->pcolum = (position %8)+97;
                rook3->row = (position+a)/8;
                rook3->colum = (position+a)%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *rook4=CopyBoard(currentBoard);
                rook4->piece[position]=' ';
                rook4->piece[position+a]='R';
                AppendListNode(allmoves, rook4);
                rook4->prow = (position/8);
                rook4->pcolum = (position %8)+97;
                rook4->row = (position+a)/8;
                rook4->colum = (position+a)%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }
        for(a =1; a<=bo;a++){
        //counting the ver | bottom one
            temp=currentBoard->piece[(position-8*a)]; 
            if (temp==' '){
                GBOARD *rook5=CopyBoard(currentBoard);
                rook5->piece[position]=' ';
                rook5->piece[position-(8*a)]='R';
                AppendListNode(allmoves, rook5);
                rook5->prow = (position/8);
                rook5->pcolum = (position %8)+97;
                rook5->row = (position-(8*a))/8;
                rook5->colum = (position-(8*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *rook6=CopyBoard(currentBoard);
                rook6->piece[position]=' ';
                rook6->piece[position-(8*a)]='R';
                AppendListNode(allmoves, rook6);
                rook6->prow = (position/8);
                rook6->pcolum = (position %8)+97;
                rook6->row = (position-(8*a))/8;
                rook6->colum = (position-(8*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }
        for (a = 1;a <=up; a++){
        //counting the ver | the upper one
            temp=currentBoard->piece[position+8*a]; 
            if (currentBoard->piece[position+(8*a)]==' '){
                GBOARD *rook7=CopyBoard(currentBoard);
                rook7->piece[position]=' ';
                rook7->piece[position+(8*a)]='R';
                AppendListNode(allmoves, rook7);
                rook7->prow = (position/8);
                rook7->pcolum = (position %8)+97;
                rook7->row = (position+(8*a))/8;
                rook7->colum = (position+(8*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *rook8=CopyBoard(currentBoard);
                rook8->piece[position]=' ';
                rook8->piece[position+(8*a)]='R';
                AppendListNode(allmoves, rook8);
                rook8->prow = (position/8);
                rook8->pcolum = (position %8)+97;
                rook8->row = (position+(8*a))/8;
                rook8->colum = (position+(8*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }//THIS IS FOR THE ROOK

        for (;;){
            //determine how many times should we do the +7
            if ((temp_p7 >= 56) && (temp_p7 <= 63)){
                break;
                //if the position ==56-63, break
            } 
            temp_p7 = temp_p7+7;
            psev = psev+1;
            if ((temp_p7 >= 56) && (temp_p7 <= 63)){
                break;
                //we get the plus seve times
            } 
            if (temp_p7==0||temp_p7==8||temp_p7==16||temp_p7==24||temp_p7==32||temp_p7==40||temp_p7||48||temp_p7==56){
              break;
            }
        }
        for (;;){
            //determine how many times should we do the -7
            if ((temp_m7>=0)&&(temp_m7<=7)){
              break;
            }
            temp_m7 = temp_m7-7;
            msev = msev+1;
            if (temp_m7==7||temp_m7==15||temp_m7==23||temp_m7==31||temp_m7==39||temp_m7==47||temp_m7==55||temp_m7==63){
                break;
                //we get the - seve times
            }
            if ((temp_m7>=0)&&(temp_m7<=7)){
              break;
            }
        } 
        for (;;){
            //determine how many times should we do the +9
            if ((temp_p9 >= 56) && (temp_p9 <=63)){
                break;
                //we get the plus nine times
            }
            temp_p9 = temp_p9+9;
            pnin = pnin+1;
            if ((temp_p9 >= 56) && (temp_p9 <=63)){
                break;
                //we get the plus nine times
            } 
            if(temp_p9==7||temp_p9==15||temp_p9==23||temp_p9==31||temp_p9==39||temp_p9==47||temp_p9==55||temp_p9==63){
              break;
            }
        }
        for (;;){
            //determine how many times should we do the -9
             if ((temp_m9>=0)&&(temp_m9<=7)){
              break;
            }
            temp_m9 = temp_m9-9;
            mnin = mnin+1;
            if (temp_m9==0||temp_m9==8||temp_m9==16||temp_m9==24||temp_m9==32||temp_m9==40||temp_m9==48||temp_m9==56){
                break;
                //we get the - nine times
            }
            if ((temp_m9>=0)&&(temp_m9<=7)){
              break;
            }
        }
        for (a= 1; a <=psev; a++){
            //check for the +7 one
            temp=currentBoard->piece[position+(7*a)]; 
            if (temp==' '){
                GBOARD *bis1=CopyBoard(currentBoard);
                bis1->piece[position]=' ';
                bis1->piece[position+(7*a)]='b';
                AppendListNode(allmoves, bis1);
                bis1->prow = position /8;
                bis1->pcolum = position %8+97;
                bis1->row = (position+(7*a))/8;
                bis1->colum = (position+(7*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis2=CopyBoard(currentBoard);
                bis2->piece[position]=' ';
                bis2->piece[position+(7*a)]='b';
                AppendListNode(allmoves, bis2);
                bis2->prow = position /8;
                bis2->pcolum = position %8+97;
                bis2->row = (position+(7*a))/8;
                bis2->colum = (position+(7*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        
        }   
        for (a= 1; a <=msev; a++){
            //check for the -7 one 
            temp=currentBoard->piece[position-(7*a)];
            if (temp==' '){
                GBOARD *bis3=CopyBoard(currentBoard);
                bis3->piece[position]=' ';
                bis3->piece[position-(7*a)]='b';
                AppendListNode(allmoves, bis3);
                bis3->prow = position /8;
                bis3->pcolum = position %8+97;
                bis3->row = (position-(7*a))/8;
                bis3->colum = (position-(7*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis4=CopyBoard(currentBoard);
                position = position -1;
                bis4->piece[position]=' ';
                bis4->piece[position-(7*a)]='b';
                AppendListNode(allmoves, bis4);
                bis4->prow = (position /8);
                bis4->pcolum = (position %8)+97;
                bis4->row = (position-(7*a))/8;
                bis4->colum = (position-(7*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }   
        for (a= 1; a <=pnin; a++){
        //check for the +9 one
            temp=currentBoard->piece[position+(9*a)]; 
            if (temp==' '){
                GBOARD *bis5=CopyBoard(currentBoard);
                bis5->piece[position]=' ';
                bis5->piece[position+(9*a)]='b';
                AppendListNode(allmoves, bis5);
                bis5->prow = (position /8);
                bis5->pcolum = (position %8)+97;
                bis5->row = (position+(9*a))/8;
                bis5->colum = (position+(9*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis6=CopyBoard(currentBoard);
                bis6->piece[position]=' ';
                bis6->piece[position+(9*a)]='b';
                AppendListNode(allmoves, bis6);
                bis6->prow = (position /8);
                bis6->pcolum = (position %8)+97;
                bis6->row = (position+(9*a))/8;
                bis6->colum = (position+(9*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }
    
        for (a= 1; a <=mnin; a++){
        //check for the -9 one
            temp=currentBoard->piece[position-(9*a)]; 
            if (temp==' '){
                GBOARD *bis7=CopyBoard(currentBoard);
                bis7->piece[position]=' ';
                bis7->piece[position-(9*a)]='b';
                AppendListNode(allmoves, bis7);
                bis7->prow = (position /8);
                bis7->pcolum = (position %8)+97;
                bis7->row = (position-(9*a))/8;
                bis7->colum = (position-(9*a))%8+97;
            }
            else if ((temp=='K')||(temp=='Q')||(temp=='R')||(temp=='B')||(temp=='N')||(temp=='P')){
                GBOARD *bis8=CopyBoard(currentBoard);
                bis8->piece[position]=' ';
                bis8->piece[position-(9*a)]='b';
                AppendListNode(allmoves, bis8);
                bis8->prow = (position /8);
                bis8->pcolum = (position %8)+97;
                bis8->row = (position-(9*a))/8;
                bis8->colum = (position-(9*a))%8+97;
                break;
            }
            else if ((temp=='k')||(temp=='q')||(temp=='r')||(temp=='b')||(temp=='n')||(temp=='p')){
                break;
            }
        }    
    }//THIS IS THE BISHOP 
}//THIS IS THE QUEEN



//Checks if the enemy King is in check
bool check(GBOARD *currentBoard){
    int king=-1;
    bool pawn=false, queen=false, knight=false, bishop=false, rook=false, kingf=false;
    //finding the king
    //Player 1 king
    if (currentBoard->playerflag==2){
        for(int i=0; i<64; i++){
            if(currentBoard->piece[i]=='K'){
                king=i;
                i=64;
            }
        }
    }
    //Player 2 king
    else{
        for(int i=0; i<64; i++){
            if(currentBoard->piece[i]=='k'){
                king=i;
                i=64;
            }
        }
    }

    //if it is attacked by a king
    //Player 1 king
    if(currentBoard->playerflag==2){
        //top
        if (king<55){
            if (currentBoard->piece[king+8]!=' '){
                if (currentBoard->piece[king+8]=='k'){
                    kingf=true;
                }
            }
        }
        //bottom
        if (king>7){
            if (currentBoard->piece[king-8]!=' '){
                if (currentBoard->piece[king-8]=='k'){
                    kingf=true;
                }
            }
        }
        //left
        if (king%8!=0){
            if (currentBoard->piece[king-1]!=' '){
                if (currentBoard->piece[king-1]=='k'){
                    kingf=true;
                }
            }
        }
        //right
        if (king%8!=7){
            if (currentBoard->piece[king+1]!=' '){
                if (currentBoard->piece[king+1]=='k'){
                    kingf=true;
                }
            }
        }
        //top right 
        if (king<55 || king%8!=7){
            if (currentBoard->piece[king+9]!=' '){
                if (currentBoard->piece[king+9]=='k'){
                    kingf=true;
                }
            }
        }
        //top left
        if (king<55 || king%8!=0){
            if (currentBoard->piece[king+7]!=' '){
                if (currentBoard->piece[king+7]=='k'){
                    kingf=true;
                }
            }
        }
        //bottom right
        if (king>7 || king%8!=7){
            if (currentBoard->piece[king-7]!=' '){
                if (currentBoard->piece[king-7]=='k'){
                    kingf=true;
                }
            }
        }
        //bottom left
        if (king>7 || king%8!=0){
            if (currentBoard->piece[king-9]!=' '){
                if (currentBoard->piece[king-9]=='k'){
                    kingf=true;
                }
            }
        }
    }
    //Player 2 king
    else{
        //top
        if (king<55){
            if (currentBoard->piece[king+8]!=' '){
                if (currentBoard->piece[king+8]=='K'){
                    kingf=true;
                }
            }
        }
        //bottom
        if (king>7){
            if (currentBoard->piece[king-8]!=' '){
                if (currentBoard->piece[king-8]=='K'){
                    kingf=true;
                }
            }
        }
        //left
        if (king%8!=0){
            if (currentBoard->piece[king-1]!=' '){
                if (currentBoard->piece[king-1]=='K'){
                    kingf=true;
                }
            }
        }
        //right
        if (king%8!=7){
            if (currentBoard->piece[king+1]!=' '){
                if (currentBoard->piece[king+1]=='K'){
                    kingf=true;
                }
            }
        }
        //top right 
        if (king<55 || king%8!=7){
            if (currentBoard->piece[king+9]!=' '){
                if (currentBoard->piece[king+9]=='K'){
                    kingf=true;
                }
            }
        }
        //top left
        if (king<55 || king%8!=0){
            if (currentBoard->piece[king+7]!=' '){
                if (currentBoard->piece[king+7]=='K'){
                    kingf=true;
                }
            }
        }
        //bottom right
        if (king>7 || king%8!=7){
            if (currentBoard->piece[king-7]!=' '){
                if (currentBoard->piece[king-7]=='K'){
                    kingf=true;
                }
            }
        }
        //bottom left
        if (king>7 || king%8!=0){
            if (currentBoard->piece[king-9]!=' '){
                if (currentBoard->piece[king-9]=='K'){
                    kingf=true;
                }
            }
        }
    }
    



    //if it is attacked by a pawn
    //Player 1 king
    if (currentBoard->playerflag==2){
        if (king>=55 && king<=63){
        //Can't be in check by an enemy pawn
        }
        else if ((((king/8)!=((king+7)/8)) && currentBoard->piece[king+7]=='p')||((((king/8)+1)!=((king+9)/8)) && (currentBoard->piece[king+9]=='p'))){
            pawn=true;
        }   
    }
    //Player 2 king
    else{
        if (king>=0 && king<=7){
        //Can't be in check by an enemy pawn
        }
        else if ((((king/8)!=((king-7)/8)) && currentBoard->piece[king-7]=='P')||((((king/8)-1)!=((king-9)/8)) && (currentBoard->piece[king-9]=='P'))){
            pawn=true;
        }   
    }

    //if it is attacked by a rook
    //Player 1 king
    if (currentBoard->playerflag==2){
        //checking from the right
        for(int i=1; ((king+i)<(((king/8)+1)*8)); i++){
            if(currentBoard->piece[king+i]!=' '){
                if(currentBoard->piece[king+i]=='r'){
                    rook=true;
                }
                i=6;
            }
        }
        //checking from the left
        for(int i=1; ((king-i)>((king/8)*8)); i++){
            if(currentBoard->piece[king+i]!=' '){
                if(currentBoard->piece[king+i]=='r'){
                    rook=true;
                }
                i=6;
            }
        }
        //checking from the top
        for(int i=1; (king+i*8)<64; i++){
            if(currentBoard->piece[king+i*8]!=' '){
                if(currentBoard->piece[king+i*8]=='r'){
                    rook=true;
                }
                i=8;
            }
        }
        //checking from the bottom
        for(int i=1; (king-i*8)>=0; i++){
            if(currentBoard->piece[king-i*8]!=' '){
                if(currentBoard->piece[king-i*8]=='r'){
                    rook=true;
                }
                i=8;
            }
        }
    }
    //Player 2 king
    else{
        for(int i=1; ((king+i)<(((king/8)+1)*8)); i++){
            if(currentBoard->piece[king+i]!=' '){
                if(currentBoard->piece[king+i]=='R'){
                    rook=true;
                }
                i=6;
            }
        }
        //checking from the left
        for(int i=1; ((king-i)>((king/8)*8)); i++){
            if(currentBoard->piece[king+i]!=' '){
                if(currentBoard->piece[king+i]=='R'){
                    rook=true;
                }
                i=6;
            }
        }
        //checking from the top
        for(int i=1; (king+i*8)<64; i++){
            if(currentBoard->piece[king+i*8]!=' '){
                if(currentBoard->piece[king+i*8]=='R'){
                    rook=true;
                }
                i=8;
            }
        }
        //checking from the bottom
        for(int i=1; (king-i*8)>=0; i++){
            if(currentBoard->piece[king-i*8]!=' '){
                if(currentBoard->piece[king-i*8]=='R'){
                    rook=true;
                }
                i=8;
            }
        }
    }

    //if it is attacked by a bishop
    //Player 1 king
    if (currentBoard->playerflag==2){
        //checking from the top left
        for(int i=1; (king+i*8-i)<8 && ((king+i*8-i)/8)!=(king/8+i-1); i++){
            if(currentBoard->piece[king+i*8-i]!=' '){
                if(currentBoard->piece[king+i*8-i]=='b'){
                    bishop=true;
                }
                i=8;
            }
        }
        //checking from the top right
        for(int i=1; (king+i*8+i)<8 && ((king+i*8+i)/8)!=(king/8+i+1); i++){
            if(currentBoard->piece[king+i*8+i]!=' '){
                if(currentBoard->piece[king+i*8+i]=='b'){
                    bishop=true;
                }
                i=8;
            }
        }
        //checking from the bottom left
        for(int i=1; (king-i*8-i)>=0 && ((king-i*8-i)/8)!=(king/8-i-1); i++){
            if(currentBoard->piece[king-i*8-i]!=' '){
                if(currentBoard->piece[king-i*8-i]=='b'){
                    bishop=true;
                }
                i=8;
            }
        }
        //checking from the bottom right
        for(int i=1; (king-i*8+i)>=0 && ((king-i*8+i)/8)!=(king/8-i+1); i++){
            if(currentBoard->piece[king-i*8+i]!=' '){
                if(currentBoard->piece[king-i*8+i]=='b'){
                    bishop=true;
                }
                i=8;
            }
        }
    }
    //Player 2 king
    else{
        //checking from the top left
        for(int i=1; (king+i*8-i)<8 && ((king+i*8-i)/8)!=(king/8+i-1); i++){
            if(currentBoard->piece[king+i*8-i]!=' '){
                if(currentBoard->piece[king+i*8-i]=='B'){
                    bishop=true;
                }
                i=8;
            }
        }
        //checking from the top right
        for(int i=1; (king+i*8+i)<8 && ((king+i*8+i)/8)!=(king/8+i+1); i++){
            if(currentBoard->piece[king+i*8+i]!=' '){
                if(currentBoard->piece[king+i*8+i]=='B'){
                    bishop=true;
                }
                i=8;
            }
        }
        //checking from the bottom left
        for(int i=1; (king-i*8-i)>=0 && ((king-i*8-i)/8)!=(king/8-i-1); i++){
            if(currentBoard->piece[king-i*8-i]!=' '){
                if(currentBoard->piece[king-i*8-i]=='B'){
                    bishop=true;
                }
                i=8;
            }
        }
        //checking from the bottom right
        for(int i=1; (king-i*8+i)>=0 && ((king-i*8+i)/8)!=(king/8-i+1); i++){
            if(currentBoard->piece[king-i*8+i]!=' '){
                if(currentBoard->piece[king-i*8+i]=='B'){
                    bishop=true;
                }
                i=8;
            }
        }
    }

    //if it is attacked by a queen
    //Player 1 king
    if (currentBoard->playerflag==2){
        //checking from the right
        for(int i=1; ((king+i)<(((king/8)+1)*8)); i++){
            if(currentBoard->piece[king+i]!=' '){
                if(currentBoard->piece[king+i]=='q'){
                    queen=true;
                }
                i=6;
            }
        }
        //checking from the left
        for(int i=1; ((king-i)>((king/8)*8)); i++){
            if(currentBoard->piece[king+i]!=' '){
                if(currentBoard->piece[king+i]=='q'){
                    queen=true;
                }
                i=6;
            }
        }
        //checking from the top
        for(int i=1; (king+i*8)<64; i++){
            if(currentBoard->piece[king+i*8]!=' '){
                if(currentBoard->piece[king+i*8]=='q'){
                    queen=true;
                }
                i=8;
            }
        }
        //checking from the bottom
        for(int i=1; (king-i*8)>=0; i++){
            if(currentBoard->piece[king-i*8]!=' '){
                if(currentBoard->piece[king-i*8]=='q'){
                    queen=true;
                }
                i=8;
            }
        }
        //checking from the top left
        for(int i=1; (king+i*8-i)<8 && ((king+i*8-i)/8)!=(king/8+i-1); i++){
            if(currentBoard->piece[king+i*8-i]!=' '){
                if(currentBoard->piece[king+i*8-i]=='q'){
                    queen=true;
                }
                i=8;
            }
        }
        //checking from the top right
        for(int i=1; (king+i*8+i)<8 && ((king+i*8+i)/8)!=(king/8+i+1); i++){
            if(currentBoard->piece[king+i*8+i]!=' '){
                if(currentBoard->piece[king+i*8+i]=='q'){
                    queen=true;
                }
                i=8;
            }
        }
        //checking from the bottom left
        for(int i=1; (king-i*8-i)>=0 && ((king-i*8-i)/8)!=(king/8-i-1); i++){
            if(currentBoard->piece[king-i*8-i]!=' '){
                if(currentBoard->piece[king-i*8-i]=='q'){
                    queen=true;
                }
                i=8;
            }
        }
        //checking from the bottom right
        for(int i=1; (king-i*8+i)>=0 && ((king-i*8+i)/8)!=(king/8-i+1); i++){
            if(currentBoard->piece[king-i*8+i]!=' '){
                if(currentBoard->piece[king-i*8+i]=='q'){
                    queen=true;
                }
                i=8;
            }
        }
    }
    //Player 2 king
    else{
        //checking from the right
        for(int i=1; ((king+i)<(((king/8)+1)*8)); i++){
            if(currentBoard->piece[king+i]!=' '){
                if(currentBoard->piece[king+i]=='Q'){
                    queen=true;
                }
                i=6;
            }
        }
        //checking from the left
        for(int i=1; ((king-i)>((king/8)*8)); i++){
            if(currentBoard->piece[king+i]!=' '){
                if(currentBoard->piece[king+i]=='Q'){
                    queen=true;
                }
                i=6;
            }
        }
        //checking from the top
        for(int i=1; (king+i*8)<64; i++){
            if(currentBoard->piece[king+i*8]!=' '){
                if(currentBoard->piece[king+i*8]=='Q'){
                    queen=true;
                }
                i=8;
            }
        }
        //checking from the bottom
        for(int i=1; (king-i*8)>=0; i++){
            if(currentBoard->piece[king-i*8]!=' '){
                if(currentBoard->piece[king-i*8]=='Q'){
                    queen=true;
                }
                i=8;
            }
        }
        //checking from the top left
        for(int i=1; (king+i*8-i)<8 && ((king+i*8-i)/8)!=(king/8+i-1); i++){
            if(currentBoard->piece[king+i*8-i]!=' '){
                if(currentBoard->piece[king+i*8-i]=='Q'){
                    queen=true;
                }
                i=8;
            }
        }
        //checking from the top right
        for(int i=1; (king+i*8+i)<8 && ((king+i*8+i)/8)!=(king/8+i+1); i++){
            if(currentBoard->piece[king+i*8+i]!=' '){
                if(currentBoard->piece[king+i*8+i]=='Q'){
                    queen=true;
                }
                i=8;
            }
        }
        //checking from the bottom left
        for(int i=1; (king-i*8-i)>=0 && ((king-i*8-i)/8)!=(king/8-i-1); i++){
            if(currentBoard->piece[king-i*8-i]!=' '){
                if(currentBoard->piece[king-i*8-i]=='Q'){
                    queen=true;
                }
                i=8;
            }
        }
        //checking from the bottom right
        for(int i=1; (king-i*8+i)>=0 && ((king-i*8+i)/8)!=(king/8-i+1); i++){
            if(currentBoard->piece[king-i*8+i]!=' '){
                if(currentBoard->piece[king-i*8+i]=='Q'){
                    queen=true;
                }
                i=8;
            }
        }
    }

    //if it is attacked by a knight
    //Player 1 king
    if (currentBoard->playerflag==2){
        //checking the two top
        if(king+24+1<64){
            if(currentBoard->piece[king+24-1]=='k' && ((king+24-1)/8==(king+24)/8)){
                knight=true;
            }
        }
        if(king+24-1<64){
            if(currentBoard->piece[king+24+1]=='k' && ((king+24+1)/8==(king+24)/8)){
                knight=true;
            }
        }
    
        //checking the bottom two
        if(king-24-1>=0){
            if(currentBoard->piece[king-24-1]=='k' && ((king-24-1)/8==(king-24)/8)){
                knight=true;
            }
        }
        if(king-24+1>=0){
            if(currentBoard->piece[king-24+1]=='k' && ((king-24+1)/8==(king-24)/8)){
                knight=true;
            }
        }
        
        //checking the left two
        if(king-2+8<64){
            if(currentBoard->piece[king-2+8]=='k' && ((king-2+8)/8==king/8+1)){
                knight=true;
            }
        }
        if(king-2-8>=0){
            if(currentBoard->piece[king-2-8]=='k' && ((king-2-8)/8==king/8-1)){
                knight=true;
            }
        }
        
        //checking the right two
        if(king+2+8<64){
            if(currentBoard->piece[king+2+8]=='k' && ((king+2+8)/8==king/8+1)){
                knight=true;
            }
        }
        if(king+2-8>=0){
            if(currentBoard->piece[king+2-8]=='k' && ((king+2-8)/8==king/8-1)){
                knight=true;
            }
        }
    }
    //Player 2 king
    else{
        //checking the two top
        if(king+24+1<64){
            if(currentBoard->piece[king+24-1]=='K' && ((king+24-1)/8==(king+24)/8)){
                knight=true;
            }
        }
        if(king+24-1<64){
            if(currentBoard->piece[king+24+1]=='K' && ((king+24+1)/8==(king+24)/8)){
                knight=true;
            }
        }
    
        //checking the bottom two
        if(king-24-1>=0){
            if(currentBoard->piece[king-24-1]=='K' && ((king-24-1)/8==(king-24)/8)){
                knight=true;
            }
        }
        if(king-24+1>=0){
            if(currentBoard->piece[king-24+1]=='K' && ((king-24+1)/8==(king-24)/8)){
                knight=true;
            }
        }
        
        //checking the left two
        if(king-2+8<64){
            if(currentBoard->piece[king-2+8]=='K' && ((king-2+8)/8==king/8+1)){
                knight=true;
            }
        }
        if(king-2-8>=0){
            if(currentBoard->piece[king-2-8]=='K' && ((king-2-8)/8==king/8-1)){
                knight=true;
            }
        }
        
        //checking the right two
        if(king+2+8<64){
            if(currentBoard->piece[king+2+8]=='K' && ((king+2+8)/8==king/8+1)){
                knight=true;
            }
        }
        if(king+2-8>=0){
            if(currentBoard->piece[king+2-8]=='K' && ((king+2-8)/8==king/8-1)){
                knight=true;
            }
        }
    }
    
    if(queen==true || pawn==true || rook==true || bishop==true || knight==true || kingf==true){
        return true;
    }
    else{
        return false;
    }           
}//END OF CHECK

int checkmate(GBOARD *currentBoard){
    int king=-1;
    if(check(currentBoard)==true){
        if (currentBoard->playerflag==1){
            //searches for enemy king
            for(int i=0; i<64; i++){
                if(currentBoard->piece[i]=='k'){
                    king=i;
                    i=64;
                }
            }
            //make a board for each spot a king can move
            TNODE *kingcheck=CreateTree();
            kingmoves(currentBoard, king, kingcheck); 
            //checking if all possible moves for the king are in check still
            if(kingcheck->list->first==NULL){
                DeleteTree(kingcheck);
                return 1; 
            }           
        }
        else{
            //searches for enemy king
            for(int i=0; i<64; i++){
                if(currentBoard->piece[i]=='K'){
                    king=i;
                    i=64;
                }
            }
            //make a board for each spot a king can move 
            TNODE *kingcheck=CreateTree();
            kingmoves(currentBoard, king, kingcheck); 
            //checking if all possible moves for the king are in check still
            if(kingcheck->list->first==NULL){
                DeleteTree(kingcheck);
                return 2; 
            }           
        } 
    }
    return 0;   
}//END OF CHECKMATE


//EOF
