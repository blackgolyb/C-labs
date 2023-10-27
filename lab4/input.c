#include <stdio.h>
#include <stdbool.h>

static bool elem_in_char_array(char *array, char size, char elem)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == elem)
        {
            return true;
        }
    }

    return false;
}

char chose_one_option_input(char *chooses)
{
    char option;

    char *formatted_chooses;
    int n_chooses = strlen(chooses);
    formatted_chooses = malloc(n_chooses * 3 - 2 + 1);

    for (int i = 0; i < n_chooses - 1; i++)
    {
        formatted_chooses[i * 3] = chooses[i];
        formatted_chooses[i * 3 + 1] = ',';
        formatted_chooses[i * 3 + 2] = ' ';
    }
    formatted_chooses[(n_chooses - 1) * 3] = chooses[n_chooses - 1];

    do
    {
        printf("choose one of (%s): ", formatted_chooses);
        scanf(" %c", &option);
    } while (!elem_in_char_array(chooses, n_chooses, option));

    return option;
}

void input_float(float *value_ptr, char *value_name)
{
    printf("Введіть значення %s: ", value_name);
    scanf(" %f", value_ptr);
}

void input_double(double *value_ptr, char *value_name)
{
    printf("Введіть значення %s: ", value_name);
    scanf(" %f", value_ptr);
}

void input_int(int *value_ptr, char *value_name)
{
    printf("Введіть значення %s: ", value_name);
    scanf(" %d", value_ptr);
}

void input_char(char *value_ptr, char *value_name)
{
    printf("Введіть значення %s: ", value_name);
    scanf(" %c", value_ptr);
}
