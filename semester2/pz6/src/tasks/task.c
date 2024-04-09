#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "array_deque.h"
#include "utils.h"

void print_deque(ADeque *deque)
{
    ADeque *tmp = adeque_create(0);
    adeque_copy(tmp, deque);
    while (!adeque_is_empty(tmp))
        printf("%d ", *(int *)adeque_pop_front(tmp));
    putchar('\n');
}

void print_deque_reversed(ADeque *deque)
{
    ADeque *tmp = adeque_create(0);
    adeque_copy(tmp, deque);
    while (!adeque_is_empty(tmp))
        printf("%d ", *(int *)adeque_pop_back(tmp));
    putchar('\n');
}

void task1()
{
    int N = 10;
    int a = 43;
    int b = 65;
    int n = 2;
    int m = 4;
    int n1 = 3;
    int m1 = 3;
    int N1 = 8;
    int s = 9;

    ADeque *deque = adeque_create(N);
    for (int i = 0; i < N; i++)
    {
        int *num = malloc(sizeof(int));
        *num = random_number(a, b);
        printf("%d ", *num);
        if (*num < (a + b) / 2.0)
            adeque_push_front(deque, num);
        else
            adeque_push_back(deque, num);
    }
    putchar('\n');

    print_deque(deque);

    for (int i = 0; i < n; i++)
        adeque_pop_front(deque);
    print_deque(deque);

    for (int i = 0; i < m; i++)
        adeque_pop_back(deque);
    print_deque(deque);

    ADeque *tmp;
    tmp = adeque_create(0);
    adeque_copy(tmp, deque);
    int sum = 0;
    while (!adeque_is_empty(tmp))
    {
        int *num = (int *)adeque_pop_front(tmp);
        if (*num % 2 == 0)
            sum += *num;
    }
    printf("sum: %d\n", sum);
    adeque_destroy(tmp);

    for (int i = 0; i < n1; i++)
    {
        int *num = malloc(sizeof(int));
        *num = random_number(a, b);
        adeque_push_front(deque, num);
    }
    print_deque(deque);

    for (int i = 0; i < m1; i++)
    {
        int *num = malloc(sizeof(int));
        *num = random_number(a, b);
        adeque_push_back(deque, num);
    }
    print_deque(deque);

    printf("head: %d\n", *(int *)adeque_head(deque));
    printf("tail: %d\n", *(int *)adeque_tail(deque));
    print_deque_reversed(deque);

    adeque_change_capacity(deque, deque->capacity + N1);
    print_deque(deque);
    for (int i = 0; i < N1; i++)
    {
        int *num = malloc(sizeof(int));
        *num = random_number(a, b);
        if (i % 2 == 0)
            adeque_push_front(deque, num);
        else
            adeque_push_back(deque, num);
        print_deque(deque);
    }

    adeque_change_capacity(deque, s);
    print_deque(deque);

    adeque_destroy_with_elems(deque);
}