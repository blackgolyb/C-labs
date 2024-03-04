#include <stdio.h>
#include <stdbool.h>

#include "task_manager.h"

void register_task(struct TaskList *task_list, void (*task_function)(), int id, char *title)
{
    // Збільшення розміру масиву на один елемент
    task_list->count++;
    task_list->tasks = realloc(task_list->tasks, task_list->count * sizeof(struct Task));

    // Додавання нового завдання до масиву
    task_list->tasks[task_list->count - 1].task_function = task_function;
    task_list->tasks[task_list->count - 1].id = id;
    task_list->tasks[task_list->count - 1].title = title;
}

void run_tusk(struct TaskList *task_list, int task_number)
{
    bool is_any_task_start = false;

    for (int i = 0; i < task_list->count; i++)
    {
        if (task_list->tasks[i].id == task_number)
        {
            is_any_task_start = true;
            printf("%s\n", task_list->tasks[i].title);
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
    printf("%3d -- вийти з програми\n", -1);
    for (int i = 0; i < task_list->count; i++)
    {
        printf("%3d -- %s\n", task_list->tasks[i].id, task_list->tasks[i].title);
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
