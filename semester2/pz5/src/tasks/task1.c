#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "array_stack.h"
#include "list_stack.h"
#include "queue.h"
#include "utils.h"

void print_astacks(AStack **stacks, int n)
{
    AStack **tmp_stacks = malloc(sizeof(AStack *) * n);
    for (int i = 0; i < n; i++)
    {
        tmp_stacks[i] = astack_create();
        astack_copy(tmp_stacks[i], stacks[i]);
    }

    int max_size = 0;
    for (int i = 0; i < n; i++)
        if (max_size < astack_size(tmp_stacks[i]))
            max_size = astack_size(tmp_stacks[i]);

    int *deltas = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        deltas[i] = max_size - astack_size(tmp_stacks[i]);

    for (int i = 0; i < max_size; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((deltas[j] - i) <= 0)
                printf("    %6d", *(int *)astack_pop(tmp_stacks[j]));
            else
                printf("          ");
        }
        putchar('\n');
    }
    for (int j = 0; j < n+1; j++)
        printf("==========");
    putchar('\n');
    // printf("  ");
    for (int j = 0; j < n; j++)
        printf("    stack%d", j+1);
    putchar('\n');

    for (int i = 0; i < n; i++)
        astack_destroy(tmp_stacks[i]);
    free(deltas);
    free(tmp_stacks);
}

void task1()
{
    int k = 20;
    int a = 37;
    int b = 87;

    AStack *s1 = astack_create();
    AStack *s2 = astack_create();
    AStack *s3 = astack_create();
    for (int i = 0; i < k; i++)
    {
        int *num = (int *)malloc(sizeof(int));
        *num = random_number(a, b);
        if (*num % 2 == 0)
            astack_push(s1, num);
        else
            astack_push(s2, num);
    }

    AStack *stacks[3];
    stacks[0] = s1;
    stacks[1] = s2;
    stacks[2] = s3;
    print_astacks(stacks, 2);

    int min_size = imin(astack_size(s1), astack_size(s2));

    while (astack_size(s1) > min_size)
        free(astack_pop(s1));

    while (astack_size(s2) > min_size)
        free(astack_pop(s2));

    AStack *tmp_s1 = astack_create();
    AStack *tmp_s2 = astack_create();
    AStack *tmp_s3 = astack_create();
    for (int i = 0; i < min_size; i++)
    {
        int *num1 = astack_pop(s1);
        int *num2 = astack_pop(s2);
        int *num = (int *)malloc(sizeof(int));
        *num = (*num1) * (*num2);
        astack_push(tmp_s3, num);
        astack_push(tmp_s1, num1);
        astack_push(tmp_s2, num2);
    }
    astack_repack(s1, tmp_s1);
    astack_repack(s2, tmp_s2);
    astack_repack(s3, tmp_s3);

    putchar('\n');
    print_astacks(stacks, 3);

    astack_destroy_with_elems(s1);
    astack_destroy_with_elems(s2);
}