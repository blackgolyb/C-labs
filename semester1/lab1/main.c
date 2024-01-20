#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void task1()
{
    float a, b, c, p, S;
    printf("Введіть довжину сторони a: ");
    scanf("%f", &a);
    printf("Введіть довжину сторони b: ");
    scanf("%f", &b);
    printf("Введіть довжину сторони c: ");
    scanf("%f", &c);
    printf("\n");

    bool is_triangle_exist = (a + b > c) && (a + c > b) && (b + c > a);
    bool is_edges_positive = (a > 0) && (b > 0) && (c > 0);

    if (is_triangle_exist && is_edges_positive)
    {
        p = (a + b + c) / 2;
        S = sqrt(p * (p - a) * (p - b) * (p - c));

        printf("Площа трикутника = %5.3f\n", S);
    }
    else
    {
        printf("Дані введені з помилками\n");
    }
}

void task2()
{
    printf("C (укр. Сі) — універсальна, процедурна, імперативна мова програмування загального призначення, розроблена у 1972 році Деннісом Рітчі у Bell Telephone Laboratories з метою написання нею операційної системи UNIX.\n");
    printf("Хоча С і було розроблено для написання системного програмного забезпечення, наразі вона досить часто використовується для написання прикладного програмного забезпечення.\n\n");

    printf("Омельніцький Андрій Миколайович\n");
    printf("Група КН-1023б\n");
}

int main()
{
    task1();
    task2();

    return 0;
}
