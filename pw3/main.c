#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Розкоментуйте строку, якщо компілюєте програму на Windows
// #define IS_WINDOWS

#ifdef IS_WINDOWS
#include <windows.h>
#endif

#define PI 3.14159265358979323846

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

void print_result(float value, char *value_name)
{
    printf("\n============================");
    printf("\nРезультат: %s = %9.5f", value_name, value);
    printf("\n============================\n");
}

void task1()
{
    bool print_iteration = false;

    const int interval_start = 1;
    const int interval_stop = 45;
    const int check_divider = 4;
    int sum = 0;

    int current_number = interval_start;
    do
    {
        if (current_number % check_divider == 0)
        {
            sum += current_number;
        }

        if (print_iteration)
        {
            char *answer = (current_number % check_divider == 0 ? "Так" : "Ні");
            printf("Число: %d\n", current_number);
            printf("============================\n");
            printf("Чи треба додавати число %s\n", answer);
            printf("Значення sum = %d\n\n", sum);
        }

        current_number++;
    } while (current_number <= interval_stop);

    print_result(sum, "sum");
}

float calculate_f(float x)
{
    return sinf(2 * x) + sqrtf(fabsf(tanf(3 * x))) + expf(4 * x);
}

void log_iteration(int i, float x, float f, int n)
{
    int num_of_charges = 0;
    while (n >= 1)
    {
        n = n / 10;
        num_of_charges += 1;
    }

    char *fmt = (char *)malloc((2 + num_of_charges) * sizeof(char));
    sprintf(fmt, "%s%d%s", "%", num_of_charges, "d");
    printf(fmt, i + 1);
    printf(": x = %6.3f f(x) = %9.6f\n", i, x, f);
}

void task2()
{
    const float x0 = -40.0;
    const float step = 0.4;
    const int n = 11;
    float x, f;

    for (int i = 0; i < n; i++)
    {
        x = (i * step) + x0;
        f = calculate_f(x);
        log_iteration(i, x, f, n);
    }
}

int main()
{
    init_code_page();

    struct TaskList task_list = {NULL, 0};
    register_task(&task_list, task1, 1);
    register_task(&task_list, task2, 2);

    run_task_manager(&task_list);

    return 0;
}
