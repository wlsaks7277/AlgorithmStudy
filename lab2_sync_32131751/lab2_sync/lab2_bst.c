/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*	    Student id : 
*	    Student name : 
*
*   lab2_bst.c :
*       - thread-safe bst code.
*       - coarse-grained, fine-grained lock code
*
*   Implement thread-safe bst for coarse-grained version and fine-grained version.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>

#include "lab2_sync_types.h"





void Queue_Init(queue_t *q){
    node_t *tmp = malloc(sizeof(node_t));
    tmp->next = NULL;
    q->head = q->tail = tmp;
    pthread_mutex_init(&q->headLock, NULL);
    pthread_mutex_init(&q->tailLock, NULL);
}

void Queue_Enqueue(queue_t *q, int value){
    
    node_t *tmp = malloc(sizeof(node_t));
    assert(tmp != NULL);
    tmp->value = value;
    tmp->next = NULL;
    
    if (coarse_grained == 0)
    {
        pthread_mutex_lock(&q->tailLock);
    }
    q->tail->next = tmp;
    q->tail = tmp;
    if (coarse_grained == 0)
    {
        pthread_mutex_unlock(&q->tailLock);
    }
}

int Queue_Dequeue(queue_t *q, int *value){
    if (coarse_grained == 0)
    {
        pthread_mutex_lock(&q->headLock);
    }
    node_t *tmp = q->head;
    node_t *newHead = tmp->next;
    if (newHead == NULL){
        if (coarse_grained == 0)
        {
            pthread_mutex_unlock(&q->headLock);
        }
        return -1; //큐가 비었을때
    }
    *value = newHead->value;
    q->head = newHead;
    if (coarse_grained == 0)
    {
        pthread_mutex_unlock(&q->headLock);
    }
    //int h = tmp->value;
    //free(tmp);
    return 0;
}

void usage(const char *pname){
    printf("usage:&s[option]\n",pname);
    printf("option:[t] | [c]\n");
    printf("t need Add parameter\n");
    printf("ex) %s -t 4 -c 10000\n",pname);
    
}

void single_insert(){
    
    for(int i = 0; i < loop2; i++)
    {
        
        Queue_Enqueue(&q0, 1);
        
    }
    
}

void single_delete(){
    
    
    for(int i = 0; i < loop2; i++)
    {
        
        Queue_Dequeue(&q0, q0.head);
        
    }
    
}

void insert(){
    
    if (coarse_grained == 1)
    {
        
        for(int i = 0; i < loop; i++)
        {
            
            pthread_mutex_lock(&q1.tailLock);
            Queue_Enqueue(&q1, 1);
            pthread_mutex_unlock(&q1.tailLock);
            
        }
    }else{
        for(int i = 0; i < loop; i++)
        {
            Queue_Enqueue(&q2, 1);
        }
    }
    
}

void q_delete(){
    
    if (coarse_grained == 1)
    {
        
        for(int i = 0; i < loop; i++)
        {
            
            pthread_mutex_lock(&q1.headLock);
            Queue_Dequeue(&q1, q1.head);
            pthread_mutex_unlock(&q1.headLock);
            
        }
    }else{
        for(int i = 0; i < loop; i++)
        {
            Queue_Dequeue(&q2, q2.head);
        }
    }
    
}


/*
 * TODO
 *  Implement funtction which traverse BST in in-order
 *  
 *  @param lab2_tree *tree  : bst to print in-order. 
 *  @return                 : status (success or fail)
 */
int lab2_node_print_inorder(lab2_tree *tree) {
    // You need to implement lab2_node_print_inorder function.
}

/*
 * TODO
 *  Implement function which creates struct lab2_tree
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_tree )
 * 
 *  @return                 : bst which you created in this function.
 */
lab2_tree *lab2_tree_create() {
    // You need to implement lab2_tree_create function.
}

/*
 * TODO
 *  Implement function which creates struct lab2_node
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param int key          : bst node's key to creates
 *  @return                 : bst node which you created in this function.
 */
lab2_node * lab2_node_create(int key) {
    // You need to implement lab2_node_create function.
}

/* 
 * TODO
 *  Implement a function which insert nodes from the BST. 
 *  
 *  @param lab2_tree *tree      : bst which you need to insert new node.
 *  @param lab2_node *new_node  : bst node which you need to insert. 
 *  @return                 : satus (success or fail)
 */
int lab2_node_insert(lab2_tree *tree, lab2_node *new_node){
    // You need to implement lab2_node_insert function.

}

/* 
 * TODO
 *  Implement a function which insert nodes from the BST in fine-garined manner.
 *
 *  @param lab2_tree *tree      : bst which you need to insert new node in fine-grained manner.
 *  @param lab2_node *new_node  : bst node which you need to insert. 
 *  @return                     : status (success or fail)
 */
int lab2_node_insert_fg(lab2_tree *tree, lab2_node *new_node){
      // You need to implement lab2_node_insert_fg function.
}

/* 
 * TODO
 *  Implement a function which insert nodes from the BST in coarse-garined manner.
 *
 *  @param lab2_tree *tree      : bst which you need to insert new node in coarse-grained manner.
 *  @param lab2_node *new_node  : bst node which you need to insert. 
 *  @return                     : status (success or fail)
 */
int lab2_node_insert_cg(lab2_tree *tree, lab2_node *new_node){
    // You need to implement lab2_node_insert_cg function.
}

/* 
 * TODO
 *  Implement a function which remove nodes from the BST.
 *
 *  @param lab2_tree *tree  : bst tha you need to remove node from bst which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove(lab2_tree *tree, int key) {
    // You need to implement lab2_node_remove function.
}

/* 
 * TODO
 *  Implement a function which remove nodes from the BST in fine-grained manner.
 *
 *  @param lab2_tree *tree  : bst tha you need to remove node in fine-grained manner from bst which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove_fg(lab2_tree *tree, int key) {
    // You need to implement lab2_node_remove_fg function.
}


/* 
 * TODO
 *  Implement a function which remove nodes from the BST in coarse-grained manner.
 *
 *  @param lab2_tree *tree  : bst tha you need to remove node in coarse-grained manner from bst which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove_cg(lab2_tree *tree, int key) {
    // You need to implement lab2_node_remove_cg function.
}


/*
 * TODO
 *  Implement function which delete struct lab2_tree
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param lab2_tree *tree  : bst which you want to delete. 
 *  @return                 : status(success or fail)
 */
void lab2_tree_delete(lab2_tree *tree) {
    // You need to implement lab2_tree_delete function.
}

/*
 * TODO
 *  Implement function which delete struct lab2_node
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param lab2_tree *tree  : bst node which you want to remove. 
 *  @return                 : status(success or fail)
 */
void lab2_node_delete(lab2_node *node) {
    // You need to implement lab2_node_delete function.
}

