#include <stdio.h>
#include <math.h>
#include <stdbool.h>  //бібліотека для задання булевої змінної
#include <inttypes.h> // підтримує мобільні типи
#include <stdlib.h>

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

struct Task
{
    void (*task_function)();
    int id;
};

struct TaskList
{
    struct Task *tasks;
    int count;
};

void register_task(struct TaskList *task_list, void (*task_function)(), int id)
{
    // Збільшення розміру масиву на один елемент
    task_list->count++;
    task_list->tasks = realloc(task_list->tasks, task_list->count * sizeof(struct Task));

    // Додавання нового завдання до масиву
    task_list->tasks[task_list->count - 1].task_function = task_function;
    task_list->tasks[task_list->count - 1].id = id;
}

void run_tusk(struct TaskList *task_list, int task_number)
{
    bool is_any_task_start = false;

    for (int i = 0; i < task_list->count; i++)
    {
        if (task_list->tasks[i].id == task_number)
        {
            is_any_task_start = true;
            printf("Запущено завдання під номером %d\n", task_number);
            printf("========================================\n\n");
            task_list->tasks[i].task_function();
            printf("\n========================================\n");
        }
    }

    if (!is_any_task_start)
    {
        printf("========================================\n");
        printf("Не зайдено жодного завдання під номером %d\n", task_number);
        printf("========================================\n");
    }
}

void run_task_manager(struct TaskList *task_list)
{
    printf("Доступні опції:\n");
    printf("-1 - вийти з програми\n");
    for (int i = 0; i < task_list->count; i++)
    {
        printf("%d - запустити завдання під номером %d\n", task_list->tasks[i].id, task_list->tasks[i].id);
    }

    int task_number;

    while (true)
    {
        printf("\n\n");
        printf("Введіть номер опціїї або номер завдання: ");
        scanf("%d", &task_number);
        printf("\n");

        if (task_number == -1)
        {
            break;
        }

        run_tusk(task_list, task_number);
    };
}

void task1()
{
    // Вивід значень типу int
    int ten = 10;
    int two = 2;
    printf("=============================\n");
    printf("%d мінус %d дорівнює %d\n", ten, 2, ten - two);
    printf("=============================\n");
    return 0;
}

void task2()
{
    // Відображення вісімкових і шістнадцяткових чисел
    int x = 100;
    printf("=============================\n");
    printf("десяткове = %d\n"
           "вісімкове = %o\n"
           "шістнадцяткове = %x\n",
           x, x, x);
    printf("=============================\n");
    printf("десяткове = %d\n"
           "вісімкове = %#o\n"
           "шістнадцяткове = %#x\n",
           x, x, x);
    printf("=============================\n");
    return 0;
}

void task3()
{
    // Цілочислове переповнення
    int i = 2147483647;
    unsigned int j = 4294967295;
    printf("=============================\n");
    printf("%11d %11d %11d\n", i, i + 1, i + 2);
    printf("%11u %11u %11u\n", j, j + 1, j + 2);
    printf("=============================\n");
    return 0;
}

void task4()
{
    // Вивід значень типів short, long, long long і unsigned
    // система з 32-бітним типом int і 16-бітним типом short
    unsigned int un = 3000000000;
    short end = 200;
    long big = 65537;
    long long verybig = 12345678908642;
    printf("=============================\n");
    printf("un = %u, але не %d\n", un, un);
    printf("=============================\n");
    printf("end = %hd і %d\n", end, end);
    printf("=============================\n");
    printf("big = %ld, але не %hd\n", big, big);
    printf("=============================\n");
    printf("verybig = %lld, але не %ld\n", verybig, verybig);
    printf("=============================\n");
    return 0;
}

void task5()
{
    // Друковані символи
    unsigned char ch;
    printf("Введіть будь-який символ: ");
    scanf("%c", &ch);
    printf("Код символу %c = %d\n\n", ch, ch);

    for (int i = 32; i <= 255; i++)
    {
        if (i % 16 == 0)
            printf("\n");
        printf("%2c", i);
    }
    printf("\n");

    return 0;
}

void task6()
{
    // Мобільні типи: stdint.h і inttypes.h
    int32_t me32; // me32 — це 32-бітна змінна зі знаком
    me32 = 45933945;
    printf("Спочатку припустимо, що int32_t є int: ");
    printf("me32 = %d\n", me32);
    printf("Далі не будемо робити жодних припущень.\n");
    printf("Замість цього скористаємося \""
           "макросом\" з файлу inttypes.h: ");
    printf("me32 = %" PRId32 "\n", me32);
    return 0;
}

void task7()
{
    //  Вивід значень з рухомою комою
    float aboat = 32000.0;
    double abet = 2.14e9;
    long double dip = 5.32e-5;
    printf("%f може бути записано як %e\n", aboat, aboat);
    // для виводу наступного рядка потрібен компілятор,
    // який підтримує С99 або С11
    printf("Та його %a в шістнадцятковій формі запису\n",
           aboat);
    printf("%f може бути записано як %e\n", abet, abet);
    printf("%lf може бути записано як %le\n",
           dip, dip);
    return 0;
}

void task8()
{
    // Переповнення та втрата значущості в операціях з рухомою комою
    float toobig = 3.4E38 * 100.0f;
    printf("Виводимо на консоль дуже велике значення\n");
    printf("%e\n", toobig);
    return 0;
}

void task9()
{
    // Розміри типів
    printf("Тип int має розмір %2d байт.\n",
           sizeof(int));
    printf("Тип char має розмір %2d байт.\n",
           sizeof(char));
    printf("Тип long має розмір %2d байт.\n",
           sizeof(long));
    printf("Тип long long має розмір %2d байт.\n",
           sizeof(long long));
    printf("Тип double має розмір %2d байт.\n",
           sizeof(double));
    printf("Тип long double має розмір %2d байт.\n",
           sizeof(long double));
    return 0;
}

#define TYPE_NAME(type) #type
#define print_type_size(type) _print_type_size(sizeof(type), TYPE_NAME(type))

void _print_type_size(int type_size, char *type_name)
{
    printf("Тип %s\tмає розмір %d байт\n", type_name, type_size);
}

void task0()
{
    print_type_size(signed short);
    print_type_size(unsigned long long);
}

int main()
{
    init_code_page();

    struct TaskList task_list = {NULL, 0};
    register_task(&task_list, task0, 0);
    register_task(&task_list, task1, 1);
    register_task(&task_list, task2, 2);
    register_task(&task_list, task3, 3);
    register_task(&task_list, task4, 4);
    register_task(&task_list, task5, 5);
    register_task(&task_list, task6, 6);
    register_task(&task_list, task7, 7);
    register_task(&task_list, task8, 8);
    register_task(&task_list, task9, 9);

    run_task_manager(&task_list);
    // task5();

    return 0;
}
