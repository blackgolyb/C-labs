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

    register_task(&task_list, task2, 2, "Завдання №2. Виділення пам'яті за допомогою malloc");
    register_task(&task_list, task3, 3, "Завдання №3. Заповнення випадковими числами");
    register_task(&task_list, task4, 4, "Завдання №4. Заповнення випадковими числами матриці");
    register_task(&task_list, task5, 5, "Завдання №5. Заповнення трикутної матриці (i ^ j)");
    register_task(&task_list, task6, 6, "Завдання №6. Заповнення матриці з рядками довільної довжини");
    register_task(&task_list, task7, 7, "Завдання №7. Лінійне розсташування матриці в пам'яті");
    register_task(&task_list, task8, 8, "Завдання №8. Заповнення масива строк різної довжини");
    register_task(&task_list, task9, 9, "Завдання №9. Динамічне додавання слів до масива");

    puts("Варіант №7");
    for (int i = 2; i <= 9; i++)
        run_tusk(&task_list, i);

    return 0;
}
