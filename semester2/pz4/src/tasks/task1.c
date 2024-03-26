#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include "linked_list.h"
#include "utils.h"

#define SEP "================================================="


void ll_int_print(List *list)
{
    for (int i = 0; i < ll_len(list); i++) {
        printf("%d ", *(int *)ll_get(list, i));
    }
    putchar('\n');
}

void ll_int_add_random(List *list, int n, int start, int end)
{
    for (int i = 0; i < n; i++)
    {
        int *n = malloc(sizeof(int));
        *n = random_number(start, end);
        ll_push_back(list, n);
    }
}

void task1()
{
    int k = 7;
    int a = 16;
    int b = 43;
    int m = 35;
    int n = 2;
    int t = 5;
    int t1 = 45;
    int t2 = 88;
    int s = 7;

    puts(SEP);
    puts("Зв'язний список");
    puts(SEP);
    List *list = ll_create(sizeof(int));
    ll_int_add_random(list, k, a, b);
    ll_int_print(list);
    printf("%s\n\n", SEP);
    
    puts(SEP);
    printf("Додаємо елемент %d до списку після %d-го\n", m, n);
    puts(SEP);
    ll_insert(list, n, &m);
    ll_int_print(list);
    printf("%s\n\n", SEP);

    puts(SEP);
    puts("Додаємо в кінець списку випадкові елементи");
    puts(SEP);
    ll_int_add_random(list, t, t1, t2);
    ll_int_print(list);
    printf("%s\n\n", SEP);

    puts(SEP);
    puts("Зв'язний список після видалення голови та хвоста");
    puts(SEP);
    int *tail = (int *)ll_pop(list, -1);
    int *head = (int *)ll_pop(list, 0);
    printf("Голова: %d\n", *head);
    printf("Хвіст: %d\n", *tail);
    ll_int_print(list);
    printf("%s\n\n", SEP);

    puts(SEP);
    printf("Видаляємо %d елемент\n", s);
    puts(SEP);
    int *elem = (int *)ll_pop(list, s);
    printf("Elem (s = %d): %d\n", s, *elem);
    ll_int_print(list);
    printf("%s\n\n", SEP);
    
    ll_destroy(list);
}
