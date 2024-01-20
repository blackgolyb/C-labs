#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <wchar.h>

#define height 5
#define weight 5

typedef struct
{
    short **data;
    int w;
    int h;
} Array2d;

Array2d create_array(int w, int h)
{
    Array2d array = {NULL, w, h};
    array.data = malloc(h * sizeof(*array.data));
    for (int i = 0; i < h; i++)
    {
        array.data[i] = malloc(w * sizeof(array.data[0]));
    }

    return array;
}

void copy_data_from_array(Array2d array, int m, int n, short input_array[][n])
{
    for (int i = 0; i < array.h; i++)
    {
        for (int j = 0; j < array.w; j++)
        {
            array.data[i][j] = input_array[i][j];
        }
    }
}

void delete_array(Array2d array)
{
    for (int i = 0; i < array.h; i++)
    {
        free(array.data[i]);
    }
    free(array.data);
}

wchar_t *cross;
void init_cross()
{
    cross = malloc(9 * 9 * sizeof(wchar_t));

    cross[0] = L' ';

    cross[70] = L'╫';
    cross[50] = L'╪';

    cross[80] = L'╬';
    cross[26] = L'╦';
    cross[62] = L'╣';
    cross[74] = L'╩';
    cross[78] = L'╠';

    cross[40] = L'┼';
    cross[13] = L'┬';
    cross[31] = L'┤';
    cross[37] = L'┴';
    cross[39] = L'├';

    cross[23] = L'╤';
    cross[61] = L'╢';
    cross[47] = L'╧';
    cross[69] = L'╟';

    cross[16] = L'╥';
    cross[32] = L'╡';
    cross[64] = L'╨';
    cross[48] = L'╞';

    cross[20] = L'═';
    cross[60] = L'║';
    cross[10] = L'─';
    cross[30] = L'│';

    cross[36] = L'└';
    cross[12] = L'┌';
    cross[4] = L'┐';
    cross[28] = L'┘';

    cross[72] = L'╚';
    cross[24] = L'╔';
    cross[8] = L'╗';
    cross[56] = L'╝';

    cross[63] = L'╙';
    cross[21] = L'╒';
    cross[7] = L'╖';
    cross[29] = L'╛';

    cross[45] = L'╘';
    cross[15] = L'╓';
    cross[5] = L'╕';
    cross[55] = L'╜';
}

wchar_t get_cross(short top, short right, short bottom, short left)
{
    const short neighbors = (27 * top) + (9 * right) + (3 * bottom) + left;
    return cross[neighbors];
}

wchar_t get_borders_h(short value)
{
    if (value == 1)
    {
        return L'─';
    }
    if (value == 2)
    {
        return L'═';
    }
    return L' ';
}

wchar_t get_borders_v(short value)
{
    if (value == 1)
    {
        return L'│';
    }
    if (value == 2)
    {
        return L'║';
    }
    return L' ';
}

void print_figure(Array2d horizontals, Array2d verticals, int h_size, int v_size)
{
    wchar_t *line = (wchar_t *)malloc((horizontals.w * (h_size + 1) + 1) * sizeof(wchar_t));
    wchar_t *line_vertical_elements = (wchar_t *)malloc((horizontals.w * (h_size + 1) + 1) * sizeof(wchar_t));

    int w = horizontals.h;
    int h = verticals.h;
    short top, bottom, left, right;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            top = (i - 1 >= 0) ? verticals.data[j][i - 1] : 0;
            bottom = (i < w - 1) ? verticals.data[j][i] : 0;

            left = (j - 1 >= 0) ? horizontals.data[i][j - 1] : 0;
            right = (j < h - 1) ? horizontals.data[i][j] : 0;

            wchar_t cross = get_cross(top, right, bottom, left);
            wchar_t elem = get_borders_h(right);

            line[j * (h_size + 1)] = cross;
            line_vertical_elements[j * (h_size + 1)] = get_borders_v(bottom);
            for (int k = 0; k < h_size && j < h - 1; k++)
            {
                line[j * (h_size + 1) + 1 + k] = elem;
                line_vertical_elements[j * (h_size + 1) + 1 + k] = L' ';
            }
        }
        printf("%ls\n", line);

        for (int k = 0; k < v_size && (i < h - 1); k++)
        {
            printf("%ls\n", line_vertical_elements);
        }
    }

    free(line);
    free(line_vertical_elements);
}

int main()
{
    setlocale(LC_ALL, "C.UTF-8");
    init_cross();

    Array2d horizontals = create_array(weight - 1, height);
    Array2d verticals = create_array(height - 1, weight);

    short h[height][weight - 1] = {
        {2, 2, 2, 2},
        {2, 2, 2, 2},
        {0, 2, 2, 2},
        {0, 0, 2, 2},
        {2, 2, 2, 0},
    };

    short v[weight][height - 1] = {
        {1, 1, 1, 1},
        {0, 1, 1, 1},
        {0, 0, 2, 2},
        {0, 0, 0, 1},
        {1, 1, 1, 0},
    };

    copy_data_from_array(horizontals, height, weight - 1, h);
    copy_data_from_array(verticals, weight, height - 1, v);

    print_figure(horizontals, verticals, 15, 6);

    delete_array(horizontals);
    delete_array(verticals);
    return 0;
}
