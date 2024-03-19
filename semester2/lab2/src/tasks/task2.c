#include <stdio.h>

//=================================================================
// Перелічення констант, що являють собою номери годин
//=================================================================
enum Hours // визначення перелічення Hours
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    ELEVEN
};
int task2(void)
{
    printf("===============================================\n");
    printf("Значення констант перелічення за замовчуванням \n");
    printf("===============================================\n");
    printf(" ZERO = %2d", ZERO);
    printf(" ONE = %2d", ONE);
    printf(" TWO = %2d\n", TWO);
    printf(" THREE = %2d", THREE);
    printf(" FOUR = %2d", FOUR);
    printf(" FIVE = %2d\n", FIVE);
    printf(" SIX = %2d", SIX);
    printf(" SEVEN = %2d", SEVEN);
    printf(" EIGHT = %2d\n", EIGHT);
    printf(" NINE = %2d", NINE);
    printf(" TEN = %2d", TEN);
    printf(" ELEVEN = %2d\n", ELEVEN);
    printf("===============================================\n\n");
    enum Hours // визначення перелічення Hours
    {
        ZERO,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX = 10,
        SEVEN,
        EIGHT,
        NINE = 5,
        TEN,
        ELEVEN
    };
    printf("===============================================\n");
    printf("Змінюємо значення ( SIX = 10, NINE = 5 ) \n");
    printf("===============================================\n");
    printf(" ZERO = %2d", ZERO);
    printf(" ONE = %2d", ONE);
    printf(" TWO = %2d\n", TWO);
    printf(" THREE = %2d", THREE);
    printf(" FOUR = %2d", FOUR);
    printf(" FIVE = %2d\n", FIVE);
    printf(" SIX = %2d", SIX);
    printf(" SEVEN = %2d", SEVEN);
    printf(" EIGHT = %2d\n", EIGHT);
    printf(" NINE = %2d", NINE);
    printf(" TEN = %2d", TEN);
    printf(" ELEVEN = %2d\n", ELEVEN);
    printf("===============================================\n\n");
    enum Hours1 // визначення перелічення Hours1
    {
        ZERO1,
        ONE1,
        TWO1,
        THREE1,
        FOUR1 = 3,
        FIVE1,
        SIX1 = -7,
        SEVEN1,
        EIGHT1,
        NINE1,
        TEN1,
        ELEVEN1
    };
    printf("===============================================\n");
    printf("Змінюємо значення ( FOUR = 3, SIX = -7 ) \n");
    printf("===============================================\n");
    printf(" ZERO = %2d", ZERO1);
    printf(" ONE = %2d", ONE1);
    printf(" TWO = %2d\n", TWO1);
    printf(" THREE = %2d", THREE1);
    printf(" FOUR = %2d", FOUR1);
    printf(" FIVE = %2d\n", FIVE1);
    printf(" SIX = %2d", SIX1);
    printf(" SEVEN = %2d", SEVEN1);
    printf(" EIGHT = %2d\n", EIGHT1);
    printf(" NINE = %2d", NINE1);
    printf(" TEN = %2d", TEN1);
    printf(" ELEVEN = %2d\n", ELEVEN1);
    printf("===============================================\n\n");
    return 0;
}