#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

char chose_one_option_input(char *chooses);
void input_float(float *value_ptr, char *value_name);
void input_double(double *value_ptr, char *value_name);
void input_int(int *value_ptr, char *value_name);
void input_char(char *value_ptr, char *value_name);

#define input1(value_ptr) _Generic((value_ptr), \
    int *: input_int,                           \
    char *: input_char,                         \
    float *: input_float,                       \
    double *: input_double)(value_ptr, #value_ptr + 1)

#define input2(value_ptr, value_name) _Generic((value_ptr), \
    int *: input_int,                                       \
    char *: input_char,                                     \
    float *: input_float,                                   \
    double *: input_double)(value_ptr, value_name)

#define NARGS(...) NARGS_(__VA_ARGS__, 5, 4, 3, 2, 1, 0)
#define NARGS_(_5, _4, _3, _2, _1, N, ...) N

#define CONC(A, B) CONC_(A, B)
#define CONC_(A, B) A##B

#define input(...) CONC(input, NARGS(__VA_ARGS__))(__VA_ARGS__)

#endif // INPUT_H_INCLUDED
