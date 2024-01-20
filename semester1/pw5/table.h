#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <stdbool.h>

typedef struct
{
    char h_align;
    char v_align;
    char neighbors;
    wchar_t *text;
} cell_t;

typedef struct
{
    int width;
    int height;
    wchar_t *title;
    cell_t **cells;
} table_t;

enum NEIGHBORS_ADDITION
{
    NA_TOP = 1,
    NA_RIGHT = 2,
    NA_BOTTOM = 4,
    NA_LEFT = 8,
};

table_t create_table(int width, int height);
void destroy_table(table_t *table);

void group_cells(table_t *table, int x, int y, int width, int height);
bool *get_cell_neighbors(table_t *table, int x, int y);
int max_content_size(table_t *table, int column);
void put_string_aligned(wchar_t *dest, wchar_t *src, int place_size, int place, char align);
void print_table(table_t *table);
wchar_t *int_to_wide_string(int value);

#endif // TABLE_H_INCLUDED
