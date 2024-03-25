#include <stdio.h>
#include <stdlib.h>

int random_number(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
}

void fun_malloc()
{
    int m = 4;
    int n = 6;
    int d1 = 20;
    int d2 = 43;
    int r = 1;

    int **arr = malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++)
        arr[i] = malloc(sizeof(int) * n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = random_number(d1, d2);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);
        putchar('\n');
    }
    putchar('\n');

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[r][i];

    printf("Сумма в r-му рядку (r = %d): %d\n", r, sum);

    for (int i = 0; i < m; i++)
        free(arr[i]);
    free(arr);
}
