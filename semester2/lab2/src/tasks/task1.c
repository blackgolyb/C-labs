#include <string.h>
#include <stdio.h>

#define TYPE_NAME(type) #type
#define print_type_size(type) _print_type_size(sizeof(type), TYPE_NAME(type))

void _print_type_size(int type_size, char *type_name)
{
    printf("======================================\n");
    printf("Розмір типу %s в байтах: %d\n", type_name, type_size);
    printf("======================================\n");
}

union Value
{
    short s;
    int i;
    long l;
    float f;
    double d;
    char c;
    char ch[8];
};

void print_union_stats(union Value *value, int current_field)
{
    char ch[7];
    for (int i = 0; i < 7; i++)
        ch[i] = ' ';

    ch[current_field] = '*';

    printf("%c short: %hu\n", ch[0], value->s);
    printf("%c int: %u\n", ch[1], value->i);
    printf("%c long: %lu\n", ch[2], value->l);
    printf("%c float: %f\n", ch[3], value->f);
    printf("%c double: %f\n", ch[4], value->d);
    printf("%c char: '%c'\n", ch[5], value->c);
    printf("%c char[8]: .%-8s.\n", ch[6], value->ch);
    printf("======================================\n");
    printf("Результат: ");
    printf("|%02X|%02X|%02X|%02X|%02X|%02X|%02X|%02X|",
           value->ch[7], value->ch[6], value->ch[5], value->ch[4],
           value->ch[3], value->ch[2], value->ch[1], value->ch[0]);
    printf("\n======================================\n\n");
}

int task1(void)
{
    union Value value;

    value.d = 0.000000;
    value.s = 20698;
    printf("value.s = %hu;\n", value.s);
    print_type_size(short);
    print_union_stats(&value, 0);

    value.d = 0.000000;
    value.i = 51927206;
    printf("value.i = %u;\n", value.i);
    print_type_size(int);
    print_union_stats(&value, 1);

    value.d = 0.000000;
    value.l = 1071737324L;
    printf("value.l = %lu;\n", value.l);
    print_type_size(long);
    print_union_stats(&value, 2);

    value.d = 0.000000;
    value.f = 766.68;
    printf("value.f = %5.2f;\n", value.f);
    print_type_size(float);
    print_union_stats(&value, 3);

    value.d = 9288.81;
    printf("value.d = %5.2f;\n", value.d);
    print_type_size(double);
    print_union_stats(&value, 4);

    value.d = 0.000000;
    value.c = 'и';
    printf("value.c = '%c';\n", value.c);
    print_type_size(char);
    print_union_stats(&value, 5);

    value.d = 0.000000;
    strncpy(value.ch, "Omelniskyi", sizeof(value.ch) - 1);
    printf("value.ch[0] = '%c'; value.ch[1] = '%c';\n",
           value.ch[0], value.ch[1]);
    printf("value.ch[2] = '%c'; value.ch[3] = '%c';\n",
           value.ch[2], value.ch[3]);
    printf("value.ch[4] = '%c'; value.ch[5] = '%c';\n",
           value.ch[4], value.ch[5]);
    printf("value.ch[6] = '%c'; value.ch[7] = \'\\x0\'\n",
           value.ch[6]);
    print_type_size(char[8]);
    print_union_stats(&value, 6);

    printf("======================================\n");
    printf("Розмір об'єднання value: %d\n", sizeof(value));
    printf("======================================\n\n");
    return 0;
}