#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdbool.h>

typedef struct Cell
{
    char h_align;
    char v_align;
    char neighbors;
    wchar_t *text;
} Cell;

typedef struct Table
{
    int width;
    int height;
    wchar_t *title;
    Cell **cells;
} Table;

enum NEIGHBORS_ADDITION
{
    NA_TOP = 1,
    NA_RIGHT = 2,
    NA_BOTTOM = 4,
    NA_LEFT = 8,
};

Table *create_table(int width, int height);
void destroy_table(Table *table);

void group_cells(Table *table, int x, int y, int width, int height);
bool *get_cell_neighbors(Table *table, int x, int y);
int max_content_size(Table *table, int column);
void put_string_aligned(wchar_t *dest, wchar_t *src, int place_size, int place, char align);
void print_table(Table *table);
wchar_t *int_to_wide_string(int value);
wchar_t *string_to_wide_string(char *input_string);
wchar_t *float_to_wide_string(float input_string);

#endif // TABLE_H_INCLUDED
