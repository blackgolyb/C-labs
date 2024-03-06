#include <stdio.h>
#include <stdlib.h>

float generate_random_float(float min, float max)
{
    return (float)rand() / RAND_MAX * (max - min) + min;
}

int task2_2()
{
    int n = 14;
    // Пункт 1: Записати 14 випадкових дійсних чисел у бінарний файл bin.dat
    FILE *file = fopen("bin.dat", "wb");
    for (int i = 0; i < n; ++i)
    {
        float random_num = generate_random_float(10.28, 34.59);
        fwrite(&random_num, sizeof(float), 1, file);
    }
    fclose(file);

    // Пункт 2: Вивести числа, які містяться у файлі, на консоль
    file = fopen("bin.dat", "rb");
    printf("Числа, які містяться у файлі:\n");
    float number;
    while (fread(&number, sizeof(float), 1, file) == 1)
        printf("%.2f ", number);
        
    printf("\n");
    fclose(file);

    // Пункт 3: Прочитати сьоме число та вивести його на консоль
    file = fopen("bin.dat", "rb");
    fseek(file, 6 * sizeof(float), SEEK_SET); // Перехід на сьому числі
    fread(&number, sizeof(float), 1, file);
    printf("Сьоме число: %.2f\n", number);
    fclose(file);

    // Пункт 4: Обчислити суму чисел, які знаходяться у файлі bin.dat
    file = fopen("bin.dat", "rb");
    float sum = 0.0;
    while (fread(&number, sizeof(float), 1, file) == 1)
        sum += number;

    printf("Сума чисел у файлі: %.2f\n", sum);
    fclose(file);

    return 0;
}
