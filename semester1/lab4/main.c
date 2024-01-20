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

void task1()
{
    int a = 71;
    int b = 10;
    int result;
    char operation;

    operation = chose_one_option_input("&+");

    result = operation == '&' ? a & b : a + b;

    printf("Result of %d %c %d = %d", a, operation, b, result);
}

float calc_f(float a, float b)
{
    if (a > 10)
    {
        return a - b;
    }
    else if (0 < a && a <= 10 && b > 0)
    {
        return (a - b) / (a + b);
    }
    else
    {
        return b;
    }
}

void task2()
{
    float a, b, f;

    input(&a);
    input(&b);

    f = calc_f(a, b);
    printf("f(a, b) = %f", f);
}

void task3()
{
    float a, b, result;
    char operation;

    input(&a);
    input(&b);
    operation = chose_one_option_input("+-*/");

    switch (operation)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        if (b == 0)
        {
            printf("Division by zero error");
            return;
        }
        result = a / b;
        break;
    default:
        break;
    }

    printf("Result of %f %c %f = %f", a, operation, b, result);
}

int main()
{
    init_code_page();

    struct TaskList task_list = {NULL, 0};
    register_task(&task_list, task1, 1);
    register_task(&task_list, task2, 2);
    register_task(&task_list, task3, 3);

    run_task_manager(&task_list);

    return 0;
}
