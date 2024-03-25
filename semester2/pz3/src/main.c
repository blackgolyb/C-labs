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

    register_task(&task_list, fun_malloc, 1, "Виділення блоку пам’яті за допомогою функції malloc()");
    register_task(&task_list, fun_calloc, 2, "Виділення блоку пам’яті за допомогою функції calloc()");
    register_task(&task_list, task3, 3, "Збільшення блоку пам’яті за допомогою функції realloc()");

    run_task_manager(&task_list);

    return 0;
}