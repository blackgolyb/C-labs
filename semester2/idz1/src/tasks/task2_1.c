#include <stdio.h>

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
    const char *input_file_path = "task2.txt";

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
    for (int i = 0; i < 3; i++)
    {
        scanf("%s", word);
        fprintf(file, "\n%s", word);
    }
    fclose(file);

    // Пункт 4: Вивести вміст файлу input.txt після додавання слова
    file = fopen(input_file_path, "r");
    printf("\nВміст файлу після додавання слова:\n");
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);
    fclose(file);

    // Пункт 5: Прочитати шосте ціле число та вивести його
    file = fopen(input_file_path, "r");
    int sixth_number;
    read_number_from_file(file, 6, &sixth_number);
    printf("\nШосте ціле число: %d\n", sixth_number);
    fclose(file);
}
