#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

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

    task1();
}