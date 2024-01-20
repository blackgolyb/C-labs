#include <stdio.h>
#include <stdbool.h>
#include <math.h>

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

void input_value(float *value_ptr, char *value_name)
{
    printf("Введіть значення %s: ", value_name);
    scanf("%f", value_ptr);
}

bool check_functions_domain(float x)
{
    if (x == -2)
    {
        return false;
    }
    else if (x <= -3)
    {
        return false;
    }
    return true;
}

float calculate_function(float x)
{
    return 1 / log(x + 3);
}

void task()
{
    float x;
    input_value(&x, "x");

    if (!check_functions_domain(x))
    {
        printf("x = %f не входить в область припустимих значень функції\n", x);
        return;
    }

    float y = calculate_function(x);
    printf("Значення функці y = %f при x = %f\n", y, x);
}

int main()
{
    init_code_page();
    task();

    return 0;
}
