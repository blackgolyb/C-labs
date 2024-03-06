#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

#include "linked_list.h"

const char *get_field(char *line, int num, const char *delim)
{
    int n = strlen(line);
    char *tmp = (char *)malloc(sizeof(char) * (n + 1));
    tmp[n] = '\0';
    strcpy(tmp, line);

    const char *tok;
    for (tok = strtok(tmp, delim);
         tok && *tok;
         tok = strtok(NULL, delim))
    {
        if (!num--)
        {
            n = strlen(tok);
            char *res = (char *)malloc(sizeof(char) * (n + 1));
            res[n] = '\0';
            strcpy(res, tok);
            free(tmp);
            return res;
        }
    }
    free(tmp);
    return NULL;
}

float *get_float_field(char *line, int num, const char *delim)
{
    float *tmp = malloc(sizeof(float));
    *tmp = atof(get_field(line, num, delim));
    return tmp;
}

int *get_int_field(char *line, int num, const char *delim)
{
    int *tmp = malloc(sizeof(int));
    *tmp = atoi(get_field(line, num, delim));
    return tmp;
}

long int *get_long_int_field(char *line, int num, const char *delim)
{
    long int *tmp = malloc(sizeof(long int));
    *tmp = atol(get_field(line, num, delim));
    return tmp;
}

long long int *get_long_long_int_field(char *line, int num, const char *delim)
{
    long long int *tmp = malloc(sizeof(long long int));
    *tmp = atoll(get_field(line, num, delim));
    return tmp;
}

float count_average(List *list)
{
    int n = 0;
    float average = 0;

    for (struct ListNode *node = list->head; node; node = node->next)
    {
        n++;
        average += *(float *)node->data;
    }

    return average / n;
}

float count_min(List *list)
{
    float min = *(float *)list->head->data;
    for (struct ListNode *node = list->head; node; node = node->next)
        if (*(float *)node->data < min)
            min = *(float *)node->data;

    return min;
}

float count_max(List *list)
{
    float min = *(float *)list->head->data;
    for (struct ListNode *node = list->head; node; node = node->next)
        if (*(float *)node->data > min)
            min = *(float *)node->data;

    return min;
}

void correct_x(List *list)
{
    int i = 0;
    float x;
    for (struct ListNode *node = list->head; node; node = node->next)
    {
        x = *(float *)node->data;

        if (i < 14)
            *(float *)node->data = (i + 1) * x / 5.0;
        else if (i < 23)
            *(float *)node->data = x + 5 * i * i;
        else if (i < 30)
            *(float *)node->data = x + sqrtf((float)(i * i + i));

        i++;
    }
}

void correct_y(List *list_x, List *list_y)
{
    int i = 0;
    float s = count_average(list_x);

    for (struct ListNode *node = list_y->head; node; node = node->next)
    {
        *(float *)node->data = (*(float *)node->data + i) * 2.0 / s;
        i++;
    }
}

void task1()
{
    setlocale(LC_ALL, "C.UTF-8");

    const char *input_file_path = "input.csv";
    const char *output_file_path = "output.csv";
    const char *delim = ";";

    int n;
    FILE *input_file, *output_file;

    input_file = fopen(input_file_path, "r");
    List *x = ll_create(sizeof(float));
    List *y = ll_create(sizeof(float));

    if (input_file == NULL)
    {
        puts("Error opening file");
        exit(-1);
    }

    // Read CSV file
    char line[1024];
    while (fgets(line, 1024, input_file))
    {
        // Add x and y to the list
        ll_push_back(x, get_float_field(line, /* field index: */ 1, delim));
        ll_push_back(y, get_float_field(line, /* field index: */ 2, delim));
    }
    fclose(input_file);

    correct_y(x, y);
    correct_x(x);

    n = ll_len(x);
    output_file = fopen(output_file_path, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(output_file, "%f;%f\n", *(float *)ll_get(x, i), *(float *)ll_get(y, i));
    }
    fclose(output_file);

    float control_sum = 0;
    for (int i = 0; i < ll_len(y); i++)
        control_sum += *(float *)ll_get(y, i);

    printf("control sum: 114.5 == %.1f\n", control_sum);

    ll_destroy(x);
    ll_destroy(y);

    return 0;
}
