#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include "hash_table.h"
#include "table.h"
#include "utils.h"

struct Date
{
    int day;
    int month;
    int year;
};

typedef struct Product
{
    char *company_supplier;
    char *product_name;
    int price;
    int units_number;
    struct Date date;
    char *state_supplier;
} Product;

typedef struct Strings
{
    char **strings;
    size_t n;
} Strings;

Product generate_product(Strings *countries, Strings *companies, int year_span[2])
{
    Product product;
    product.company_supplier = companies->strings[random_number(0, companies->n - 1)];
    product.product_name = generate_name(random_number(4, 10));
    product.price = random_number(100, 1000);
    product.units_number = random_number(1, 10);
    product.date.day = random_number(1, 29);
    product.date.month = random_number(1, 12);
    product.date.year = random_number(year_span[0], year_span[1]);
    product.state_supplier = countries->strings[random_number(0, countries->n - 1)];

    return product;
}

Product *generate_products(int n, Strings *countries, Strings *companies, int year_span[2])
{
    Product *products = malloc(sizeof(Product) * n);
    for (int i = 0; i < n; i++)
        products[i] = generate_product(countries, companies, year_span);

    return products;
}

void print_products(Product *products, int n)
{
    const int ho = 2; /* header offset in table */
    Table *table = create_table(9, n + ho);
    table->title = L"Товари";

    for (int i = 0; i <= 4; i++)
        group_cells(table, i, 0, 1, 2);
    group_cells(table, 5, 0, 3, 1);
    group_cells(table, 8, 0, 1, 2);

    // Headers
    table->cells[1][0].text = L"№";
    table->cells[0][1].text = L"Фірма-";
    table->cells[1][1].text = L"постачальник";
    table->cells[0][2].text = L"Найменування";
    table->cells[1][2].text = L"товару";
    table->cells[0][3].text = L"Вартість";
    table->cells[0][4].text = L"Кількість";
    table->cells[1][4].text = L"одиниць товару";
    table->cells[0][5].text = L"Дата постачання";
    table->cells[1][5].text = L"День";
    table->cells[1][6].text = L"Місяць";
    table->cells[1][7].text = L"Рік";
    table->cells[0][8].text = L"Держава-";
    table->cells[1][8].text = L"постачальник";

    // Fill table with dat of the products
    for (int i = 0; i < n; i++)
    {
        table->cells[ho + i][0].text = int_to_wide_string(i + 1);

        table->cells[ho + i][1].text = string_to_wide_string(products[i].company_supplier);
        table->cells[ho + i][2].text = string_to_wide_string(products[i].product_name);

        table->cells[ho + i][3].text = int_to_wide_string(products[i].price);
        table->cells[ho + i][4].text = int_to_wide_string(products[i].units_number);

        // date
        table->cells[ho + i][5].text = int_to_wide_string(products[i].date.day);
        table->cells[ho + i][6].text = int_to_wide_string(products[i].date.month);
        table->cells[ho + i][7].text = int_to_wide_string(products[i].date.year);

        table->cells[ho + i][8].text = string_to_wide_string(products[i].state_supplier);
    }

    print_table(table);
    destroy_table(table);
}

ht *print_country_repeats(Product *products, int n)
{

    ht *countries_repeats = ht_create();
    for (int i = 0; i < n; i++)
    {
        int *ht_value = ht_get(countries_repeats, products[i].state_supplier);
        if (ht_value == NULL)
        {
            ht_value = (int *)malloc(sizeof(int));
            *ht_value = 0;
            ht_set(countries_repeats, products[i].state_supplier, ht_value);
        }

        *ht_value += 1;
    }

    const int ho = 1; /* header offset in table */
    Table *table = create_table(2, ht_length(countries_repeats) + ho);
    table->title = L"Держави та кількість їх товарів";
    table->cells[0][0].text = L" Держава ";
    table->cells[0][1].text = L"Кількість товарів";

    int i = 0;
    hti it = ht_iterator(countries_repeats);
    while (ht_next(&it))
    {
        table->cells[i+ho][0].text = string_to_wide_string(it.key);
        table->cells[i+ho][1].text = int_to_wide_string(*(int *)it.value);
        i++;
    }

    print_table(table);
    destroy_table(table);

    return countries_repeats;
}

void filter_products_by_year(Product *products, int n, Product *filtered_products, int *filtered_n, int year_span[2])
{
    *filtered_n = 0;
    for (int i = 0; i < n; i++)
    {
        if (products[i].date.year < year_span[0] || products[i].date.year > year_span[1])
            continue;

        memcpy(&filtered_products[*filtered_n], &products[i], sizeof(Product));
        (*filtered_n)++;
    }
}

void task1_service(Product *products, int n)
{
    /* Filtering products by year of production [2019, 2020] */
    int filtered_n = 0;
    Product *filtered_products = malloc(sizeof(Product) * n);
    filter_products_by_year(products, n, filtered_products, &filtered_n, (int[2]){2019, 2020});

    print_products(filtered_products, filtered_n);

    putc('\n', stdout);

    ht *countries_repeats = print_country_repeats(filtered_products, filtered_n);

    // Search for the country that produced the most products
    char *best_country = NULL;
    hti it = ht_iterator(countries_repeats);
    while (ht_next(&it))
    {
        if (best_country == NULL || *(int *)ht_get(countries_repeats, best_country) <= *(int *)it.value)
            best_country = it.key;
    }

    printf("\nНайбільш розповсюджена країна постачальник: %s (%d)\n", best_country, *(int *)ht_get(countries_repeats, best_country));

    ht_destroy(countries_repeats);
    free(filtered_products);
}

void task1()
{
    setlocale(LC_ALL, "C.UTF-8");

    // Configurations
    int n = 100;
    char *countries_r[] = {
        "USA",
        "Ukraine",
        "China",
        "Japan",
        "Germany",
        "France",
    };
    char *companies_r[] = {
        "Apple",
        "Google",
        "Microsoft",
        "Facebook",
        "Amazon",
    };
    Strings countries = {countries_r, 6};
    Strings companies = {companies_r, 5};

    int year_span[2] = {2008, 2024};

    // Generate a list of products
    Product *products = generate_products(n, &countries, &companies, year_span);

    task1_service(products, n);

    // Clear
    free(products);
}
