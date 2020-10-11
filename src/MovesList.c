//
//  Board.h
//  GameBoard
//
//  Created by Matthew Dunn on 1/12/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

//This file contains the functions that handle the double linked list of moves


#include <stdlib.h>
#include <assert.h>
#include "MovesList.h"
#include "ChessTree.h"


// Create a new node in the list 
LNODE *CreateListNode(void)
{
    LNODE *node = NULL;
    node = malloc(sizeof(LNODE));
    if(!node) {
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    node->head = NULL;
    node->next = NULL;
    node->prev = NULL;
    node->tnode = NULL;
    return node;
}



// Delete a node from the list (and the Tree node) 
void DeleteListNode(LNODE *node)
{
    assert(node);
    if(node->tnode) {
        DeleteTreeNode(node->tnode);
        node->tnode = NULL;
    }
    free(node);
    return;
}



// Create a new move list 
MLIST *CreateMoveList(void)
{
    MLIST *list;
    list = malloc(sizeof(MLIST));
    if(!list) {
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    list->length = 0;
    list->first = NULL;
    list->last = NULL;
    list->parent = NULL;     
    return list;
}



// Delete an move list (and all entries) 
void DeleteMoveList(MLIST *list)
{
    assert(list);
    LNODE *node1, *node2;
    node1 = list->first;
    while(node1) {
        node2 = node1->next;
        DeleteListNode(node1);
        node1 = node2;
    }
    free(list);   
    node1 = NULL;
    node2 = NULL;
    return;
}





// Insert a node to the list at the end creates a tree node under the list and appends a board there 
void AppendListNode(TNODE *tnode, GBOARD *gboard)
{
    assert(tnode);
    assert(gboard);
    LNODE *node = NULL;
    TNODE *tree = NULL;
    MLIST *list = NULL;
    node = CreateListNode();
    assert(node);
    tree = CreateTreeNode();
    assert(tree);
    list = CreateMoveList();
    assert(list);
    if(tnode->list->last) {
        assert(tnode->list->last);
        node->head = tnode->list;
        node->next = NULL;
        node->prev = tnode->list->last;
        tnode->list->last->next = node;
        tnode->list->last = node;
        tree->back = tnode;
        node->tnode = tree;
        node->tnode->list = list;
        node->tnode->board = gboard;
        
    } else {
          node->head = tnode->list;
          tnode->list->first = node;
          tnode->list->last = node;
          node->prev = NULL;
          node->next = NULL;
          tree->back = tnode;
          node->tnode = tree;
          node->tnode->list = list;
          node->tnode->board = gboard;
    }
    tree->depth = tnode->depth + 1;
    tnode->list->length++;
    return;
}






//Delete the last node in the list
void DeleteLastNode(TNODE *tnode){
    assert(tnode);
    LNODE *node = NULL;
    
    if(tnode->list->last) {
        node = tnode->list->last;
        tnode->list->last = node->prev;
        if(tnode->list->last){
            tnode->list->last->next = NULL;
        } else {
            assert(tnode->list->first = node);
            tnode->list->first = NULL;
        }       
        tnode->list->length--;
        DeleteListNode(node);
    }
    return;
}




/* EOF */
