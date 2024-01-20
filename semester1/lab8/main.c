#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "task_manager.h"

// Розкоментуйте строку, якщо компілюєте програму на Windows
// #define IS_WINDOWS

#ifdef IS_WINDOWS
#include <windows.h>
#endif

void init_code_page()
{
    // Перевірка чи компілюється програма на Windows чи ні

#ifdef IS_WINDOWS
    SetConsoleOutputCP(1251);
#endif
}

int task1_foo(char *filename)
{
    FILE *file;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Не вдалося відкрити файл '%s'\n", filename);
        return 1;
    }

    char name[100];
    fgets(name, sizeof(name), file);

    printf("Інформація з файлу '%s':\n%s\n\n", filename, name);

    fclose(file);
    return 0;
}

void task1()
{
    task1_foo("input.txt");
    task1_foo("../input.txt");
    task1_foo("hmm.txt");
}

int task2()
{
    FILE *input_file;
    FILE *output_file;

    int number_of_input_files = 3;
    char input_files_names[][20] = {"input1.txt", "input2.txt", "input3.txt"};
    char output_file_name[] = "output.txt";

    char data[100];

    output_file = fopen(output_file_name, "a");

    if (output_file == NULL)
    {
        printf("Не вдалося відкрити файл для запису '%s'\n", output_file_name);
        return 1;
    }

    for (int i = 0; i < number_of_input_files; i++)
    {
        input_file = fopen(input_files_names[i], "r");

        if (input_file == NULL)
        {
            printf("Не вдалося відкрити вхідний файл '%s'\n", input_files_names[i]);
            return 1;
        }

        fgets(data, sizeof(data), input_file);
        fputs(data, output_file);

        fclose(input_file);
    }

    fclose(output_file);

    printf("Інформація з трьох вхідних файлів була успішно записана в '%s'\n", output_file_name);
    return 0;
}

int task3_fill(int n, char *filename)
{
    FILE *file;
    int *numbers = malloc(sizeof(int) * n);

    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        numbers[i] = rand() % 90 + 10;
    }

    file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Не вдалося відкрити файл для запису '%s'\n", filename);
        return 1;
    }
    fwrite(numbers, sizeof(int), n, file);
    fclose(file);
    return 0;
}

int task3_print(int n, int variant_number, char *filename)
{
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Не вдалося відкрити файл для читання '%s'\n", filename);
        return 1;
    }

    printf("Вміст файлу '%s':\n", filename);

    int *numbers = malloc(sizeof(int) * n);
    fread(numbers, sizeof(int), n, file);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    int position = (variant_number - 1) % n;
    printf("Число на позиції %d: %d\n", position, numbers[position]);

    fclose(file);
    return 0;
}

void task3()
{

    const int n = 16;
    char filename[] = "bin.dat";
    int variant_number = 7;

    task3_fill(n, filename);
    task3_print(n, variant_number, filename);

    return 0;
}

int main()
{
    init_code_page();

    struct TaskList task_list = {NULL, 0};
    register_task(&task_list, task1, 1, "Завдання 1");
    register_task(&task_list, task2, 2, "Завдання 2");
    register_task(&task_list, task3, 3, "Завдання 3");

    run_task_manager(&task_list);

    return 0;
}
