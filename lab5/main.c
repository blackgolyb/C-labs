#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "task_manager.h"
#include "input.h"
#include "sort.h"

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

void task1()
{
    int len;
    input(&len, "довжини масиву");

    dyn_array arr = create_array(len);

    fill_array_random(arr, -99, 99);

    printf("Початковий масив:\n");
    print_array(arr);
    printf("\n\n");

    printf("Процес сортування:\n");
    sort_array(arr, "bubble", "<=", true);
    printf("\n");

    printf("Масив після сортування:\n");
    print_array(arr);
    printf("\n");

    destroy_array(&arr);
}

void task2()
{
    int len;
    input(&len, "довжини масиву");

    dyn_array arr = create_array(len);

    fill_array_random(arr, 0, 50);

    printf("Початковий масив:\n");
    print_array(arr);
    printf("\n\n");

    printf("Процес сортування:\n");
    sort_array(arr, "selection", "<=", true);
    printf("\n");

    printf("Масив після сортування:\n");
    print_array(arr);
    printf("\n");

    destroy_array(&arr);
}

void task3()
{
    int len = 10;
    dyn_array arr = create_array(len);

    fill_array_random(arr, -100, 100);

    printf("Початковий масив:\n");
    print_array(arr);
    printf("\n\n");

    printf("Процес сортування:\n");
    sort_array(arr, "insertion", ">=", true);
    printf("\n");

    printf("Масив після сортування:\n");
    print_array(arr);
    printf("\n");

    destroy_array(&arr);
}

void task4()
{
    int len;
    input(&len, "половини розміру масиву");

    dyn_array arr = create_array(len * 2 + 1);

    fill_array_random(arr, 20, 90);

    printf("Початковий масив:\n");
    print_array(arr);
    printf("\n\n");

    sort_array(arr, "bubble", ">");

    printf("Масив після сортування:\n");
    print_array(arr);
    printf("\n");

    int median = arr.arr[arr.len / 2];
    printf("Медіана масиву: %d\n", median);

    destroy_array(&arr);
}

void count_unique_elements(dyn_array arr, dyn_array *unique_arr, dyn_array *unique_elements_arr)
{
    int unique_count = 0;
    if (arr.len)
    {
        unique_count = 1;
    }
    for (int i = 1; i < arr.len; i++)
    {
        if (arr.arr[i] != arr.arr[i - 1])
            unique_count++;
    }

    resize_array(unique_arr, unique_count);
    resize_array(unique_elements_arr, unique_count);

    int unique_i = 0;
    if (unique_count)
    {
        unique_arr->arr[0] = arr.arr[0];
        unique_elements_arr->arr[0] = 1;
        unique_i = 1;
    }
    for (int i = 1; i < arr.len; i++)
    {
        if (arr.arr[i] != arr.arr[i - 1])
        {
            unique_arr->arr[unique_i] = arr.arr[i];
            unique_i++;
            unique_elements_arr->arr[unique_i - 1] = 1;
        }
        else
        {
            unique_elements_arr->arr[unique_i - 1] += 1;
        }
    }
}

int found_max(dyn_array arr)
{
    int max_elem = arr.arr[0];
    for (int i = 1; i < arr.len; i++)
    {
        if (arr.arr[i] > max_elem)
        {
            max_elem = arr.arr[i];
        }
    }

    return max_elem;
}

void task5()
{
    int len;
    input(&len, "довжини масиву");

    dyn_array arr = create_array(len);

    fill_array_random(arr, 0, 30);

    printf("Початковий масив:\n");
    print_array(arr);
    printf("\n\n");

    sort_array(arr, "bubble", ">");

    printf("Масив після сортування:\n");
    print_array(arr);
    printf("\n\n");

    dyn_array unique_arr = create_array(0);
    dyn_array unique_elements_arr = create_array(0);
    count_unique_elements(arr, &unique_arr, &unique_elements_arr);

    int unique_count = unique_arr.len;

    int max_appearance = found_max(unique_elements_arr);

    printf("Кількість унікальних елементів: %d\n\n", unique_count);

    printf("Унікальні елементи (m1):\n");
    print_array(unique_arr);
    printf("\n\n");

    printf("Масив кількості повторів елементи (m2):\n");
    print_array(unique_elements_arr);
    printf("\n\n");

    for (int i = 0; i < unique_elements_arr.len; i++)
    {
        if (unique_elements_arr.arr[i] == max_appearance)
        {
            printf("Мода масива:\t%d зустрічається %d разів\n", unique_arr.arr[i], unique_elements_arr.arr[i]);
        }
    }

    destroy_array(&unique_arr);
    destroy_array(&unique_elements_arr);
    destroy_array(&arr);
}

int main()
{
    init_code_page();

    struct TaskList task_list = {NULL, 0};
    register_task(&task_list, task1, 1);
    register_task(&task_list, task2, 2);
    register_task(&task_list, task3, 3);
    register_task(&task_list, task4, 4);
    register_task(&task_list, task5, 5);

    run_task_manager(&task_list);

    return 0;
}
