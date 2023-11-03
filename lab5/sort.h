#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define lambda(lambda$_ret, lambda$_args, lambda$_body) \
    ({                                                  \
        lambda$_ret lambda$__anon$ lambda$_args         \
            lambda$_body                                \
                &lambda$__anon$;                        \
    })

int random_number(int start, int stop);
int swap(int *a, int *b);

typedef struct
{
    int *arr;
    int len;
} dyn_array;

dyn_array create_array(int len);
void resize_array(dyn_array *arr, int len);
void destroy_array(dyn_array *arr);
void fill_array_random(dyn_array arr, int start, int stop);
void print_array(dyn_array arr);

typedef void (*log_iteration_type)(dyn_array, dyn_array);
typedef bool (*compare_function_type)(int, int);

void bubble_sort(dyn_array arr, compare_function_type compare_function, log_iteration_type log_iteration);
void selection_sort(dyn_array arr, compare_function_type compare_function, log_iteration_type log_iteration);
void insertion_sort(dyn_array arr, compare_function_type compare_function, log_iteration_type log_iteration);

void _void_log_iteration(dyn_array arr, dyn_array iter_args);
void log_bubble_sort_iteration(dyn_array arr, dyn_array iter_args);
void log_selection_sort_iteration(dyn_array arr, dyn_array iter_args);
void log_insertion_sort_iteration(dyn_array arr, dyn_array iter_args);

int _sort_array(dyn_array arr, char *algo, char *compare, bool log_iterations, log_iteration_type log_iteration);

#define sort_array3(arr, algo, compare) _sort_array(arr, algo, compare, false, _void_log_iteration)
#define sort_array4(arr, algo, compare, log_iterations) _sort_array(arr, algo, compare, log_iterations, _void_log_iteration)
#define sort_array5(arr, algo, compare, log_iterations, log_func) _sort_array(arr, algo, compare, log_iterations, log_func)

#define NARGS(...) NARGS_(__VA_ARGS__, 5, 4, 3, 2, 1, 0)
#define NARGS_(_5, _4, _3, _2, _1, N, ...) N

#define CONC(A, B) CONC_(A, B)
#define CONC_(A, B) A##B

/**
 * Macro to easy use _sort_array function.
 *
 * @param arr the array that will be sorted.
 * @param algo the name of the algorithm that will be used to sort. One of ("bubble", "selection", "insertion")
 * @param compare the operand by which the elements will be compared. One of (">", ">=", "<", "<=")
 * @param log_iterations whether it is necessary to log iterations. One of (true, false)
 * @param log_iteration the function that will be called to log iterations. It must take two arguments: dyn_array and dyn_array.
 * @return nothing (void)
 *
 * @note
 * Here you can see available uses of this macro:
 * @code{c}
 * sort_array(dyn_array arr, char *algo, char *compare)
 * sort_array(dyn_array arr, char *algo, char *compare, bool log_iterations)
 * sort_array(dyn_array arr, char *algo, char *compare, bool log_iterations, log_iteration_type log_iteration)
 * @endcode
 */
#define sort_array(...) CONC(sort_array, NARGS(__VA_ARGS__))(__VA_ARGS__)

#endif // SORT_H_INCLUDED
