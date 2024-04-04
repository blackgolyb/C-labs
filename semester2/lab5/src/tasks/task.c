#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "linked_list.h"
#include "linked_list_sort.h"
#include "linked_list_utils.h"
#include "utils.h"

bool task1_cmp(void *a, void *b)
{
    // printf("a = %d b = %d\n", *(int *)a, *(int *)b);
    return *(int *)a < *(int *)b;
}

void task1()
{
    // 17 27 48 up
    int k = 19;
    int a = 27;
    int b = 48;

    List *l = ll_create();

    ll_fill_int_random(l, k, a, b);
    int t = 32;
    ll_insert(l, 0, &t);
    ll_print(l, "int", " ", "\n");

    ll_bubble_sort(l, task1_cmp);
    ll_print(l, "int", " ", "\n");

    ll_quick_sort(l, task1_cmp);
    ll_print(l, "int", " ", "\n");

}