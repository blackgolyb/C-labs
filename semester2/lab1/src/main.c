#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#include "task_manager.h"
#include "tasks.h"

#ifdef WIN32
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <io.h>
#include <fcntl.h>
#include <windows.h>

#endif

void init_code_page()
{
    // Перевірка чи компілюється програма на Windows чи ні
    setlocale(LC_ALL, "C.UTF-8");
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

void register_tasks(struct TaskList *task_list, void *(*tasks[])(), int n, char *name_template)
{
    for (int i = 0; i < n; ++i)
    {
        char *formattedString = malloc(sizeof(char) * 20);
        sprintf(formattedString, name_template, i + 1);
        register_task(task_list, tasks[i], i + 1, formattedString);
    }
}

int main()
{
    init_code_page();

    struct TaskList task_list = {NULL, 0};

    int n = sizeof(tasks) / sizeof(tasks[0]);
    register_tasks(&task_list, &tasks, n, "Завдання %d");

    run_task_manager(&task_list);

    return 0;
}