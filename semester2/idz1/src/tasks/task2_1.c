#include <stdio.h>
#include <locale.h>

#ifdef WIN32
#include <windows.h>
#endif

#ifdef WIN32
#define FIX_FOR_SCANF(body)\
    SetConsoleOutputCP(1251);\
    SetConsoleCP(1251);\
    body\
    SetConsoleOutputCP(CP_UTF8);\
    SetConsoleCP(CP_UTF8);
#else
#define FIX_FOR_SCANF(body) body
#endif

int read_number_from_file(FILE *file, int line_number, int *number)
{
    rewind(file);
    for (int currentLine = 1; currentLine < line_number; ++currentLine)
        if (fscanf(file, "%*[^\n]\n") == EOF)
            return 0;

    return fscanf(file, "%d", number) == 1;
}

void task2_1()
{
    const char *input_file_path = "input.txt";

    // Пункт 1: Записати 7 довільних цілих чисел у файл input.txt
    FILE *file = fopen(input_file_path, "w");

    int nn = 7;
    int number;
    printf("Введіть %d довільних цілих чисел:\n", nn);
    for (int i = 0; i < nn; ++i)
    {
        scanf("%d", &number);
        fprintf(file, "%d", number);
        if (i != nn - 1)
            fprintf(file, "\n");
    }
    fclose(file);

    // Пункт 2: Вивести вміст файлу input.txt
    file = fopen(input_file_path, "r");
    printf("Вміст файлу після додавання:\n");
    char ch;
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);
    fclose(file);

    // Пункт 3: Додати слово українською до кінця файлу input.txt
    file = fopen(input_file_path, "a");
    char word[50];
    printf("\nВведіть 3 слова українською:\n");

    FIX_FOR_SCANF(
        for (int i = 0; i < 3; i++)
        {
            scanf("%s", word);
            fprintf(file, "\n%s", word);
        }
    );
    fclose(file);

    // Пункт 4: Вивести вміст файлу input.txt після додавання слова
    file = fopen(input_file_path, "r");
    printf("\nВміст файлу після додавання слова:\n");
    FIX_FOR_SCANF(
        while ((ch = fgetc(file)) != EOF)
            putchar(ch);
    );
    fclose(file);

    // Пункт 5: Прочитати шосте ціле число та вивести його
    file = fopen(input_file_path, "r");
    int sixth_number;
    read_number_from_file(file, 6, &sixth_number);
    printf("\nШосте ціле число: %d\n", sixth_number);
    fclose(file);
}
