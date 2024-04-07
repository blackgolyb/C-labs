#include <stdio.h>


#define AUTHOR "Омельніцький А.М."
#define GROUP "КН-1023б"
#define PRINT_INFO() printf("Author: %s, Group: %s\n", AUTHOR, GROUP)


int task3() {
    PRINT_INFO();
    printf("Дата компіляції: %s\n", __DATE__);
    printf("Файл: %s\n", __FILE__);
    printf("Лінія коду: %d\n", __LINE__);

#ifdef __STDC__
    printf("Стандарт C підтримується.\n");
#else
    printf("Стандарт C не підтримується.\n");
#endif

#ifdef __STDC_HOSTED__
    printf("Код виконується в хостовому середовищі.\n");
#else
    printf("Код виконується воношовому середовищі.\n");
#endif

#ifdef __STDC_VERSION__
    printf("Версія стандарту C: %ld\n", __STDC_VERSION__);
#else
    printf("Стандарт C не підтримується.\n");
#endif

    printf("Час компіляції: %s\n", __TIME__);
    printf("Функція: %s\n", __func__);

    return 0;
}
