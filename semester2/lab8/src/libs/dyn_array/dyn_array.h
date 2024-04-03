#ifndef DYN_ARRAY_H_INCLUDED
#define DYN_ARRAY_H_INCLUDED

#include <stdlib.h>

typedef struct DynArray
{
    void **arr;
    int size;
    int capacity;
    int capacity_addition;
    int item_size;
} DynArray;

DynArray *da_create(int capacity, int capacity_addition, int item_size);
void da_append(DynArray *array, void *item);
void *da_get(DynArray *array, int i);
int da_size(DynArray *array);
void da_free(DynArray *array);

#endif // DYN_ARRAY_H_INCLUDED