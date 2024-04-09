#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "linked_list.h"
#include "linked_list_sort.h"
#include "linked_list_utils.h"
#include "utils.h"

#define SEED 1234

int int_cmp(void *a, void *b)
{
    if (*(int *)a == *(int *)b)
        return 0;

    return *(int *)a > *(int *)b ? 1 : -1;
}

void task1()
{
    int k = 17;
    int a = 27;
    int b = 48;
    bool ascending = true;

    List *l = ll_create();
    srand(SEED);

    ll_fill_int_random(l, k, a, b);
    ll_print(l, "int", " ", "\n");

    ll_bubble_sort(l, int_cmp, ascending);
    ll_print(l, "int", " ", "\n");
    ll_destroy(l);
}

void task2()
{
    int k = 20;
    int a = 21;
    int b = 69;
    bool ascending = false;

    List *l = ll_create();
    srand(SEED);

    ll_fill_int_random(l, k, a, b);
    ll_print(l, "int", " ", "\n");

    ll_quick_sort(l, int_cmp, ascending);
    ll_print(l, "int", " ", "\n");
    ll_destroy(l);
}

void task3()
{
    int k = 21;
    int a = 32;
    int b = 57;
    bool ascending = true;

    List *l = ll_create();
    srand(SEED);

    ll_fill_int_random(l, k, a, b);
    ll_print(l, "int", " ", "\n");

    ll_marge_sort(l, int_cmp, ascending);
    ll_print(l, "int", " ", "\n");
    ll_destroy(l);
}

void task4()
{
    int n = 30000;
    int a = 29;
    int b = 4349;
    bool ascending = false;
    clock_t t;
    double t1, t2, t3;

    List *l = ll_create();

    srand(SEED);
    ll_fill_int_random(l, n, a, b);
    // ll_print(l, "int", " ", "\n");
    t = clock();
    ll_bubble_sort(l, int_cmp, ascending);
    t = clock() - t;
    t1 = ((double)t) / CLOCKS_PER_SEC;
    // ll_print(l, "int", " ", "\n");
    printf("bubble_sort: %lf seconds\n", t1);

    srand(SEED);
    ll_fill_int_random(l, n, a, b);
    // ll_print(l, "int", " ", "\n");
    t = clock();
    ll_quick_sort(l, int_cmp, ascending);
    t = clock() - t;
    t2 = ((double)t) / CLOCKS_PER_SEC;
    // ll_print(l, "int", " ", "\n");
    printf("quick_sort: %lf seconds\n", t2);

    srand(SEED);
    ll_fill_int_random(l, n, a, b);
    // ll_print(l, "int", " ", "\n");
    t = clock();
    ll_marge_sort(l, int_cmp, ascending);
    t = clock() - t;
    t3 = ((double)t) / CLOCKS_PER_SEC;
    // ll_print(l, "int", " ", "\n");
    printf("marge_sort: %lf seconds\n", t3);
    ll_destroy(l);
}

void task5()
{

    int a = 29;
    int b = 4349;
    bool ascending = false;
    clock_t t;

    List *l = ll_create();

    const int nf = 3;
    void (*fs[])(List *, CmpFun, bool) = {ll_bubble_sort, ll_quick_sort, ll_marge_sort};

    int k = 28;
    float delta = 1.5;
    int n_start = 2;
    int n = n_start;
    double **times = malloc(sizeof(double *) * nf);
    for (int i = 0; i < nf; i++)
        times[i] = malloc(sizeof(double) * k);

    for (int i = 0; i < k; i++)
    {
        printf("n %d\n", n);
        for (int fi = 0; fi < nf; fi++)
        {
            srand(SEED);
            ll_fill_int_random(l, n, a, b);
            t = clock();
            fs[fi](l, int_cmp, ascending);
            t = clock() - t;
            times[fi][i] = ((double)t) / CLOCKS_PER_SEC;
            printf("sort %d: %lf seconds\n", fi, times[fi][i]);
        }
        n *= delta;
    }

    FILE *f = fopen("sort.csv", "w");
    n = n_start;
    for (int i = 0; i < k-1; i++)
    {
        fprintf(f, "%d; ", n);
        n *= delta;
    }
    fprintf(f, "%d", n);
    fprintf(f, "\n");
    for (int fi = 0; fi < nf; fi++)
    {
        for (int i = 0; i < k-1; i++)
            fprintf(f, "%lf; ", times[fi][i]);
        fprintf(f, "%lf", times[fi][k-1]);
        fprintf(f, "\n");
    }
    fclose(f);
    ll_destroy(l);
}