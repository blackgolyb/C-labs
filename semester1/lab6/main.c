#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "task_manager.h"
#include "input.h"

// Розкоментуйте строку, якщо компілюєте програму на Windows
// #define IS_WINDOWS

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

typedef struct
{
    void ***data;
    size_t n;
    size_t m;
} dyn_array_2d;

dyn_array_2d create_2d_array(size_t n, size_t m)
{
    dyn_array_2d array;
    array.data = (void ***)malloc(n * sizeof(void **));
    for (size_t i = 0; i < n; i++)
    {
        array.data[i] = (void **)malloc(m * sizeof(void *));
    }

    array.n = n;
    array.m = m;
    return array;
}

int random_number(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
}

void fill_2d_array_random(dyn_array_2d *arr, int start, int stop)
{
    for (size_t i = 0; i < arr->n; i++)
    {
        for (size_t j = 0; j < arr->m; j++)
        {
            int *value = (int *)malloc(sizeof(int));
            *value = random_number(start, stop);
            arr->data[i][j] = value;
        }
    }
}

void destroy_2d_array(dyn_array_2d *array)
{
    for (size_t i = 0; i < array->n; ++i)
    {
        for (size_t j = 0; j < array->m; ++j)
            free(array->data[i][j]);
        free(array->data[i]);
    }
    free(array->data);
}

void print_2d_array(dyn_array_2d *array)
{
    for (size_t i = 0; i < array->n; i++)
    {
        for (size_t j = 0; j < array->m; j++)
        {
            printf("%d\t", *(int *)array->data[i][j]);
        }
        printf("\n");
    }
}

void print_2d_arrays(dyn_array_2d *array[], int n)
{
    int max_height = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (max_height < array[i]->n)
            max_height = array[i]->n;
    }

    printf("╔═");
    for (size_t k = 0; k < n; k++)
    {
        for (size_t j = 0; j < array[k]->m; j++)
            printf("═════════");

        if (k != n - 1)
            printf("═╦═");
    }
    printf("═╗\n");

    printf("║ ");
    for (size_t k = 0; k < n; k++)
    {
        printf("array %3d", k + 1);
        for (size_t j = 0; j < array[k]->m - 1; j++)
            printf("         ");
        printf(" ║ ");
    }
    printf("\n");

    printf("╠═");
    for (size_t k = 0; k < n; k++)
    {
        for (size_t j = 0; j < array[k]->m; j++)
            printf("═════════");

        if (k != n - 1)
            printf("═╬═");
    }
    printf("═╣\n");

    for (size_t i = 0; i < max_height; i++)
    {
        printf("║ ");
        for (size_t k = 0; k < n; k++)
        {
            if (i >= array[k]->n)
            {
                for (size_t j = 0; j < array[k]->m; j++)
                    printf("         ");
            }
            else
            {
                for (size_t j = 0; j < array[k]->m; j++)
                {
                    printf("%8d ", *(int *)array[k]->data[i][j]);
                }
            }
            printf(" ║ ");
        }

        printf("\n");
    }

    printf("╚═");
    for (size_t k = 0; k < n; k++)
    {
        for (size_t j = 0; j < array[k]->m; j++)
            printf("═════════");

        if (k != n - 1)
            printf("═╩═");
    }
    printf("═╝\n");
}

void fill_2d_array_funny(dyn_array_2d *dest, dyn_array_2d *array1, dyn_array_2d *array2)
{
    for (size_t i = 0; i < dest->n; i++)
    {
        for (size_t j = 0; j < dest->m; j++)
        {
            dest->data[i][j] = (void *)(int *)malloc(sizeof(int));
            if (i == j)
            {
                *(int *)dest->data[i][j] = (*(int *)array1->data[i][j]) & (*(int *)array2->data[i][j]);
            }
            else if ((i + j) % 2 == 0)
            {
                *(int *)dest->data[i][j] = (*(int *)array1->data[i][j]) ^ (*(int *)array2->data[i][j]);
            }
            else
            {
                *(int *)dest->data[i][j] = (*(int *)array1->data[i][j]) | (*(int *)array2->data[i][j]);
            }
        }
    }
}

int count_2d_array_sum_divided(dyn_array_2d *array, int divider)
{
    int sum = 0;
    for (size_t i = 0; i < array->n; i++)
        for (size_t j = 0; j < array->m; j++)
            sum += *(int *)array->data[i][j] % divider == 0 ? *(int *)array->data[i][j] : 0;

    return sum;
}

void S1()
{
    float a, b;
    input(&a);
    input(&b);

    printf("S = %f\n", a * b / 2);
}

void S2()
{
    float m, h;
    input(&m);
    input(&h);

    printf("S = %f\n", m * h);
}

void task2()
{
    struct TaskList task_list = {NULL, 0};
    register_task(&task_list, S1, 1, "Площя прямокутного трикутника");
    register_task(&task_list, S2, 2, "Площа трапеції за довжиною середньої лінії та висотою");

    run_task_manager(&task_list);
}

void task3()
{
    int n = chose_one_option_input("567") - '0';

    dyn_array_2d array1 = create_2d_array(n, n);
    dyn_array_2d array2 = create_2d_array(n, n);
    dyn_array_2d array3 = create_2d_array(n, n);

    fill_2d_array_random(&array1, 0, 255);
    fill_2d_array_random(&array2, 0, 255);
    fill_2d_array_funny(&array3, &array1, &array2);

    dyn_array_2d *printing_arrays[] = {&array1, &array2, &array3};
    print_2d_arrays(printing_arrays, 3);
    printf("\n");

    printf("Сума елементім кратних 3: %d", count_2d_array_sum_divided(&array3, 3));
    printf("\n");

    destroy_2d_array(&array1);
    destroy_2d_array(&array2);
    destroy_2d_array(&array3);
}

int main()
{
    init_code_page();

    struct TaskList task_list = {NULL, 0};
    register_task(&task_list, task2, 2, "Завдання 2");
    register_task(&task_list, task3, 3, "Завдання 3");

    run_task_manager(&task_list);

    return 0;
}
