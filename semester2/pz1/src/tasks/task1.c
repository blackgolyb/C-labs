#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include "table.h"
#include "task_manager.h"
#include "linked_list.h"

typedef struct Date
{
    int year;
    int month;
    int day;
} Date;

typedef struct Employee
{
    char *name;
    char *position;
    char *office;
    int age;
    Date start_date;
} Employee;

const char *get_field(char *line, int num, const char *delim)
{
    int n = strlen(line);
    char *tmp = (char *)malloc(sizeof(char) * (n + 1));
    tmp[n] = '\0';
    strcpy(tmp, line);

    const char *tok;
    for (tok = strtok(tmp, delim);
         tok && *tok;
         tok = strtok(NULL, delim))
    {
        if (!num--)
        {
            n = strlen(tok);
            char *res = (char *)malloc(sizeof(char) * (n + 1));
            res[n] = '\0';
            strcpy(res, tok);
            free(tmp);
            return res;
        }
    }
    free(tmp);
    return NULL;
}

float *get_float_field(char *line, int num, const char *delim)
{
    float *tmp = malloc(sizeof(float));
    *tmp = atof(get_field(line, num, delim));
    return tmp;
}

int *get_int_field(char *line, int num, const char *delim)
{
    int *tmp = malloc(sizeof(int));
    *tmp = atoi(get_field(line, num, delim));
    return tmp;
}

long int *get_long_int_field(char *line, int num, const char *delim)
{
    long int *tmp = malloc(sizeof(long int));
    *tmp = atol(get_field(line, num, delim));
    return tmp;
}

long long int *get_long_long_int_field(char *line, int num, const char *delim)
{
    long long int *tmp = malloc(sizeof(long long int));
    *tmp = atoll(get_field(line, num, delim));
    return tmp;
}

Date parse_date(char *line, const char *delim)
{
    int *day = get_int_field(line, 0, delim);
    int *month = get_int_field(line, 1, delim);
    int *year = get_int_field(line, 2, delim);
    Date res = {*year, *month, *day};
    free(year);
    free(month);
    free(day);
    return res;
}

void print_employees(List *employees)
{
    int n = ll_len(employees);
    const int ho = 2; /* header offset in table */

    Table *table = create_table(8, n + ho);
    for (int i = 0; i < 5; i++)
        group_cells(table, i, 0, 1, 2);
    group_cells(table, 5, 0, 3, 1);

    // Headers
    table->cells[1][0].text = L"№";
    table->cells[0][1].text = L"Name";
    table->cells[0][2].text = L"Position";
    table->cells[0][3].text = L"Office";
    table->cells[0][4].text = L"Age";
    table->cells[0][5].text = L"Start date";
    table->cells[1][5].text = L"Day";
    table->cells[1][6].text = L"Month";
    table->cells[1][7].text = L"Year";

    for (int i = 0; i < n; i++)
    {
        Employee *employee = (Employee *)ll_get(employees, i);

        table->cells[i + ho][0].text = int_to_wide_string(i + 1);
        table->cells[i + ho][1].text = string_to_wide_string(employee->name);
        table->cells[i + ho][2].text = string_to_wide_string(employee->position);
        table->cells[i + ho][3].text = string_to_wide_string(employee->office);
        table->cells[i + ho][4].text = int_to_wide_string(employee->age);
        table->cells[i + ho][5].text = int_to_wide_string(employee->start_date.day);
        table->cells[i + ho][6].text = int_to_wide_string(employee->start_date.month);
        table->cells[i + ho][7].text = int_to_wide_string(employee->start_date.year);

        for (int j = 0; j < 5; j++)
            table->cells[i + ho][j].h_align = "r";
    }

    print_table(table);
    destroy_table(table);
}

Employee *input_employee()
{
    Employee *employee = (Employee *)malloc(sizeof(Employee));
    const int field_size = 30;
    employee->name = malloc(sizeof(char) * field_size);
    employee->position = malloc(sizeof(char) * field_size);
    employee->office = malloc(sizeof(char) * field_size);

    printf("Name: ");
    scanf("%s", employee->name);
    printf("Position: ");
    scanf("%s", employee->position);
    printf("Office: ");
    scanf("%s", employee->office);
    printf("Age: ");
    scanf("%d", &employee->age);
    printf("Start date: ");
    scanf("%d.%d.%d", &employee->start_date.day, &employee->start_date.month, &employee->start_date.year);

    return employee;
}

void add_employee(Employee *employees)
{
    int idx;
    printf("Index: ");
    scanf("%d", &idx);

    Employee *employee = input_employee();
    ll_insert(employees, idx - 1, employee);
}

int count_age_by_month(List *employees, int month)
{
    int n = ll_len(employees);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        Employee *employee = (Employee *)ll_get(employees, i);
        if (employee->start_date.month == month)
            sum += employee->age;
    }
    return sum;
}

bool compare_date(Date *d1, Date *d2)
{
    if (d1->year != d2->year)
        return d1->year > d2->year;

    if (d1->month != d2->month)
        return d1->month > d2->month;

    if (d1->day != d2->day)
        return d1->day > d2->day;

    return false;
}

void sort_employees_by_date(List *employees, bool direction)
{
    int n = ll_len(employees);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            Employee *e1 = ll_get(employees, j);
            Employee *e2 = ll_get(employees, j + 1);
            bool cmp;

            if (direction == 0)
                cmp = compare_date(&e1->start_date, &e2->start_date);
            else
                cmp = compare_date(&e2->start_date, &e1->start_date);

            if (cmp)
            {
                void *temp = e1;
                ll_set(employees, j, e2);
                ll_set(employees, j + 1, temp);
            }
        }
    }
}

List *employees;
const char *input_file_path = "input.csv";
const char *output_file_path = "output.csv";
const char *delim = ";";

void app_load_from_file()
{
    FILE *input_file;

    input_file = fopen(input_file_path, "r");

    if (input_file == NULL)
    {
        puts("Error opening file");
        int err;
        scanf("%d", err);
        exit(-1);
    }

    ll_clear(employees);

    // Read CSV file
    char line[1024];
    while (fgets(line, 1024, input_file))
    {
        Employee *employee = (Employee *)malloc(sizeof(Employee));

        employee->name = get_field(line, /* field index: */ 0, delim);
        employee->position = get_field(line, /* field index: */ 1, delim);
        employee->office = get_field(line, /* field index: */ 2, delim);
        employee->age = *get_int_field(line, /* field index: */ 3, delim);
        char *raw_date = get_field(line, /* field index: */ 4, delim);
        employee->start_date = parse_date(raw_date, ".");
        free(raw_date);
        ll_push_back(employees, employee);
    }
    fclose(input_file);

    puts("Loaded successfully!");
}

void app_save_to_file()
{
    FILE *output_file;

    output_file = fopen(output_file_path, "w");

    if (output_file == NULL)
    {
        puts("Error opening file");
        exit(-1);
    }

    for (int i = 0; i < ll_len(employees); i++)
    {
        Employee *employee = (Employee *)ll_get(employees, i);
        fprintf(
            output_file,
            "%s;%s;%s;%d;%d.%d.%d\n",
            employee->name,
            employee->position,
            employee->office,
            employee->age,
            employee->start_date.day,
            employee->start_date.month,
            employee->start_date.year);
    }
    fclose(output_file);

    puts("Saved successfully!");
}

void app_remove_employee()
{
    int idx = -1;
    int n = ll_len(employees);
    do
    {
        printf("Index: ");
        scanf("%d", &idx);

        if (idx >= 1 && idx <= n)
            break;

        printf("Incorrect index (%d). Index must be in [1, %d]\n", idx, n);
    } while (1);

    Employee *employee = (Employee *)ll_pop(employees, idx - 1);
    free(employee->name);
    free(employee->position);
    free(employee->office);
    free(employee);
}

void app_add_employee()
{
    add_employee(employees);
}

void app_print_employees()
{
    print_employees(employees);
}

void app_count_age_by_month()
{
    int accumulate_age = count_age_by_month(employees, 9);
    printf("Сумарний вік осіб, які почали працювати у вересні = %d\n", accumulate_age);
}

void app_sort_employees_by_date()
{
    int direction;
    do
    {
        printf("Введіть нарвавлення сортування за зростанням / за спаданням [0/1]: ");
        scanf("%d", &direction);
    } while (direction != 0 && direction != 1);

    sort_employees_by_date(employees, direction);
}

void task1()
{
    setlocale(LC_ALL, "C.UTF-8");

    employees = ll_create(sizeof(Employee *));

    struct TaskList task_list = {NULL, 0};

    register_task(&task_list, app_load_from_file, 1, "Завантажити список співробітників з файла");
    register_task(&task_list, app_save_to_file, 2, "Зберегти список співробітників до файлу");
    register_task(&task_list, app_print_employees, 3, "Вивести список співробітників");
    register_task(&task_list, app_remove_employee, 4, "Прибрати співробітника");
    register_task(&task_list, app_add_employee, 5, "Додати співробітника");
    register_task(&task_list, app_count_age_by_month, 6, "Підррвхувати умарний вік осіб, які почали працювати у вересні");
    register_task(&task_list, app_sort_employees_by_date, 7, "Вісортувати список за датою найму");

    run_task_manager(&task_list);

    // Clear
    for (int i = 0; i < ll_len(employees); i++)
    {
        Employee *employee = (Employee *)ll_get(employees, i);
        free(employee->name);
        free(employee->position);
        free(employee->office);
    }

    ll_destroy(employees);

    return 0;
}
