#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode
{
    void *data;
    struct ListNode *next;
    struct ListNode *prev;
};

typedef struct
{
    int type_size;
    struct ListNode *head;
} List;

List *create_list(int type_size)
{
    List *list = malloc(sizeof(List));
    list->type_size = type_size;
    list->head = NULL;
    return list;
}

int len_of_list(List *list)
{
    int len = 0;
    for (struct ListNode *node = list->head; node; node = node->next)
        len++;

    return len;
}

void destroy_list(List *list)
{
    for (struct ListNode *node = list->head; node; node = node->next)
        free(node);
}

void push_back(List *list, void *elem)
{
    struct ListNode *last_node = list->head;

    if (!last_node)
    {
        list->head = malloc(sizeof(struct ListNode));
        list->head->data = elem;
        list->head->next = NULL;
        list->head->prev = NULL;
        return;
    }

    while (last_node->next)
        last_node = last_node->next;

    last_node->next = malloc(sizeof(struct ListNode));
    last_node->next->data = elem;
    last_node->next->next = NULL;
    last_node->next->prev = last_node;
}

void *get_by_index(List *list, int index)
{
    int i = 0;
    struct ListNode *node = list->head;

    for (; node && (i != index); node = node->next)
        i++;

    if (!node)
        return NULL;

    return node->data;
}

const char *get_field(char *line, int num, const char *delim)
{
    char tmp[strlen(line)];
    strcpy(tmp, line);

    const char *tok;
    for (tok = strtok(tmp, delim);
         tok && *tok;
         tok = strtok(NULL, delim))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

float *get_float_field(char *line, int num, const char *delim)
{
    float *tmp = malloc(sizeof(float));
    *tmp = atof(get_field(line, num, delim));
    return tmp;
}

float *get_int_field(char *line, int num, const char *delim)
{
    int *tmp = malloc(sizeof(int));
    *tmp = atoi(get_field(line, num, delim));
    return tmp;
}

float *get_long_int_field(char *line, int num, const char *delim)
{
    long int *tmp = malloc(sizeof(long int));
    *tmp = atol(get_field(line, num, delim));
    return tmp;
}

float *get_long_long_int_field(char *line, int num, const char *delim)
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

List *copy_list(List *list)
{
    List *new_list = create_list(list->type_size);
    void *tmp;
    for (struct ListNode *node = list->head; node; node = node->next)
    {
        tmp = malloc(list->type_size);
        memcpy(tmp, node->data, list->type_size);
        push_back(new_list, tmp);
    }
        

    return new_list;
}

void correct_x(List *list)
{
    int i = 0;
    float x;
    for (struct ListNode *node = list->head; node; node = node->next)
    {
        x = *(float *)node->data;

        if (i <= 9)
        {
            *(float *)node->data = x / (i + 1);
        }
        else if (i <= 19)
        {
            *(float *)node->data = x - i - 1;
        }
        else if (i <= 29)
        {
            *(float *)node->data = x - (i + 1) * (i + 1);
        }

        i++;
    }
}

void correct_y(List *list_x, List *list_y)
{
    int i = 0;
    float s = count_average(list_x);

    for (struct ListNode *node = list_y->head; node; node = node->next)
    {
        *(float *)node->data = *(float *)node->data - s / ((i + 1) * (i + 1));
        i++;
    }
}

int main()
{
    const char *input_file_path = "input.csv";
    const char *output_file_path = "output.csv";
    const char *delim = ";";

    int n;
    FILE *input_file, *output_file;

    input_file = fopen(input_file_path, "r");
    List *x = create_list(sizeof(float));
    List *y = create_list(sizeof(float));

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
        push_back(x, get_float_field(line, /* field index: */ 1, delim));
        push_back(y, get_float_field(line, /* field index: */ 2, delim));
    }
    fclose(input_file);

    correct_y(x, y);
    correct_x(x);

    n = len_of_list(x);
    output_file = fopen(output_file_path, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(output_file, "%f;%f\n", *(float *)get_by_index(x, i), *(float *)get_by_index(y, i));
    }
    fclose(output_file);

    return 0;
}
