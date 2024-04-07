#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "linked_list.h"
#include "linked_list_sort.h"
#include "linked_list_utils.h"
#include "utils.h"

int int_cmp(void *a, void *b)
{
    if (*(int *)a == *(int *)b)
        return 0;

    return *(int *)a > *(int *)b ? 1 : -1;
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

    ll_bubble_sort(l, int_cmp, true);
    ll_print(l, "int", " ", "\n");

    ll_quick_sort(l, int_cmp, false);
    ll_print(l, "int", " ", "\n");

}