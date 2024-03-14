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

int main()
{
    init_code_page();
    
    struct TaskList task_list = {NULL, 0};

    register_task(&task_list, task1, 1, "Завдання 1");
    register_task(&task_list, task2_1, 2, "Завдання 2 I (Робота з текстовим файлом)");
    register_task(&task_list, task2_2, 3, "Завдання 2 II (Робота з бінарним файлом)");

    run_task_manager(&task_list);

    return 0;
}