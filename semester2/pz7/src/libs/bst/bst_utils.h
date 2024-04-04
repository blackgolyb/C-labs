#ifndef BST_UTILS_H_INCLUDED
#define BST_UTILS_H_INCLUDED


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bst.h"

typedef struct HighlightPair
{
    void *data;
    int color;
} HighlightPair;


HighlightPair highlight_pair(void *data, int color);
void bst_print(BST *tree, char *type, bool info);
void bst_print_with_highlights(BST *tree, char *type, bool info, HighlightPair *elems, int en);

#endif // BST_UTILS_H_INCLUDED
