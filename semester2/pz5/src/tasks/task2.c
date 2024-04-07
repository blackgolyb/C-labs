#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "list_stack.h"
#include "queue.h"
#include "utils.h"

void print_lstacks(LStack **stacks, int n)
{
    LStack **tmp_stacks = malloc(sizeof(LStack *) * n);
    for (int i = 0; i < n; i++)
    {
        tmp_stacks[i] = lstack_create();
        lstack_copy(tmp_stacks[i], stacks[i]);
    }
    
    int max_size = 0;
    for (int i = 0; i < n; i++)
        if (max_size < lstack_size(tmp_stacks[i]))
            max_size = lstack_size(tmp_stacks[i]);

    int *deltas = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        deltas[i] = max_size - lstack_size(tmp_stacks[i]);

    for (int i = 0; i < max_size; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((deltas[j] - i) <= 0)
                printf("%5d    ", *(int *)lstack_pop(tmp_stacks[j]));
            else
                printf("         ");
        }
        putchar('\n');
    }

    for (int i = 0; i < n; i++)
        lstack_destroy(tmp_stacks[i]);
    free(deltas);
    free(tmp_stacks);
}

void task2()
{
    int m = 19;
    int d = 83;
    int e = 99;
    int n = 91;

    LStack *s1 = lstack_create();
    LStack *s2 = lstack_create();
    Queue *q = queue_create();

    for (int i = 0; i < m; i++)
    {
        int *num = (int *)malloc(sizeof(int));
        *num = random_number(d, e);
        queue_insert(q, num);
    }

    Queue *tmp = queue_create();
    queue_copy(tmp, q);
    while (!queue_is_empty(tmp))
        printf("%d ", *(int *)queue_remove(tmp));
    putchar('\n');

    while (!queue_is_empty(q))
    {
        int *num = queue_remove(q);
        if (*num < n)
            lstack_push(s1, num);
        else
            lstack_push(s2, num);
    }

    LStack *stacks[2];
    stacks[0] = s1;
    stacks[1] = s2;

    putchar('\n');
    print_lstacks(stacks, 2);

    lstack_destroy_with_elems(s1);
    lstack_destroy_with_elems(s2);
}