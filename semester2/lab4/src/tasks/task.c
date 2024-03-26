#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SEP "========================================================"

int random_number(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
}

double random_double(double start, double stop)
{
    int d = 100000;
    long long start_i, stop_i;
    start_i = start * d;
    stop_i = stop * d;
    return ((rand() % (stop_i - start_i + 1)) + start_i) / (double)d;
}

void task2()
{
    int n = 32;
    double *arr = malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
        printf("%d:\t%lf\n", i, arr[i]);

    free(arr);
}

void task3()
{
    int n = 7;
    int a = 25;
    int b = 125;
    int *arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        arr[i] = random_number(a, b);

    for (int i = 0; i < n; i++)
        printf("%d:\t%d\n", i, arr[i]);

    free(arr);
}

void task4()
{
    int n = 5;
    int m = 4;
    double a = 1.29;
    double b = 4.55;

    double **arr = malloc(sizeof(double *) * m);
    for (int i = 0; i < m; i++)
        arr[i] = malloc(sizeof(double) * n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = random_double(a, b);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%lf ", arr[i][j]);
        putchar('\n');
    }

    for (int i = 0; i < m; i++)
        free(arr[i]);
    free(arr);
}

void task5()
{
    int n = 10;

    int **arr = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        arr[i] = malloc((i + 1) * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            arr[i][j] = i ^ j;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
            printf("%2d ", arr[i][j]);
        putchar('\n');
    }

    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}

void task6()
{
    int n = 4;
    int N1 = 1;
    int k = 7;
    int N2 = 54;
    int N3 = 77;

    int *m = malloc(n * sizeof(int));
    int **a = malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
        m[i] = random_number(N1, k);

    for (int i = 0; i < n; i++)
        a[i] = malloc(m[i] * sizeof(int *));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m[i]; j++)
            a[i][j] = random_number(N2, N3);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m[i]; j++)
            printf("%d ", a[i][j]);
        putchar('\n');
    }

    for (int i = 0; i < n; i++)
        free(a[i]);
    free(a);
    free(m);
}

void task7()
{
    int n = 5;
    int m = 5;
    int N2 = 19;
    int N3 = 45;

    int *arr = malloc(sizeof(int) * m * n);

    for (int i = 0; i < m * n; i++)
        arr[i] = random_number(N2, N3);

    printf("Запомнення послідовним способом iє[0; %d)\n", m * n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", arr[i * m + j]);
        putchar('\n');
    }

    printf("\nЗапомнення звичайним способом iє[0; %d) jє[0; %d)\n", m, n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            arr[i * m + j] = random_number(N2, N3);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", arr[i * m + j]);
        putchar('\n');
    }

    free(arr);
}

void task8()
{
    int n = 6;
    int k = 10;

    int *m = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        m[i] = random_number(1, k);

    char **str = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
        str[i] = malloc((m[i] + 1) * sizeof(char));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m[i]; j++)
            str[i][j] = '0' + random_number(0, 9);
        str[i][m[i]] = '\0';
    }

    for (int i = 0; i < n; i++)
        printf("%s\n", str[i]);

    for (int i = 0; i < n; i++)
        free(str[i]);
    free(str);
    free(m);
}

typedef struct DynArray
{
    void **arr;
    int size;
    int capacity;
    int capacity_addition;
    int item_size;
} DynArray;

DynArray * create_dyn_array(int capacity, int capacity_addition, int item_size)
{
    DynArray *array = malloc(sizeof(DynArray));
    array->capacity = capacity;
    array->capacity_addition = capacity_addition;
    array->item_size = item_size;
    array->size = 0;
    array->arr = malloc(array->capacity * array->item_size);

    return array;
}

void append_dyn_array(DynArray *array, void *item)
{
    if ((array->size + 1) > array->capacity)
    {
        array->capacity += array->capacity_addition;
        array->arr = realloc(array->arr, array->capacity * array->item_size);
    }

    array->arr[array->size] = item;
    array->size++;
}

void free_dyn_array(DynArray *array)
{
    for (int i = 0; i < array->size; i++)
        free(array->arr[i]);
    free(array->arr);
    free(array);
}

void task9()
{
    int n = 2;
    int m = 6;
    char stop_word[] = "вісім";

    DynArray *array = create_dyn_array(m, n, sizeof(char *));

    const int str_size = 200;
    char *buffer;
    do
    {
        buffer = malloc(str_size * sizeof(char));
        printf("Введіть слово: ");
        scanf("%s", buffer);

        append_dyn_array(array, buffer);

    } while (strcmp(stop_word, buffer));

    putchar('\n');

    for (int i = 0; i < array->size; i++)
    {
        printf("%s\n", (char *)(array->arr[i]));
    }

    free_dyn_array(array);
}