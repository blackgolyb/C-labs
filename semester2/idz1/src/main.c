#include <stdio.h>
#include <stdlib.h>

#include "task_manager.h"
#include "tasks.h"

int main()
{
    struct TaskList task_list = {NULL, 0};

    register_task(&task_list, task1, 1, "Завдання 1");
    register_task(&task_list, task2_1, 2, "Завдання 2 I (Робота з текстовим файлом)");
    register_task(&task_list, task2_2, 3, "Завдання 2 II (Робота з бінарним файлом)");

    run_task_manager(&task_list);

    return 0;
}