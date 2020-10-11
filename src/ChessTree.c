//
//  ChessTree.c
//
//  Tree for game moves
//
//  Created by Matthew Dunn on 1/12/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

//This is the definition for the functions that operate on the chess tree


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ChessTree.h"
#include "Board.h"
#include "MovesList.h"




//This function is a test main that allows for testing of the components of the tree and the list.
/*
int (void) {

    TNODE *tree;
    tree = CreateTree();
    CreateTestList(tree);
    CreateTestList(tree->list->first->tnode);
    CreateTestList(tree->list->first->tnode->list->first->tnode);
    CreateTestList(tree->list->first->tnode->list->first->next->tnode);
    printf("The depth of the node is:  %d\n", tree->list->first->tnode->depth);
    printf("The depth of the next nodes back node is:  %d\n", tree->list->first->tnode->list->first->tnode->back->depth);
    printf("The depth of the node is:  %d\n", tree->list->first->tnode->list->first->tnode->list->first->next->next->tnode->depth);
    DeleteTree(tree); 
    return 0; 
}
*/





//test function this is temporary to test out the components of the list and the tree.
GBOARD *create(void) {

    GBOARD *board;
    board = malloc(sizeof(GBOARD));
    return board;
}





// Create a new node in the tree (used to create a tree node that already has a list underneath)
TNODE *CreateTreeNode(void)
{
    TNODE *node = NULL;
    node = malloc(sizeof(TNODE));
    if(!node) {
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    node->list = NULL;
    node->board = NULL;
    node->back = NULL;
    node->depth = 0;
    return node;
}



//Delstes the tree node. The list in the node must be null.
void DeleteTreeNode(TNODE *node)
{
    assert(node);
    if(node->board){
        DeleteBoard(node->board);

   node->board = NULL;
        node->board = NULL;
    }
    if(node->list) {
        DeleteMoveList(node->list);
        node->list = NULL;
    }      
    free(node);
    return;
}



//This function deletes the tree and uses recursion to make sure all of the lists are deleted
void DeleteTree(TNODE *node) {
    assert(node);
    
    if(node->list) {
        DeleteMoveList(node->list);
        node->list = NULL;
    }
    //added make sure to replace this with the delete board function
    if(node->board) {
    free(node->board);
    }
    free(node);   
    return;
}





//Append a list to the tree node
void AppendList(TNODE *node, MLIST *list)
{
    assert(node);
    assert(list);
    if(!node->list) {
        node->list = list;
        list->parent = node;
    }
    return;
}



//Creates a tree and list under the tree
TNODE *CreateTree(void)
{
    TNODE *tree;
    tree = CreateTreeNode();
    assert(tree);
    
    MLIST *list;
    list = CreateMoveList();
    assert(list);
  
    AppendList(tree,list);

    return tree;
}
   

//EOF
