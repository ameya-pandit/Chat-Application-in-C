//playersmove.c file
//this is the file for the function that asks for player input and moves the piece
//Team04

GBOARD *playersmove(TNODE *treenode){
    int spot, dest, currow, newrow;
    char piece, curcol, newcol;
    bool flag=false;
    do{
        do{
            //Finds position of the piece
            spot=GetUserInput();
            if (spot>=600){
                if (spot==600){
                    flag=true;
                }
            }
            else if(spot>=0 && spot<=63){
                piece=treenode->board.[spot];
                if(treenode->board.playerflag==1){
                    if((piece!='K')||(piece!='Q')||(piece!='R')||(piece!='B')||(piece!='N')||(piece!='P')){
                        printf("Invalid piece to move\n");
                    }
                    else{
                        flag=true;
                    }
                }
                if(treenode->board.playerflag==2){
                    if((piece!='k')||(piece!='q')||(piece!='r')||(piece!='b')||(piece!='n')||(piece!='p')){
                        printf("Invalid piece to move\n");
                    }
                    else{
                        flag=true;
                    }
                }
            }
            else{
                printf("Invalid Input\n");
                flag=false;
            }
        }while(flag==false);
    }while(flag==false);

    //Ask for where the player wants to move the piece
    do{
        dest=GetUserInput();
        if (dest>=600){
            if (dest==600){
                flag=true;
            }
        }
        else if(dest>=0 && dest<=63){

            TNODE *tree;
            tree = CreateTree();
            
            //Create the list of possible moves at this location.
            checkmove(tree);

            LNODE *node1, *node2;
            if(tree->list->first) {
            node1 = tree->list->first; 
            while(node1){
                node2 = node1->next;
                GBOARD *temp;
                temp = node1->tnode->board;
                
                if((temp->row == newrow) && (temp->prow == currow)
                   && (temp->colum == newcol) && (temp->pcolum == curcol)) {  
                    return temp;
                } 
                node1 = node2;  
            }
        }    
        }
        else{
            printf("Invalid Input\n");
        }
        }while (flag==false);     
}//End of playersmove

void checkpromote(TNODE *treenode){
    char promo;
    if (treenode->board->playerflag==1){
        for(int i=55; i<64; i++){
            if (treenode->board->piece[i]='P'){
                do{
                    printf("Which piece would you like to promote to?");
                    scanf("%c", promo);
                    if(promo=='Q'||promo=='R'||promo=='B'||promo=='N'){
                        treenode->board->piece[i]=promo;
                    }
                    else{
                        printf("Invalid input\n");
                    }
                }while(promo!='Q'||promo!='R'||promo!='B'||promo!='N');
            }
        }
    }
    else{
        for(int i=0; i<8; i++){
            if (treenode->board->piece[i]='p'){
                do{
                    printf("Which piece would you like to promote to?");
                    scanf("%c", promo);
                    if(promo=='q'||promo=='r'||promo=='b'||promo=='n'){
                        treenode->board->piece[i]=promo;
                    }
                    else{
                        printf("Invalid input\n");
                    }
                }while(promo!='q'||promo!='r'||promo!='b'||promo!='n');
            }
        }
    }
}//End of checkpromote


//EOF
