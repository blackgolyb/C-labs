#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>

#include "table.h"

int random_number(int start, int stop)
{
    return (rand() % (stop - start + 1)) + start;
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
