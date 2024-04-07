#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define AUTHOR "Омельніцький А.М."
#define GROUP "КН-1023б"
#define PRINT_INFO() printf("Author: %s, Group: %s\n", AUTHOR, GROUP)


// Макрос для обчислення максимуму між двома числами
#define PRINT_MAX(x, y) printf("MAX(%s, %s) = %d\n", #x, #y, ((x) > (y) ? (x) : (y)))

// Макрос для об'єднання двох рядків
#define CONCAT(x, y) x##y


void task1()
{
    PRINT_INFO();

    int num1 = 10, num2 = 20;
    
    // Використання макросу для знаходження максимуму
    PRINT_MAX(num1, num2);

    // Використання операції ## для об'єднання двох рядків
    int CONCAT(num, 3) = 13;
    printf("Змінна num1: %d\n", num3);
}