#include "bst.h"

BST *bst_create(BSTCmpFun cmp)
{
    BST *tree = malloc(sizeof(BST));
    tree->root = NULL;
    tree->cmp = cmp;
    return tree;
}

int __bst__len_body(BSTNode *node)
{
    if (!node)
        return 0;

    return 1 + __bst__len_body(node->left) + __bst__len_body(node->right);
}

int bst_len(BST *tree)
{
    return __bst__len_body(tree->root);
}

void __bst__destroy_body(BSTNode *node)
{
    if (!node)
        return;

    __bst__destroy_body(node->left);
    __bst__destroy_body(node->right);
    free(node);
}

void bst_destroy(BST *tree)
{
    __bst__destroy_body(tree->root);
    free(tree);
}

void bst_insert(BST *tree, void *elem)
{
    BSTNode *node = malloc(sizeof(BSTNode));
    node->data = elem;
    node->left = NULL;
    node->right = NULL;

    if (tree->root == NULL)
    {
        tree->root = node;
        return;
    }

    BSTNode *tmp = tree->root;
    BSTNode *parent = NULL;
    while (tmp)
    {
        parent = tmp;
        if (tree->cmp(elem, tmp->data) == 1)
            tmp = tmp->right;
        else
            tmp = tmp->left;
    }

    if (tree->cmp(elem, parent->data) == 1)
        parent->right = node;
    else
        parent->left = node;
}

BSTNode *bst_find_node(BST *tree, void *elem)
{
    if (tree == NULL || tree->root == NULL || tree->root == elem)
        return NULL;

    BSTNode *node = tree->root;
    while (node)
    {
        if (tree->cmp(elem, node->data) == 0)
            return node;
        else if (tree->cmp(elem, node->data) == 1)
            node = node->right;
        else
            node = node->left;
    }

    return NULL;
}

BSTNode *bst_find_parent(BST *tree, void *elem)
{
    if (tree == NULL || tree->root == NULL)
        return NULL;

    BSTNode *node = tree->root;
    while (node)
    {
        if (node->left && tree->cmp(node->left->data, elem) == 0)
            return node;
        else if (node->right && tree->cmp(node->right->data, elem) == 0)
            return node;
        else if (tree->cmp(elem, node->data) == 1)
            node = node->right;
        else
            node = node->left;
    }

    return NULL;
}

BSTNode *bst_max_node(BST *tree)
{
    if (tree == NULL || tree->root == NULL)
        return NULL;

    BSTNode *node = tree->root;
    while (node->right)
        node = node->right;

    return node;
}
BSTNode *bst_min_node(BST *tree)
{
    if (tree == NULL || tree->root == NULL)
        return NULL;

    BSTNode *node = tree->root;
    while (node->left)
        node = node->left;

    return node;
}

void *bst_max(BST *tree)
{
    return bst_max_node(tree)->data;
}

void *bst_min(BST *tree)
{
    return bst_min_node(tree)->data;
}

void bst_delete(BST *tree, void *elem)
{
    BSTNode *node = bst_find_node(tree, elem);
    BSTNode *parent = bst_find_parent(tree, elem);
    if (!node)
        return;

    if (node->left == NULL && node->right == NULL)
    {
        if (parent)
        {
            if (parent->left == node)
                parent->left = NULL;
            else
                parent->right = NULL;
        }

        if (tree->root == node)
            tree->root = NULL;

        free(node);
        return;
    }

    if (node->left != NULL && node->right != NULL)
    {
        BSTNode *max = node->left;
        BSTNode *max_prev = node;
        while (max->right)
        {
            max_prev = max;
            max = max->right;
        }

        if (max_prev == node)
            max_prev->left = max->left;
        else
            max_prev->right = max->left;

        node->data = max->data;
        free(max);
        return;
    }

    if (node->left != NULL)
    {
        if (parent)
        {
            if (parent->left == node)
                parent->left = node->left;
            else
                parent->right = node->left;
        }

        if (tree->root == node)
            tree->root = node->left;

        free(node);
        return;
    }

    if (node->right != NULL)
    {
        if (parent)
        {
            if (parent->left == node)
                parent->left = node->right;
            else
                parent->right = node->right;
        }

        if (tree->root == node)
            tree->root = node->right;

        free(node);
        return;
    }
}
