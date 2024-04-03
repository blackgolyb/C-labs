#include "dyn_array.h"


DynArray *da_create(int capacity, int capacity_addition, int item_size)
{
    DynArray *array = malloc(sizeof(DynArray));
    array->capacity = capacity;
    array->capacity_addition = capacity_addition;
    array->item_size = item_size;
    array->size = 0;
    array->arr = malloc(array->capacity * array->item_size);

    return array;
}

void da_append(DynArray *array, void *item)
{
    if ((array->size + 1) > array->capacity)
    {
        array->capacity += array->capacity_addition;
        array->arr = realloc(array->arr, array->capacity * array->item_size);
    }

    array->arr[array->size] = item;
    array->size++;
}

void *da_get(DynArray *array, int i)
{
    if (i < 0)
        i = array->size-i;
    if (i >= array->size)
        return NULL;
    return array->arr[i];
}

int da_size(DynArray *array)
{
    return array->size;
}

void da_free(DynArray *array)
{
    for (int i = 0; i < array->size; i++)
        free(array->arr[i]);
    free(array->arr);
    free(array);
}
