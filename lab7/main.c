#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "task_manager.h"
// #include "input.h"

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

void task2()
{
    unsigned long L = 11116271;
    char *cp = (char *)&L;
    int *ip = (int *)&L;
    long *lp = (long *)&L;

    printf("Значення адреси комірки пам\'яті, "
           "в якій знаходиться змінна L\n");
    printf("&L = %10p\n\n", &L);
    printf("Значення змінної L\n");
    printf("L = %10ld\n\n", L);
    printf("Значення змінної, на яку вказує "
           "вказівник cp типу char\n");
    printf("*cp = %10c\n\n", *cp);
    printf("*cp = %10d\n\n", *cp);
    printf("Значення змінної, на яку вказує "
           "вказівник ip типу int\n");
    printf("*ip = %10d\n\n", *ip);
    printf("Значення змінної, на яку вказує "
           "вказівник lp типу long\n");
    printf("*lp = %10ld\n\n", *lp);
}

void task3()
{
    double a = 3.1415;
    double *p = &a;
    void *pp = &a;

    printf("Адреса змінної a: %p\n", &a);
    printf("Значення a: %f\n\n", a);

    // Виведення адреси та значення вказівників
    printf("Адреса вказівника p: %p\n", &p);
    printf("Значення вказівника p (адреса, на яку вказує): %p\n", p);
    printf("Значення, яке отримане після розіменування p: %f\n\n", *p);

    printf("Адреса вказівника pp: %p\n", &pp);
    // При використанні вказівника на тип void потрібно явно привести тип для розіменування
    printf("Значення вказівника pp (адреса, на яку вказує): %p\n", pp);
    printf("Значення, яке отримане після розіменування pp: %f\n\n", *((double *)pp));

    // Для демонстрації ролі та послідовності виконання унарних операцій
    printf("Значення виразу \"* &a\": %f\n", *(&a));
}

void task4()
{
    int a, c, b;
    int *ca, *cb;
    int *sa, *sb, *sc;

    a = 3;
    b = 6;
    c = a + b;

    printf("c = a + b = %2d\n", c);
    // ініціалізація вказівників через взяття адреси
    sa = &a;
    sb = &b;
    sc = &c;
    // присвоювання вказівнику значення виразу
    *sc = c + a - b;
    // присвоювання вказівнику значення іншого вказівника
    ca = sa;
    cb = sb;
    // присвоювання вказівнику значення константи
    *sa = 12;
    printf("\n*ca = %2d\n", *ca);
    printf("*sa = %2d\n", *sa);
    printf("*cb = %2d\n", *cb);
    printf("*sb = %2d\n", *sb);
    printf("*sc = %2d\n\n", *sc);
    printf("ca = %p\n", ca);
    printf("cb = %p\n", cb);
    printf("sc = %p\n\n", sc);
    printf("a = %2d\n", a);
    printf("b = %2d\n", b);
    printf("c = %2d\n\n", c);
    printf("&a = %p\n", &a);
    printf("&b = %p\n", &b);
    printf("&c = %p\n\n", &c);
    printf("*&a = %2d\n\n", *&a);
    printf("*cb - *ca = %2d\n", *cb - *ca);
    printf("*cb + *ca = %2d\n\n", *cb + *ca);
    printf("Значення вказівника до\n"
           "додавання константи 2: cb = %p\n\n",
           cb);
    cb = cb + 2; // додавання константи до вказівника
    printf("Значення вказівника після\n"
           "додавання константи 2: cb = %p\n\n",
           cb);
    cb++;
    printf("cb = %p\n", cb);
    ca--;
    printf("ca = %p\n", ca);
    printf("cb - ca = %d\n\n", cb - ca);
}

void task5()
{
    // Введення натурального чотиризначного числа
    int *number;
    printf("Введіть натуральне чотиризначне число: ");
    scanf("%d", number);

    // Ініціалізація вказівника на число та інші допоміжні змінні
    int original_number = *number;
    int sum = 0;
    int digit;

    // Цикл для обчислення суми цифр числа
    while (*number > 0)
    {
        // Отримання останньої цифри числа
        digit = *number % 10;

        // Додавання цифри до суми
        sum += digit;

        // Видалення останньої цифри числа
        *number /= 10;
    }

    // Виведення результатів
    printf("Число: %d\n", original_number);
    printf("Сума його цифр: %d\n", sum);
}

void task6()
{
    // Ініціалізація змінної типу double
    double number = 3.1415;

    // Ініціалізація вказівників та їх адресами
    char *char_p = &number;
    int *int_p = &number;
    double *double_p = &number;
    void *void_p = &number;

    // Виведення значень вказівників та їхніх характеристик
    printf("Значення вказівника char_p: %p, Розмір: %zu, Довжина: %zu\n", (void *)char_p, sizeof(char_p), sizeof(*char_p));
    printf("Значення вказівника int_p: %p, Розмір: %zu, Довжина: %zu\n", (void *)int_p, sizeof(int_p), sizeof(*int_p));
    printf("Значення вказівника double_p: %p, Розмір: %zu, Довжина: %zu\n", (void *)double_p, sizeof(double_p), sizeof(*double_p));
    printf("Значення вказівника void_p: %p, Розмір: %zu\n", (void *)void_p, sizeof(void_p));
}

int main()
{
    init_code_page();

    struct TaskList task_list = {NULL, 0};
    register_task(&task_list, task2, 2, "Завдання 2");
    register_task(&task_list, task3, 3, "Завдання 3");
    register_task(&task_list, task4, 4, "Завдання 4");
    register_task(&task_list, task5, 5, "Завдання 5");
    register_task(&task_list, task6, 6, "Завдання 6");

    run_task_manager(&task_list);

    return 0;
}
