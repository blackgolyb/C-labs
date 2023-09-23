#include <stdio.h>
#include <stdbool.h>

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
    bool print_iteration = false;

    int sum = 0;
    int start = 1;
    int stop = 30;

    for (int i = start; i <= stop; i++)
    {
        if (i % 2 == 0)
        {
            sum += i;
        }

        if (print_iteration)
        {
            printf("Ітерація №%d\n", i);
            printf("============================\n");
            printf("Значення sum = %d\n\n", sum);
        }
    }

    printf("============================\n");
    printf("Результат: sum = %d\n", sum);
    printf("============================\n");
}

int main()
{
    init_code_page();

    task1();
    return 0;
}
