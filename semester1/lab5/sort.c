#include "sort.h"

int random_number(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
}

int swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

dyn_array create_array(int len)
{
    return (dyn_array){malloc(sizeof(int) * len), len};
}

void resize_array(dyn_array *arr, int len)
{
    arr->arr = realloc(arr->arr, sizeof(int) * len);
    arr->len = len;
}

void destroy_array(dyn_array *arr)
{
    free(arr->arr);
}

void fill_array_random(dyn_array arr, int start, int stop)
{
    for (int i = 0; i < arr.len; i++)
    {
        arr.arr[i] = random_number(start, stop);
    }
}

bool is_array_include(dyn_array *arr, int elem)
{
    for (int i = 0; i < arr->len; i++)
    {
        if (arr->arr[i] == elem)
            return true;
    }

    return false;
}

void print_array(dyn_array arr)
{
    printf("[");
    for (int i = 0; i < arr.len; i++)
    {
        if (i == arr.len - 1)
        {
            printf("%d", arr.arr[i]);
            continue;
        }

        printf("%d, ", arr.arr[i]);
    }
    printf("]");
}

typedef void (*log_iteration_type)(dyn_array, dyn_array);
typedef bool (*compare_function_type)(int, int);

void bubble_sort(dyn_array arr, compare_function_type compare_function, log_iteration_type log_iteration)
{
    dyn_array iter_args = create_array(4);

    bool swapped, need_to_swap;
    for (int i = 0; i < arr.len - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < arr.len - i - 1; j++)
        {
            need_to_swap = compare_function(arr.arr[j], arr.arr[j + 1]);
            iter_args.arr[0] = j;
            iter_args.arr[1] = j + 1;
            iter_args.arr[2] = need_to_swap;
            iter_args.arr[3] = i;
            log_iteration(arr, iter_args);

            if (need_to_swap)
            {
                swap(&arr.arr[j], &arr.arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }

    destroy_array(&iter_args);
}

void selection_sort(dyn_array arr, compare_function_type compare_function, log_iteration_type log_iteration)
{
    dyn_array iter_args = create_array(4);

    bool swapped, need_to_swap;
    int temp;
    for (int i = 0; i < arr.len - 1; i++)
    {
        temp = i;
        swapped = false;
        for (int j = i + 1; j < arr.len; j++)
        {
            need_to_swap = compare_function(arr.arr[j], arr.arr[temp]);
            iter_args.arr[0] = i;
            iter_args.arr[1] = j;
            iter_args.arr[2] = need_to_swap;
            iter_args.arr[3] = false;
            log_iteration(arr, iter_args);

            if (need_to_swap)
            {
                temp = j;
                swapped = true;
            }
        }
        iter_args.arr[0] = i;
        iter_args.arr[1] = temp;
        iter_args.arr[2] = swapped;
        iter_args.arr[3] = true;
        log_iteration(arr, iter_args);
        if (swapped == true)
        {
            swap(&arr.arr[i], &arr.arr[temp]);
        }
    }

    destroy_array(&iter_args);
}

void insertion_sort(dyn_array arr, compare_function_type compare_function, log_iteration_type log_iteration)
{
    dyn_array iter_args = create_array(3);

    int key;
    for (int i = 0; i < arr.len; i++)
    {
        int j;
        key = arr.arr[i];
        for (j = i - 1; j >= 0 && compare_function(arr.arr[j], key); j--)
        {
            arr.arr[j + 1] = arr.arr[j];
        }
        arr.arr[j + 1] = key;

        iter_args.arr[0] = i;
        iter_args.arr[1] = j + 1;
        iter_args.arr[2] = true;
        log_iteration(arr, iter_args);
    }

    destroy_array(&iter_args);
}

void _void_log_iteration(dyn_array arr, dyn_array iter_args)
{
}

void log_bubble_sort_iteration(dyn_array arr, dyn_array iter_args)
{
    bool is_swapped = iter_args.arr[2];
    int already_sorted = arr.len - iter_args.arr[3] - 1;
    char *color_start = "";
    char *color_end = "";

    for (int i = 0; i < arr.len; i++)
    {
        if ((i == iter_args.arr[0] || i == iter_args.arr[1]) && is_swapped)
        {
            color_start = "\033[01m\033[032m";
            color_end = "\033[0m";
        }
        else if ((i == iter_args.arr[0] || i == iter_args.arr[1]) && !is_swapped)
        {
            color_start = "\033[01m\033[031m";
            color_end = "\033[0m";
        }
        else if (i > already_sorted)
        {
            color_start = "\033[01m\033[034m";
            color_end = "\033[0m";
        }
        else
        {
            color_start = "";
            color_end = "";
        }

        if (i == arr.len - 1)
        {
            printf("%s%4d%s", color_start, arr.arr[i], color_end);
            continue;
        }

        printf("%s%4d%s ", color_start, arr.arr[i], color_end);
    }
    printf(" ------ i = %d;  j = %d\n", iter_args.arr[3], iter_args.arr[0]);
}

void log_selection_sort_iteration(dyn_array arr, dyn_array iter_args)
{
    bool is_swapped = iter_args.arr[2];
    bool is_inplace = iter_args.arr[3];
    int already_sorted = iter_args.arr[0];
    char *color_start = "";
    char *color_end = "";

    for (int i = 0; i < arr.len; i++)
    {
        if (i == iter_args.arr[1] && i == iter_args.arr[0])
        {
            color_start = "\033[01m\033[032m";
            color_end = "\033[0m";
        }
        else if (i == iter_args.arr[0])
        {
            color_start = "\033[01m\033[033m";
            color_end = "\033[0m";
        }
        else if (i < already_sorted)
        {
            color_start = "\033[01m\033[034m";
            color_end = "\033[0m";
        }
        else if (i == iter_args.arr[1])
        {
            if (is_inplace)
            {
                color_start = "\033[01m\033[032m";
            }
            else if (is_swapped)
            {
                color_start = "\033[01m\033[035m";
            }
            else
            {
                color_start = "\033[01m\033[031m";
            }
            color_end = "\033[0m";
        }
        else
        {
            color_start = "";
            color_end = "";
        }

        if (i == arr.len - 1)
        {
            printf("%s%4d%s", color_start, arr.arr[i], color_end);
            continue;
        }

        printf("%s%4d%s ", color_start, arr.arr[i], color_end);
    }
    printf("\n");
}

void log_insertion_sort_iteration(dyn_array arr, dyn_array iter_args)
{
    char *color_start = "";
    char *color_end = "";

    for (int i = 0; i < arr.len; i++)
    {
        if (i == iter_args.arr[1] && i == iter_args.arr[0])
        {
            color_start = "\033[01m\033[032m";
            color_end = "\033[0m";
        }
        else if (i == iter_args.arr[0] + 1)
        {
            color_start = "\033[01m\033[033m";
            color_end = "\033[0m";
        }
        else if (i == iter_args.arr[1])
        {
            color_start = "\033[01m\033[035m";
            color_end = "\033[0m";
        }
        else
        {
            color_start = "";
            color_end = "";
        }

        printf("%s%5d%s", color_start, arr.arr[i], color_end);
    }
    printf("\n");
}

int _sort_array(dyn_array arr, char *algo, char *compare, bool log_iterations, log_iteration_type log_iteration)
{
    log_iteration_type iteration_logger;
    compare_function_type compare_function;

    if (!strcmp(compare, ">"))
    {
        compare_function = lambda(bool, (int a, int b), { return a > b; });
    }
    else if (!strcmp(compare, ">="))
    {
        compare_function = lambda(bool, (int a, int b), { return a >= b; });
    }
    else if (!strcmp(compare, "<"))
    {
        compare_function = lambda(bool, (int a, int b), { return a < b; });
    }
    else if (!strcmp(compare, "<="))
    {
        compare_function = lambda(bool, (int a, int b), { return a <= b; });
    }
    else
    {
        printf("wtf");
        printf("%d", compare == "<=");
        printf(" %d, %d ", &compare, &"<=");
        return -1;
    }

    if (!strcmp(algo, "bubble"))
    {
        iteration_logger = (log_iteration == _void_log_iteration) ? log_bubble_sort_iteration : log_iteration;
        iteration_logger = log_iterations ? iteration_logger : _void_log_iteration;
        bubble_sort(arr, compare_function, iteration_logger);
    }
    if (!strcmp(algo, "selection"))
    {
        iteration_logger = (log_iteration == _void_log_iteration) ? log_selection_sort_iteration : log_iteration;
        iteration_logger = log_iterations ? iteration_logger : _void_log_iteration;
        selection_sort(arr, compare_function, iteration_logger);
    }
    if (!strcmp(algo, "insertion"))
    {
        iteration_logger = (log_iteration == _void_log_iteration) ? log_insertion_sort_iteration : log_iteration;
        iteration_logger = log_iterations ? iteration_logger : _void_log_iteration;
        insertion_sort(arr, compare_function, iteration_logger);
    }
    else
    {
        return -1;
    }

    return 0;
}
