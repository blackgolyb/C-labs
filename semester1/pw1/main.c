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

void input_float_value(float *value_ptr, char *value_name)
{
    printf("Введіть значення %s: ", value_name);
    scanf("%f", value_ptr);
}

void input_int_value(int *value_ptr, char *value_name)
{
    printf("Введіть значення %s: ", value_name);
    scanf("%d", value_ptr);
}

void print_result(float value, char *value_name)
{
    printf("\n============================");
    printf("\nРезультат: %s = %9.5f", value_name, value);
    printf("\n============================\n");
}

void task1()
{
    float m;
    input_float_value(&m, "m");

    const float N = m * m + 2.8 * fabs(m) + 0.55;

    print_result(N, "N");
}

void task2()
{
    int N;

    input_int_value(&N, "N");

    if (N % 2 == 0)
    {
        float y, k, x;
        input_float_value(&y, "y");
        input_float_value(&k, "k");
        input_float_value(&x, "x");

        const float U = exp(y) + 7.355 * (k * k) + powf(sinf(x), 2);

        print_result(U, "U");
    }
    else
    {
        float z;
        input_float_value(&z, "z");

        const float F = 2 * sinf(0.214 * powf(z, 5) + 1);

        print_result(F, "F");
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
