#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "bst.h"
#include "bst_utils.h"
#include "utils.h"

int int_cmp(void *a, void *b)
{
    if (*(int *)a == *(int *)b)
        return 0;

    return *(int *)a > *(int *)b ? 1 : -1;
}

BST *task1_part1(int *data, int n)
{
    BST *tree = bst_create(int_cmp);

    for (int i = 0; i < n; i++)
        bst_insert(tree, &data[i]);

    printf("Виводимо створене ДДП:\n");
    bst_print(tree, "int", true);
    putchar('\n');
    return tree;
}

void task1_part23(BST *tree)
{
    HighlightPair highlight[2];
    int min = *(int *)bst_min(tree);
    int max = *(int *)bst_max(tree);

    int max_color = 31;
    int min_color = 34;
    highlight[0] = highlight_pair(&min, min_color);
    highlight[1] = highlight_pair(&max, max_color);
    printf(
        "Позначемо \033[%dmмінімальний %d\033[0m та \033[%dmмаксиальний %d\033[0m елемент на графі:\n",
        min_color, min, max_color, max);
    bst_print_with_highlights(tree, "int", false, highlight, 2);
}

void task1_part4(BST *tree, int elem)
{
    HighlightPair highlight[2];
    BSTNode *p = bst_find_parent(tree, &elem);
    if (p != NULL)
    {
        int elem_color = 34;
        int parent_color = 31;
        printf(
            "\nПозначемо \033[%dmбатька %d\033[0m \033[%dmелемента %d\033[0m на графі:\n",
            parent_color, *(int *)p->data, elem_color, elem);
        highlight[0] = highlight_pair(&elem, elem_color);
        highlight[1] = highlight_pair(p->data, parent_color);
        bst_print_with_highlights(tree, "int", false, highlight, 2);
    }
    else
    {
        printf("Батько елемента %d: немає\n", elem);
    }
}

void task1_part56(BST *tree, int *delete_nodes, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nГраф після видалення елемента %d\n", delete_nodes[i]);
        bst_delete(tree, &delete_nodes[i]);
        bst_print(tree, "int", false);
    }
}

void task1()
{
    int data[] = {33, 13, 41, 17, 84, 7, 14, 37, 69, 21, 60, 27, 83, 6, 85};
    int elem = 7;
    int delete[] = {33, 60, 84};

    BST *tree = task1_part1(data, sizeof(data) / sizeof(data[0]));
    task1_part23(tree);
    task1_part4(tree, elem);
    task1_part56(tree, delete, sizeof(delete) / sizeof(delete[0]));

    bst_destroy(tree);
}