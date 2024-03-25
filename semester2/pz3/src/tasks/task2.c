#include <stdio.h>
#include <stdlib.h>

float random_float(float start, float stop)
{
    int d = 100000;
    long long start_i, stop_i;
    start_i = start * d;
    stop_i = stop * d;
    return ((rand() % (stop_i - start_i + 1)) + start_i) / (float)d;
}

void fun_calloc()
{
    int s = 8;
    float t1 = 21.00;
    float t2 = 23.00;
    float p = 22.00;

    float *arr = calloc(s, sizeof(float));
    for (int i = 0; i < s; i++)
        arr[i] = random_float(t1, t2);

    for (int i = 0; i < s; i++)
        printf("%f ", arr[i]);
    putchar('\n');

    float sum = 0.0;
    for (int i = 0; i < s; i++)
        if (arr[i] >= p)
            sum += arr[i];

    printf("Сумма елементів які >= p (p = %f): %f\n", p, sum);

    free(arr);
}
