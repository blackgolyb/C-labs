#include <stdio.h>

unsigned char swap_adjacent_bits(unsigned char num) {
    return ((num & 0b10101010) >> 1) | ((num & 0b01010101) << 1);
}

void print_binary(unsigned char num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

void task1()
{
    char *file_name = "output.txt";
    int counts = 3;
    FILE *output_file;

    unsigned char input_num;

    output_file = fopen(file_name, "w");
    fclose(output_file);

    for (int i = 0; i < counts; i++)
    {
        do{
            printf("Введіть число від 138 до 225: ");
            scanf("%hhu", &input_num);

            if (input_num < 138 || input_num > 225) {
                printf("Число має бути в межах від 138 до 225.\n");
                continue;
            }

            break;
        } while(1);

        unsigned char result = swap_adjacent_bits(input_num);
        printf("Введено:\t%hhu\t= 0x%X = ", input_num, input_num);
        print_binary(input_num);
        putchar('\n');
        printf("Результат:\t%hhu\t= 0x%X = ", result, result);
        print_binary(result);
        putchar('\n');

        output_file = fopen(file_name, "a");
        fprintf(output_file, "Введене число: %hhu\n", input_num);
        fprintf(output_file, "Результат: %hhu\n", result);
        fclose(output_file);

        putchar('\n');
    }
    
    

    return 0;
}
