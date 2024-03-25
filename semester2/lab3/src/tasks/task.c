#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SEP "===================================================="

void print_binary(void *num, size_t num_bytes)
{
    for (int i = (num_bytes * 8) - 1; i >= 0; i--)
    {
        printf("%d", (*(unsigned long long *)(num) >> i) & 1);
        if (i % 4 == 0)
            putchar(' ');
    }
}

void print_binary_with_highlight(void *num, size_t num_bytes, bool *highlights)
{
    for (int i = (num_bytes * 8) - 1; i >= 0; i--)
    {
        if (highlights[i])
            printf("\033[41m\033[30m\033[1m");
        printf("%d", (*(unsigned long long *)(num) >> i) & 1);
        if (highlights[i])
            printf("\033[0m");
        if (i % 4 == 0)
            putchar(' ');
    }
}

int count_ones(void *num, size_t num_bytes)
{
    int sum = 0;
    for (int i = (num_bytes * 8) - 1; i >= 0; i--)
        sum += (*(unsigned long long *)(num) >> i) & 1;

    return sum;
}

int task1(unsigned short a, unsigned short b)
{
    printf("Операнд a:\t\t\t");
    print_binary(&a, sizeof(a));
    putchar('\n');

    puts(SEP);
    printf("Кількість одиниць операнда a:\t\t%d\n", count_ones(&a, sizeof(a)));
    puts(SEP);

    printf("Операнд b:\t\t\t");
    print_binary(&b, sizeof(b));
    putchar('\n');

    puts(SEP);
    printf("Кількість одиниць операнда a:\t\t%d\n", count_ones(&b, sizeof(b)));
}

int task2(unsigned short a, unsigned short b)
{
    unsigned short not_a, not_b;
    not_a = ~a;
    not_b = ~b;

    printf("Операнд a:\t\t\t");
    print_binary(&a, sizeof(a));
    putchar('\n');

    puts(SEP);

    printf("Результат (~a):\t\t\t");
    print_binary(&not_a, sizeof(not_a));
    putchar('\n');

    puts(SEP);

    printf("Операнд b:\t\t\t");
    print_binary(&b, sizeof(b));
    putchar('\n');

    puts(SEP);

    printf("Результат (~b):\t\t\t");
    print_binary(&not_b, sizeof(not_b));
    putchar('\n');
}

int task3(unsigned short a, unsigned short b)
{
    unsigned short op1, op2, op3;
    op1 = a & b;
    op2 = a | b;
    op3 = a ^ b;

    printf("Операнд a:\t\t\t");
    print_binary(&a, sizeof(a));
    putchar('\n');

    printf("Операнд b:\t\t\t");
    print_binary(&b, sizeof(b));
    putchar('\n');

    puts(SEP);

    printf("Результат (a & b):\t\t");
    print_binary(&op1, sizeof(op1));
    putchar('\n');

    printf("Результат (a | b):\t\t");
    print_binary(&op2, sizeof(op2));
    putchar('\n');

    printf("Результат (a ^ b):\t\t");
    print_binary(&op3, sizeof(op3));
    putchar('\n');
}

void print_binary_highlight_bytes(unsigned short a, int start_bit, int end_bit)
{
    bool *highlights = calloc(sizeof(a), sizeof(bool));
    for (int i = start_bit; i <= end_bit; i++)
        highlights[i] = true;

    print_binary_with_highlight(&a, sizeof(a), highlights);
    free(highlights);
}

unsigned short get_bit_mask(int start_bit, int end_bit)
{
    unsigned short mask;
    mask = ((1 << (end_bit - start_bit + 1)) - 1);
    mask = mask << start_bit;
    return mask;
}

int task4(unsigned short a, int start_bit, int end_bit)
{
    unsigned short mask, res;
    mask = get_bit_mask(start_bit, end_bit);
    mask = ~mask;
    res = a & mask;

    printf("Операнд a:\t\t\t");
    print_binary(&a, sizeof(a));
    putchar('\n');

    printf("Маска:\t\t\t\t");
    print_binary(&mask, sizeof(mask));
    putchar('\n');

    puts(SEP);

    printf("Результат (a & 0x%x):\t\t", mask);
    print_binary_highlight_bytes(res, start_bit, end_bit);
    putchar('\n');
}

int task5(unsigned short b, int start_bit, int end_bit)
{
    unsigned short mask, res;
    mask = get_bit_mask(start_bit, end_bit);
    res = b | mask;

    printf("Операнд b:\t\t\t");
    print_binary(&b, sizeof(b));
    putchar('\n');

    printf("Маска:\t\t\t\t");
    print_binary(&mask, sizeof(mask));
    putchar('\n');

    puts(SEP);

    printf("Результат (a | 0x%x):\t\t", mask);
    print_binary_highlight_bytes(res, start_bit, end_bit);
    putchar('\n');
}

int task6(unsigned short a, int start_bit, int end_bit)
{
    unsigned short mask, res;
    mask = get_bit_mask(start_bit, end_bit);
    res = (a & mask) >> start_bit;

    printf("Операнд a:\t\t\t");
    print_binary_highlight_bytes(a, start_bit, end_bit);
    putchar('\n');

    puts(SEP);

    printf("Результат ((a & 0x%x)>>%d):\t", mask, start_bit);
    print_binary_highlight_bytes(res, 0, end_bit - start_bit);
    putchar('\n');
}

int task7(unsigned short b, int start_bit, int end_bit)
{
    unsigned short mask, res, bits, offset;
    bits = sizeof(b) * 8;
    mask = get_bit_mask(start_bit, end_bit);
    offset = bits - end_bit - 1;
    res = (b & mask) << offset;

    printf("Операнд b:\t\t\t");
    print_binary_highlight_bytes(b, start_bit, end_bit);
    putchar('\n');

    puts(SEP);

    printf("Результат ((b & 0x%x)<<%d):\t", mask, offset);
    print_binary_highlight_bytes(res, offset + start_bit, bits);
    putchar('\n');
}
