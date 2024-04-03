#include "utils.h"

int random_number(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
}

char *generate_name(int len)
{
    char *res = malloc(sizeof(char) * (len + 1));

    for (int i = 0; i < len; i++)
    {
        res[i] = random_number('a', 'z');
    }
    res[len] = '\0';

    return res;
}