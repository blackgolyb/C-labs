#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTNode
{
    void *data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

/**
 * @brief  BST compare function for your type of elements
 * @return  -1 if first less than second element 1 if greater and 0 if equal
 * 
 */
typedef int (* BSTCmpFun)(void *a, void *b);

typedef struct BST
{
    BSTNode *root;
    BSTCmpFun cmp;
} BST;


BST *bst_create();
int bst_len(BST *tree);
void bst_destroy(BST *tree);
void bst_insert(BST *tree, void *elem);
void *bst_max(BST *tree);
void *bst_min(BST *tree);
BSTNode *bst_find_node(BST *tree, void *elem);
BSTNode *bst_find_parent(BST *tree, void *elem);
BSTNode *bst_max_node(BST *tree);
BSTNode *bst_min_node(BST *tree);
void bst_delete(BST *tree, void *elem);

#endif