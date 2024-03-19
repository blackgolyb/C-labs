#include <stdio.h>
#include <stdbool.h> // C99, визначення bool, true, false

struct Card
{
    enum
    {
        SPADES,
        CLUBS,
        DIAMONDS,
        HEARTS
    } suit;
    enum
    {
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE
    } value;
} c1, c2;

int cs; // Козирна карта
bool result;

// Функція перевіряє чи б'є карта 1 карту 2
bool Kick(struct Card c1, struct Card c2, int cs)
{
    if (c1.suit == c2.suit) // Якщо масті однакові
        if (c1.value > c2.value)
            return true;
        else
            return false;
    else // Якщо масті не однакові
        if (c1.suit == cs) // Якщо це козирна карта
            return true;
        else
            return false;
}
void Message(struct Card c)
{
    switch (c.value)
    {
    case SIX:
        printf("6 ");
        break;
    case SEVEN:
        printf("7 ");
        break;
    case EIGHT:
        printf("8 ");
        break;
    case NINE:
        printf("9 ");
        break;
    case TEN:
        printf("10 ");
        break;
    case JACK:
        printf("валет ");
        break;
    case QUEEN:
        printf("дама ");
        break;
    case KING:
        printf("король ");
        break;
    case ACE:
        printf("туз ");
        break;
    default:
        break;
    }
    switch (c.suit)
    {
    case SPADES:
        printf("пік");
        break;
    case CLUBS:
        printf("треф");
        break;
    case DIAMONDS:
        printf("бубей");
        break;
    case HEARTS:
        printf("чірва");
        break;
    default:
        break;
    }
}
void trump_card(int cs)
{
    printf("Козирна масть: ");
    switch (cs)
    {
    case 0:
        printf("піки");
        break;
    case 1:
        printf("трефи");
        break;
    case 2:
        printf("бубни");
        break;
    case 3:
        printf("чирви");
        break;
    default:
        break;
    }
    printf("\n");
}

void kick_message(struct Card c1, struct Card c2, int cs)
{
    result = Kick(c1, c2, cs);
    trump_card(cs);
    Message(c1);
    if (result)
        printf(" б'є ");
    else
        printf(" не б'є ");
    Message(c2);
}

int task3(void)
{
    cs = CLUBS;

    c1.suit = DIAMONDS;
    c1.value = ACE;
    c2.suit = CLUBS;
    c2.value = SIX;
    kick_message(c1, c2, cs);
    printf("\n============================================\n");
    
    c1.suit = DIAMONDS;
    c1.value = KING;
    c2.suit = DIAMONDS;
    c2.value = ACE;
    kick_message(c1, c2, cs);
    printf("\n============================================\n");

    c1.suit = HEARTS;
    c1.value = SEVEN;
    c2.suit = HEARTS;
    c2.value = EIGHT;
    kick_message(c1, c2, cs);
    printf("\n============================================\n");

    return 0;
}