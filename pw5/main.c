#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include <math.h>

int random_number(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
}

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

table_t create_table(int width, int height)
{
    table_t table;
    table.width = width;
    table.height = height;
    table.cells = malloc(sizeof(cell_t *) * height);
    for (int i = 0; i < height; i++)
    {
        table.cells[i] = malloc(sizeof(cell_t) * width);
        for (int j = 0; j < width; j++)
        {
            table.cells[i][j] = (cell_t){'c', 'c', 0, L""};
        }
    }

    return table;
}
void destroy_table(table_t *table)
{
    for (int i = 0; i < table->height; i++)
    {
        free(table->cells[i]);
        table->cells[i] = NULL;
    }
    free(table->cells);
    table->cells = NULL;
    table->width = 0;
    table->height = 0;
}

enum NEIGHBORS_ADDITION
{
    NA_TOP = 1,
    NA_RIGHT = 2,
    NA_BOTTOM = 4,
    NA_LEFT = 8,
};

void group_cells(table_t *table, int x, int y, int width, int height)
{
    char add_h, add_v;
    for (int i = 0; i < height; i++)
    {
        if (height == 1)
        {
            add_h = 0;
        }
        else if (i == 0)
        {
            add_h = NA_BOTTOM;
        }
        else if (i == height - 1)
        {
            add_h = NA_TOP;
        }
        else
        {
            add_h = NA_TOP + NA_BOTTOM;
        }
        for (int j = 0; j < width; j++)
        {
            if (width == 1)
            {
                add_v = 0;
            }
            else if (j == 0)
            {
                add_v = NA_RIGHT;
            }
            else if (j == width - 1)
            {
                add_v = NA_LEFT;
            }
            else
            {
                add_v = NA_LEFT + NA_RIGHT;
            }

            table->cells[y + i][x + j].neighbors = add_h + add_v;
        }
    }
}

bool *get_cell_neighbors(table_t *table, int x, int y)
{
    bool *neighbors = malloc(sizeof(bool) * 4);
    char neighbors_val = table->cells[y][x].neighbors;

    for (int i = 0; i < 4; i++)
    {
        neighbors[i] = neighbors_val % 2;
        neighbors_val /= 2;
    }

    return neighbors;
}

int max_content_size(table_t *table, int column)
{
    int max_size = 0;
    int current_size = 0;
    for (int i = 0; i < table->height; i++)
    {
        if (table->cells[i][column].text == NULL)
            continue;

        current_size = wcslen(table->cells[i][column].text) + 2;
        if (current_size > max_size)
        {
            max_size = current_size;
        }
    }

    return max_size;
}

void put_string_aligned(wchar_t *dest, wchar_t *src, int place_size, int place, char align)
{
    int src_size = wcslen(src);
    int addition = 0;

    for (int i = 0; i < place_size; i++)
    {
        dest[i + place] = L' ';
    }

    switch (align)
    {
    case 'c':
        addition = (place_size - src_size) / 2;
        break;
    case 'l':
        addition = 0;
        break;
    case 'r':
        addition = (place_size - src_size);
        break;
    default:
        break;
    }

    for (int i = 0; i < src_size; i++)
    {
        dest[i + addition + place] = src[i];
    }
}

void print_table(table_t *table)
{
    int *column_sizes = malloc(sizeof(int) * table->width);
    int line_size = 1;

    for (int i = 0; i < table->width; i++)
    {
        column_sizes[i] = max_content_size(table, i);
        line_size += column_sizes[i] + 1;
    }

    wchar_t *line = (wchar_t *)malloc(line_size * sizeof(wchar_t));

    put_string_aligned(line, table->title, line_size, 0, 'c');
    printf("%ls\n", line);

    int c_size;
    int i;
    for (i = 0; i < table->height; i++)
    {
        c_size = 0;
        for (int j = 0; j < table->width; j++)
        {
            bool *neighbors = get_cell_neighbors(table, j, i);

            if (j == 0)
            {
                if (i == 0)
                    line[0] = L'╔';
                else
                    line[0] = (!neighbors[0]) ? L'╟' : L'║';
                c_size++;
            }

            for (int k = 0; k < column_sizes[j]; k++)
            {
                if (i == 0)
                    line[c_size] = L'═';
                else
                    line[c_size] = (!neighbors[0]) ? L'─' : L' ';

                c_size++;
            }
            if (j == table->width - 1)
            {
                if (i == 0)
                    line[line_size - 1] = L'╗';
                else
                    line[line_size - 1] = (!neighbors[0]) ? L'╢' : L'║';
            }
            else
            {
                if (i == 0)
                    line[c_size] = (!neighbors[1]) ? L'╤' : L'═';
                else
                {
                    if (neighbors[0] && neighbors[1])
                        line[c_size] = L' ';
                    else if (neighbors[1])
                        line[c_size] = L'┴';
                    else if (neighbors[0])
                        line[c_size] = L'├';
                    else if (get_cell_neighbors(table, j, i - 1)[1])
                        line[c_size] = L'┬';
                    else if (get_cell_neighbors(table, j + 1, i)[0])
                        line[c_size] = L'┤';
                    else
                        line[c_size] = L'┼';
                }
            }
            c_size++;
        }
        printf("%ls\n", line);

        c_size = 0;
        int grouped = 0;
        int grouped_start = 0;
        for (int j = 0; j < table->width; j++)
        {
            bool *neighbors = get_cell_neighbors(table, j, i);

            if (j == 0)
            {
                line[0] = L'║';
                c_size++;
            }

            if (!grouped)
                grouped_start = j;

            grouped += column_sizes[j];

            if (neighbors[1])
            {
                grouped++;
            }
            else
            {
                line[c_size] = L' ';
                c_size++;
                put_string_aligned(line, table->cells[i][grouped_start].text, grouped - 2, c_size, table->cells[i][grouped_start].h_align);
                c_size += grouped - 2;
                line[c_size] = L' ';
                c_size++;
                line[c_size] = (j == table->width - 1) ? L'║' : L'│';
                c_size++;

                grouped = 0;
            }
        }
        printf("%ls\n", line);
    }

    i = table->height - 1;
    c_size = 0;
    for (int j = 0; j < table->width; j++)
    {
        bool *neighbors = get_cell_neighbors(table, j, i);

        if (j == 0)
        {
            line[0] = L'╚';
            c_size++;
        }

        for (int k = 0; k < column_sizes[j]; k++)
        {
            line[c_size] = L'═';
            c_size++;
        }
        if (j == table->width - 1)
        {
            line[line_size - 1] = L'╝';
        }
        else
        {
            line[c_size] = (!neighbors[1]) ? L'╧' : L'═';
        }
        c_size++;
    }
    printf("%ls\n", line);
}

wchar_t *int_to_wide_string(int value)
{
    int len = 1;
    int temp = value;

    // Calculate the length of the integer
    while (temp >= 10)
    {
        temp /= 10;
        len++;
    }

    // Allocate memory for the wide string
    wchar_t *str = (wchar_t *)malloc((len + 1) * sizeof(wchar_t));

    // Check if memory allocation was successful
    if (str == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // Convert the int to a wide string
    swprintf(str, len + 1, L"%d", value);

    return str;
}

int main()
{
    setlocale(LC_ALL, "C.UTF-8");

    table_t table = create_table(7, 8);
    table.title = L"Перелік витрат за 1-е півріччя 2021 року";
    group_cells(&table, 0, 0, 1, 2);
    group_cells(&table, 1, 0, 6, 1);
    int n_categories = 6;
    wchar_t *categories[] = {
        L"Житло",
        L"Кредит",
        L"Харчування",
        L"Податки",
        L"Інші витрати",
        L"Усього витрат",
    };

    int n_months = 6;
    wchar_t *months[] = {
        L"Січень",
        L"Лютий",
        L"Березень",
        L"Квітень",
        L"Травень",
        L"Червень",
    };

    // Data
    int n = 6;
    int m = 6;
    int **data = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        data[i] = malloc(sizeof(int) * m);
    }

    // Fill data
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            data[i][j] = random_number(20, 100);
        }
    }
    for (int j = 0; j < m; j++)
    {
        int sum = 0;
        for (int i = 0; i < n - 1; i++)
        {
            sum += data[i][j];
        }

        data[n - 1][j] = sum;
    }

    // Headers
    table.cells[0][0].text = L"Стаття";
    table.cells[1][0].text = L"витрат";
    table.cells[0][1].text = L"Місяць";

    for (int i = 0; i < n_categories; i++)
    {
        table.cells[2 + i][0].text = categories[i];
        table.cells[2 + i][0].h_align = 'l';
    }
    for (int i = 0; i < n_months; i++)
    {
        table.cells[1][1 + i].text = months[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            table.cells[2 + i][1 + j].text = int_to_wide_string(data[i][j]);
        }
    }

    print_table(&table);

    // Clear
    for (int i = 0; i < n; i++)
    {
        free(data[i]);
    }
    free(data);
    destroy_table(&table);
    return 0;
}
