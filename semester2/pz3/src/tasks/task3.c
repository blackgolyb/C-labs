#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void task3()
{
    char *buffer = (char*)malloc(sizeof(char) * 13);
    strcpy(buffer, "Omelnytskyi");
    printf("До %s\n", buffer);

    buffer = (char*)realloc(buffer, sizeof(char) * 33);
    strcpy(buffer, "Omelnytskyi Andrii Mykolaiovych");
    printf("Після %s\n", buffer);
}
