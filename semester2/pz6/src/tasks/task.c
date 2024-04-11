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

    puts("Заповнює дек випадковими цілими числами в діапазоні від a до b");
    puts("Випадкові числа: ");
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
    puts("Вміст деки: ");
    print_deque(deque);
    putchar('\n');

    puts("Витягає з голови деку n чисел і виводить на екран вміст деку");
    for (int i = 0; i < n; i++)
        adeque_pop_front(deque);
    print_deque(deque);
    putchar('\n');

    puts("Витягає з хвоста деку m чисел і виводить на екран вміст деку");
    for (int i = 0; i < m; i++)
        adeque_pop_back(deque);
    print_deque(deque);
    putchar('\n');

    ADeque *tmp;
    tmp = adeque_create(0);
    adeque_copy(tmp, deque);
    int sum = 0;
    while (!adeque_is_empty(tmp))
    {
        int *num = (int *)adeque_pop_front(tmp);
        if (*num % 2 == 0)
            sum++;
    }
    adeque_destroy(tmp);
    printf("Кількість парних чисел, які на даний момент знаходяться в деку: %d\n", sum);
    putchar('\n');

    puts("Додає до голови деку n1 випадкових чисел і виводить вміст деку на екран");
    for (int i = 0; i < n1; i++)
    {
        int *num = malloc(sizeof(int));
        *num = random_number(a, b);
        adeque_push_front(deque, num);
    }
    print_deque(deque);
    putchar('\n');

    puts("Додає до хвоста деку m1 випадкових чисел і виводить вміст деку на екран");
    for (int i = 0; i < m1; i++)
    {
        int *num = malloc(sizeof(int));
        *num = random_number(a, b);
        adeque_push_back(deque, num);
    }
    print_deque(deque);
    putchar('\n');

    puts("Виводить на екран голову та хвіст деку, а також всі елементи деку у зворотному порядку");
    printf("Голова: %d\n", *(int *)adeque_head(deque));
    printf("Хвіст: %d\n", *(int *)adeque_tail(deque));
    print_deque_reversed(deque);
    putchar('\n');

    puts("Додати N1 випадкових елементів почергово до голови і хвоста деку");
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
    putchar('\n');

    puts("Зменшити розмір деку до s елементів і вивести його вміст на екран");
    adeque_change_capacity(deque, s);
    print_deque(deque);
    putchar('\n');

    adeque_destroy_with_elems(deque);
}