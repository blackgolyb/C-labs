#include "bst_utils.h"

HighlightPair highlight_pair(void *data, int color)
{
    HighlightPair pair;
    pair.data = data;
    pair.color = color;
    return pair;
}

void __bst__printf_void_pointer(void *ptr, char *type)
{
    if (ptr == NULL)
        printf("NULL\n");
    else
    {
        if (!strcasecmp(type, "int"))
            printf("%d", *(int *)ptr);
        else if (!strcasecmp(type, "char"))
            printf("%c", *(char *)ptr);
        else if (!strcasecmp(type, "float"))
            printf("%f", *(float *)ptr);
        else if (!strcasecmp(type, "double"))
            printf("%lf", *(double *)ptr);
        else if (!strcasecmp(type, "string") || !strcasecmp(type, "str"))
            printf("%s", *(char *)ptr);
        else if (!strcasecmp(type, "pointer") || !strcasecmp(type, "ptr"))
            printf("%p", ptr);
        else if (!strcasecmp(type, "bool"))
            printf("%s", *(bool *)ptr ? "true" : "false");
    }
}

void __bst__print_prefixes(int *prefixes, int level)
{
    for (int i = 0; i < level; i++)
    {
        printf("%s", !prefixes[i] ? "   " : "│  ");
    }
}

void __bst__print_body(BST *tree, BSTNode *node, BSTNode *parent, char *type, int *prefixes, int level, bool info, HighlightPair *elems, int en)
{
    if (!node)
        return;

    __bst__print_prefixes(prefixes, level - 1);
    bool is_right = 0;// is root node right in his parent
    if (parent && parent->right == node)
        is_right = 1;

    if (level > 0)
    {
        if (is_right) 
            printf("%s──", parent->left? "├" : "└");
        else
            printf("└──");
    }

    bool highlight = false;
    int color = 31;
    for (int i = 0; i < en; i++)
    {
        if (tree->cmp(node->data, elems[i].data) == 0)
        {
            highlight = true;
            color = elems[i].color;
            break;
        }
    }
    if (highlight)
        printf("\033[%dm", color);
    __bst__printf_void_pointer(node->data, type);
    if (highlight)
        printf("\033[0m");

    if (info)
    {
        if (parent != NULL)
            printf(" \033[36m%s lvl: %d\033[0m", is_right? "(r)" : "(l)", level);
        else
            printf(" \033[36mroot lvl: 0\033[0m");
    }
    putchar('\n');

    prefixes[level] = !!node->left;
    __bst__print_body(tree, node->right, node, type, prefixes, level + 1, info, elems, en);

    prefixes[level] = 0;
    __bst__print_body(tree, node->left, node, type, prefixes, level + 1, info, elems, en);
}

void bst_print(BST *tree, char *type, bool info)
{
    if (tree == NULL || tree->root == NULL)
        return;

    int n = bst_len(tree);
    int *prefixes = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        prefixes[i] = 0;

    __bst__print_body(tree, tree->root, NULL, type, prefixes, 0, info, NULL, 0);
    free(prefixes);
}

void bst_print_with_highlights(BST *tree, char *type, bool info, HighlightPair *elems, int en)
{
    if (tree == NULL || tree->root == NULL)
        return;

    int n = bst_len(tree);
    int *prefixes = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        prefixes[i] = 0;

    __bst__print_body(tree, tree->root, NULL, type, prefixes, 0, info, elems, en);
    free(prefixes);
}
