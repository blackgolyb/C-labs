#include "table.h"

Table *create_table(int width, int height)
{
    Table *table = malloc(sizeof(Table));
    table->title = L"";
    table->width = width;
    table->height = height;
    table->cells = malloc(sizeof(Cell *) * height);
    for (int i = 0; i < height; i++)
    {
        table->cells[i] = malloc(sizeof(Cell) * width);
        for (int j = 0; j < width; j++)
        {
            table->cells[i][j] = (Cell){'c', 'c', 0, L""};
        }
    }

    return table;
}

void destroy_table(Table *table)
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

void group_cells(Table *table, int x, int y, int width, int height)
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

bool *get_cell_neighbors(Table *table, int x, int y)
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

int max_content_size(Table *table, int column)
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

void print_table(Table *table)
{
#ifdef WIN32
#define PRINT_FUNC(str) wprintf(L"%ls\n", line);
    _setmode(_fileno(stdout), _O_U16TEXT);
#else
#define PRINT_FUNC(str) printf("%ls\n", line)
#endif

    int *column_sizes = malloc(sizeof(int) * table->width);
    int line_size = 1;

    for (int i = 0; i < table->width; i++)
    {
        column_sizes[i] = max_content_size(table, i);
        line_size += column_sizes[i] + 1;
    }

    wchar_t *line = (wchar_t *)malloc((line_size + 1) * sizeof(wchar_t));
    line[line_size] = L'\0';

    wchar_t *buffer;
    wchar_t delim[] = L"\n";
    wchar_t temp[wcslen(table->title) + 1];
    wcscpy(temp, table->title);

#ifdef WIN32
    wchar_t *title = wcstok(temp, delim);
#else
    wchar_t *title = wcstok(temp, delim, &buffer);
#endif

    while (title)
    {
        put_string_aligned(line, title, line_size, 0, 'c');
        PRINT_FUNC(line);

#ifdef WIN32
        title = wcstok(NULL, delim);
#else
        title = wcstok(NULL, delim, &buffer);
#endif
    }

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
                    else if (get_cell_neighbors(table, j, i - 1)[1] && neighbors[1])
                        line[c_size] = L'─';
                    else if (get_cell_neighbors(table, j + 1, i)[0] && neighbors[0])
                        line[c_size] = L'│';
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
        PRINT_FUNC(line);

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
        PRINT_FUNC(line);
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
    PRINT_FUNC(line);

#ifdef WIN32
    _setmode(_fileno(stdout), _O_TEXT);
#endif
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

wchar_t *string_to_wide_string(char *input_string)
{
    int n = strlen(input_string);

    wchar_t *result = malloc(sizeof(wchar_t) * (n + 1));
    swprintf(result, n + 1, L"%hs", input_string);

    return result;
}

wchar_t *float_to_wide_string(float input_string)
{
    int len = snprintf(NULL, 0, "%f", input_string);
    char *result = malloc(len + 1);
    snprintf(result, len + 1, "%f", input_string);

    return string_to_wide_string(result);
}
