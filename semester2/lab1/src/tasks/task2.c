#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include "hash_table.h"
#include "table.h"
#include "utils.h"

typedef struct Product
{
    char *name;
    int expenses;
    int profit;
} Product;

typedef struct Firm
{
    char *name;
    char *activity_type;
} Firm;

typedef struct BusinessActivity
{
    Firm firm;
    Product product;
    int sales_volume;
    int realization_cost;
} BusinessActivity;

typedef struct Strings
{
    char **strings;
    size_t n;
} Strings;

BusinessActivity generate_activity(Strings *firms, Strings *activities_types)
{
    BusinessActivity activity;
    activity.firm.activity_type = activities_types->strings[random_number(0, activities_types->n - 1)];
    activity.firm.name = firms->strings[random_number(0, firms->n - 1)];
    activity.product.name = generate_name(10);
    activity.product.expenses = random_number(5, 50);
    activity.product.profit = random_number(10, 100);
    activity.sales_volume = random_number(10000, 100000);
    activity.realization_cost = random_number(1000, 10000);

    return activity;
}

BusinessActivity *generate_activities(int n, Strings *firms, Strings *activities_types)
{
    BusinessActivity *activities = malloc(sizeof(BusinessActivity) * n);
    for (int i = 0; i < n; i++)
        activities[i] = generate_activity(firms, activities_types);

    return activities;
}

void print_activities(BusinessActivity *activities, int n)
{
    const int ho = 2; /* header offset in table */
    Table *table = create_table(8, n + ho);
    table->title = L"Господарські діяльності";
    group_cells(table, 0, 0, 1, 2);
    group_cells(table, 1, 0, 3, 1);
    group_cells(table, 6, 0, 2, 1);
    group_cells(table, 4, 0, 1, 2);
    group_cells(table, 5, 0, 1, 2);

    table->cells[1][0].text = L"№";
    table->cells[0][1].text = L"Товар";
    table->cells[0][4].text = L"Об'єм";
    table->cells[1][4].text = L"продажу";
    table->cells[0][5].text = L"Собівартість";
    table->cells[1][5].text = L"реалізованого товару";
    table->cells[0][6].text = L"Фірма";

    table->cells[1][1].text = L"Назва";
    table->cells[1][2].text = L"Видатки";
    table->cells[1][3].text = L"Чистий прибуток";

    table->cells[1][6].text = L"Найменування";
    table->cells[1][7].text = L"Вид діяльності";

    for (int i = 0; i < n; i++)
    {

        table->cells[i + ho][0].text = int_to_wide_string(i + 1);

        table->cells[i + ho][1].text = string_to_wide_string(activities[i].product.name);
        table->cells[i + ho][2].text = int_to_wide_string((activities + i)->product.expenses);
        table->cells[i + ho][3].text = int_to_wide_string((activities + i)->product.profit);

        table->cells[i + ho][4].text = int_to_wide_string((activities + i)->sales_volume);
        table->cells[i + ho][5].text = int_to_wide_string((activities + i)->realization_cost);

        table->cells[i + ho][6].text = string_to_wide_string((activities + i)->firm.name);
        table->cells[i + ho][7].text = string_to_wide_string((activities + i)->firm.activity_type);
    }

    print_table(table);
    destroy_table(table);
}

ht *print_activities_mean_profit(BusinessActivity *activities, int n)
{

    ht *activities_repeats = ht_create();
    ht *activities_mean_profit = ht_create();
    for (int i = 0; i < n; i++)
    {
        int *ht_value = ht_get(activities_repeats, activities[i].firm.activity_type);
        float *htp_value = ht_get(activities_mean_profit, activities[i].firm.activity_type);
        if (ht_value == NULL)
        {
            ht_value = (int *)malloc(sizeof(int));
            htp_value = (float *)malloc(sizeof(float));
            *ht_value = 0;
            *htp_value = 0.0;
            ht_set(activities_repeats, activities[i].firm.activity_type, ht_value);
            ht_set(activities_mean_profit, activities[i].firm.activity_type, htp_value);
        }

        *ht_value += 1;
        *htp_value += activities[i].product.profit;
    }

    const int ho = 1; /* header offset in table */
    Table *table = create_table(2, ht_length(activities_mean_profit) + ho);
    table->title = L"Вид діяльності та середній чистий прибуток";
    table->cells[0][0].text = L"Вид діяльності";
    table->cells[0][1].text = L"Середній чистий прибуток";

    int i = 0;
    hti it = ht_iterator(activities_mean_profit);
    while (ht_next(&it))
    {
        // Divide sum of profit by repeats of activities
        *(float *)it.value = *(float *)it.value / *(int *)ht_get(activities_repeats, it.key);

        table->cells[i + ho][0].text = string_to_wide_string(it.key);
        table->cells[i + ho][1].text = float_to_wide_string(*(float *)it.value);

        i++;
    }

    print_table(table);
    destroy_table(table);

    return activities_mean_profit;
}

void task2_service(BusinessActivity *activities, int n)
{
    print_activities(activities, n);

    ht *activities_mean_profit = print_activities_mean_profit(activities, n);

    char *worst_activity = NULL;
    hti it = ht_iterator(activities_mean_profit);
    while (ht_next(&it))
    {
        if (worst_activity == NULL || *(float *)ht_get(activities_mean_profit, worst_activity) >= *(float *)it.value)
            worst_activity = it.key;
    }

    printf(
        "\nНайнерентабельніший вид діяльності, виходячи з показників чистого прибутку: %s (%f)\n",
        worst_activity,
        *(float *)ht_get(activities_mean_profit, worst_activity));

    ht_destroy(activities_mean_profit);
}

int task2()
{
    setlocale(LC_ALL, "C.UTF-8");

    int n = 100;
    char *firms_r[] = {
        "Apple",
        "Google",
        "Microsoft",
        "Facebook",
        "Netflix",
        "Amazon",
    };
    char *activities_types_r[] = {
        "Consumer electronics",
        "Software and applications",
        "Streaming services",
        "Cloud computing",
        "Online advertising",
        "Physical retail stores",
        "E-commerce platforms",
        "Original content production",
        "Content licensing and distribution",
        "Search engine technology",
        "Virtual reality",
        "Artificial intelligence",
        "Social media platforms",
        "Messaging services",
        "Delivery services",
    };

    Strings firms = {firms_r, 6};
    Strings activities_types = {activities_types_r, 15};

    BusinessActivity *activities = generate_activities(n, &firms, &activities_types);

    task2_service(activities, n);

    free(activities);
}
