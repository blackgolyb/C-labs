#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ldeque.h"
#include "utils.h"
#include "input.h"

void print_deque(LDeque *deque)
{
    LDeque *tmp = ldeque_create();
    ldeque_copy(tmp, deque);
    while (!ldeque_is_empty(tmp))
    {
        printf("%d ", *(int *)ldeque_pop_front(tmp));
    }
    putchar('\n');
    ldeque_destroy(tmp);
}

int int_cmp(void *a, void *b)
{
    if (*(int *)a == *(int *)b)
        return 0;

    return *(int *)a > *(int *)b ? 1 : -1;
}

void print_deque_reverse(LDeque *deque)
{
    LDeque *tmp = ldeque_create();
    ldeque_copy(tmp, deque);
    while (!ldeque_is_empty(tmp))
    {
        printf("%d ", *(int *)ldeque_pop_back(tmp));
    }
    putchar('\n');
    ldeque_destroy(tmp);
}

void task1()
{
    int k = 18;
    int a = 32;
    int b = 75;
    int n = 5;
    int m = 3;
    int n1 = 4;
    int m1 = 4;

    LDeque *deque = ldeque_create();

    puts("Заповнює дек випадковими цілими числами в діапазоні від a до b");
    puts("Випадкові числа: ");
    for (int i = 0; i < k; i++)
    {
        int *num = malloc(sizeof(int));
        *num = random_number(a, b);
        printf("%d ", *num);
        if (*num % 2 == 0)
            ldeque_push_front(deque, num);
        else
            ldeque_push_back(deque, num);
    }
    putchar('\n');
    puts("Вміст деки: ");
    print_deque(deque);
    putchar('\n');

    puts("Витягає з голови деку n чисел і виводить на екран вміст деку");
    for (int i = 0; i < n; i++)
        ldeque_pop_front(deque);
    print_deque(deque);
    putchar('\n');

    puts("Витягає з хвоста деку m чисел і виводить на екран вміст деку");
    for (int i = 0; i < m; i++)
        ldeque_pop_back(deque);
    print_deque(deque);
    putchar('\n');

    LDeque *tmp = ldeque_create();
    ldeque_copy(tmp, deque);
    int sum = 0;
    while (!ldeque_is_empty(tmp))
    {
        sum += *(int *)ldeque_pop_front(tmp);
    }
    ldeque_destroy(tmp);
    printf("Виводить на екран суму чисел, які на даний момент знаходяться в деку: %d\n", sum);
    putchar('\n');

    puts("Додає до голови деку n1 випадкових чисел і виводить вміст деку на екран");
    for (int i = 0; i < n1; i++)
    {
        int *num = malloc(sizeof(int));
        *num = random_number(a, b);
        ldeque_push_front(deque, num);
    }
    print_deque(deque);
    putchar('\n');

    puts("Додає до хвоста деку m1 випадкових чисел і виводить вміст деку на екран");
    for (int i = 0; i < m1; i++)
    {
        int *num = malloc(sizeof(int));
        *num = random_number(a, b);
        ldeque_push_back(deque, num);
    }
    print_deque(deque);
    putchar('\n');

    puts("Виводить на екран голову та хвіст деку, а також всі елементи деку у зворотному порядку");
    printf("Голова: %d\n", *(int *)deque->head->data);
    printf("Хвіст: %d\n", *(int *)deque->tail->data);
    print_deque_reverse(deque);
    putchar('\n');

    int n2, m2;
    for (int i = 0; i < 2; i++)
    {
        puts("Міняє місцями елементи n2 і m2");
        print_deque(deque);
        input(&n2, "n2: ");
        input(&m2, "m2: ");
        ldeque_swap(deque, &n2, &m2, int_cmp);
        print_deque(deque);
        putchar('\n');
    }

    ldeque_destroy_with_elems(deque);
}