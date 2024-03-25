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

#define lambda(lambda$_ret, lambda$_args, lambda$_body) \
    ({                                                  \
        lambda$_ret lambda$__anon$ lambda$_args         \
            lambda$_body                                \
                &lambda$__anon$;                        \
    })

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

    unsigned short a, b;
    a = 0b0001011011001100;
    b = 0b0001001011000101;

    register_task(
        &task_list,
        lambda(void, (), { task1(a, b); }),
        1,
        "Завдання №1. Визначення кількості одиниць"
    );
    register_task(
        &task_list,
        lambda(void, (), { task2(a, b); }),
        2,
        "Завдання №2. Операція побітового заперечення (~)"
    );
    register_task(
        &task_list,
        lambda(void, (), { task3(a, b); }),
        3,
        "Завдання №3. Двомісні побітові операції"
    );
    register_task(
        &task_list,
        lambda(void, (), { task4(a, 6, 12); }),
        4,
        "Завдання №4. Встановлення бітів 6-12 для a в 0"
    );
    register_task(
        &task_list,
        lambda(void, (), { task5(a, 1, 7); }),
        5,
        "Завдання №5. Встановлення бітів 1-7 для b в 0"
    );
    register_task(
        &task_list,
        lambda(void, (), { task6(a, 7, 12); }),
        6,
        "Завдання №6. Зсув бітів 7-12 операнда a вправо"
    );
    register_task(
        &task_list,
        lambda(void, (), { task7(a, 7, 12); }),
        7,
        "Завдання №7. Зсув бітів 7-12 операнда b вліво"
    );

    puts("Варіант №7");
    for (int i = 1; i <= 7; i++)
        run_tusk(&task_list, i);

    return 0;
}