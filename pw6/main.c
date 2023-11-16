#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "input.h"

#ifdef IS_WINDOWS
#include <windows.h>
#endif

void init_code_page()
{
    // Перевірка чи компілюється програма на Windows чи ні

#ifdef IS_WINDOWS
    SetConsoleOutputCP(1251);
#endif
}

int random_number(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
}

int **create_array(int n, int m)
{
    int **array = malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++)
    {
        array[i] = malloc(sizeof(int) * m);
    }

    return array;
}

void fill_random(int **array, int n, int m, int start, int stop)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            array[i][j] = random_number(start, stop);
}

void fill_number(int **array, int n, int m, int num)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            array[i][j] = num;
}

void print_array(int **array, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%3d ", array[i][j]);
        printf("\n");
    }
}

void delete_array(int **array, int n, int m)
{
    for (int i = 0; i < n; i++)
        free(array[i]);

    free(array);
}

void task_algo(int **array, int **result, int m)
{
    int min_elem;

    for (int i = 0; i < m - 1; i++)
    {
        min_elem = array[0][m - i - 1];
        for (int j = 0; j <= i; j++)
            if (array[j][m - i + j - 1] < min_elem)
                min_elem = array[j][m - i + j - 1];

        result[0][m - i - 1] = min_elem;
    }

    for (int i = 0; i < m - 1; i++)
    {
        min_elem = array[m - 1][m - i - 2];
        for (int j = 0; j <= m - 2 - i; j++)
            if (array[m - j - 1][m - i - j - 2] < min_elem)
                min_elem = array[m - j - 1][m - i - j - 2];

        result[m - 1][m - i - 2] = min_elem;
    }
}

void task()
{
    int m;
    input(&m, "розмірність матриці m");

    int **array = create_array(m, m);
    int **result = create_array(m, m);

    fill_random(array, m, m, 1, 9);
    fill_number(result, m, m, 0);

    print_array(array, m, m);
    printf("\n");

    task_algo(array, result, m);

    print_array(result, m, m);
    printf("\n");

    delete_array(array, m, m);
    delete_array(result, m, m);
}

int main()
{
    init_code_page();

    task();

    return 0;
}
