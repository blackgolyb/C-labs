#include <stdio.h>
#include <limits.h>
#include <math.h>

#define ABIT 1
#define BBIT 3
#define CBIT 6

// Визначення структури з бітовими полями
struct
{
    unsigned int a : ABIT;
    unsigned int b : BBIT;
    unsigned int c : CBIT;
} bstr;

char *itobs(int n, char *ps)
{
    int i;
    const static int size = CHAR_BIT * sizeof(int);
    // передбачається кодування ASCII або схоже
    for (i = size - 1; i >= 0; i--, n >>= 1)
        ps[i] = (01 & n) + '0';
    ps[size] = '\0';
    return ps;
}

// відображення двійкового рядка блоками по 4
void show_bstr(const char *str)
{
    int i = 0;
    while (str[i]) // поки не буде отриманий нульовий символ
    {
        putchar(str[i]);
        if (++i % 4 == 0 && str[i])
            putchar(' ');
    }
}

void print_int_in_bin(int n)
{
    char bin_str[CHAR_BIT * sizeof(int) + 1];
    itobs(n, bin_str);
    show_bstr(bin_str);
}

void print_hypothesis(unsigned int a, unsigned int b, unsigned int c)
{
    bstr.a = a;
    bstr.b = b;
    bstr.c = c;

    int result = (bstr.c << (BBIT + ABIT)) + (bstr.b << ABIT) + bstr.a;

    puts("Перевірка гіпотези\n");
    printf("гіпотетичне значення в структури в int: %u\n", result);
    printf("реальне значення в структури в int: %u\n", *(unsigned int *)&bstr);
}

void print_test_case(unsigned int a, unsigned int b, unsigned int c)
{
    bstr.a = a;
    bstr.b = b;
    bstr.c = c;

    puts("=============================================");
    puts("Присвоєння значень бітовим полям \n");
    printf(" bstr.a = %5d;\n"
           " bstr.b = %5d;\n"
           " bstr.c = %5d;\n",
           a, b, c);
    puts("=============================================");
    printf("bstr = %u\n", bstr);
    puts("=============================================");
    print_int_in_bin(*(unsigned int *)&bstr);
    puts("\n=============================================");

    print_int_in_bin(bstr.a);
    printf("%5d\n", bstr.a);

    print_int_in_bin(bstr.b);
    printf("%5d\n", bstr.b);

    print_int_in_bin(bstr.c);
    printf("%5d\n", bstr.c);

    puts("=============================================");
    print_hypothesis(a, b, c);
    puts("=============================================\n");
}

void print_struct_info()
{
    printf("sizeof(bstr) = %d\n", sizeof(bstr));
    printf("=============================================\n");
    printf("Визначення бітових полів \n");
    printf("=============================================\n");
    printf("unsigned int a : %d;\n"
           "unsigned int b : %d;\n"
           "unsigned int c : %d;\n",
           ABIT, BBIT, CBIT);
    printf("=============================================\n\n");
}

int task4(void)
{
    print_struct_info();
    print_test_case(1, 6, 15);
    print_test_case(3, 40, 1111111);
}
