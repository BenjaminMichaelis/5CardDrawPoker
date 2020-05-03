#include "poker.h"

void game_controller(const int deck[][FACES], const char* face[], const char* suit[], Hand p1_hand, Hand dealer_hand)
{
    int indexForRejectedCards[3] = { 5,6,8 };
    shuffle(deck);
    deal(deck, face, suit, p1_hand, dealer_hand);
    //p1pair = check_pair(p1_hand);
    //p12pairs = checkTwoPairs(p1_hand);
    scoreHand(p1_hand);
}

int runmenu()
{
    int menu_input = 0;
    do {
        printf("\nMAIN MENU\n");
        printf("1. Print game rules\n");
        printf("2. Start a game of Poker\n");
        printf("3. Exit\n");
        menu_input = getint();
    } while (menu_input < 1 && menu_input > 3);
    return menu_input;
}

int getint()
{
    int number;
    scanf("%d", &number);
    return number;
}

void displayrules()
{
    printf("Rules:\n");
    printf("Each player is dealt 5 cards that they can look at.\nYou will then have the opportunity to replace cards in your hand with new cards drawn\nthe player with the best hand will then win\n");
}

/* shuffle cards in deck */
void shuffle(int wDeck[][FACES])
{
    int row = 0;    /* row number */
    int column = 0; /*column number */
    int card = 0;   /* card counter */

    /* for each of the 52 cards, choose slot of deck randomly */
    for (card = 1; card <= CARDS; card++)
    {
        /* choose new random location until unoccupied slot found */
        do
        {
            row = rand() % SUITS;
            column = rand() % FACES;
        } while (wDeck[row][column] != 0);

        /* place card number in chosen slot of deck */
        wDeck[row][column] = card;
    }
}

/* deal cards in deck */
void deal(const int wDeck[][FACES], const char* wFace[], const char* wSuit[], Hand p1_hand, Hand dealer_hand)
{
    int row = 0;    /* row number */
    int column = 0; /*column number */
    int card = 0;   /* card counter */
    int cards_dealer = 0; //number of cards dealt dealer counter to keep track in array

    /* deals 2 hands worth of 5 cards each (5*2=10) */
    for (card = 1; card <= 10; card++)
    {
        /* loop through rows of wDeck */
        for (row = 0; row < SUITS; row++)
        {
            /* loop through columns of wDeck for current row */
            for (column = 0; column < FACES; column++)
            {
                /* if slot contains current card, deal card */
                if (wDeck[row][column] == card && card <= 5)
                {
                    p1_hand.player_hand[card].face_index = column;
                    p1_hand.player_hand[card].suit_index = row;
                    printf("Card: %d: %5s of %-8s\n", card, wFace[column], wSuit[row]);
                    /*printf("%5s of %-8s%c", wFace[column], wSuit[row], card % 2 == 0 ? '\n' : '\t'); //print every card in deck if initialized properly with loops*/
                }
                else if (wDeck[row][column] == card && card > 5)
                {
                    dealer_hand.player_hand[cards_dealer].face_index = column;
                    dealer_hand.player_hand[cards_dealer].suit_index = row;
                    cards_dealer++;
                }
            }
        }
    }
}

bool check_pair(Hand hand)
{
    bool is_pair = false;
    int card = 0, card2 = 0; //pair =0
    for (card = 0; card < 5; card++)
    {
        for (card2 = 0; card2 < 5 && card2 != card; card2++)
        {
            if (hand.player_hand[card].face_index == hand.player_hand[card2].face_index)
            {
                is_pair = true;
            }
        }
    }
    return is_pair;
}

bool checkTwoPairs(Hand hand, Card excludeCards[])
{
    bool is_pair = false, is_pair2 = false;
    int card = 0, card2 = 0, savecardpair1 = 0; //pair =0

    for (card = 0; card < 5; card++)
    {
        for (card2 = 0; card2 < 5 && card2 != card; card2++)
        {
            if (hand.player_hand[card].face_index == hand.player_hand[card2].face_index &&
                hand.player_hand[savecardpair1].face_index != hand.player_hand[card].face_index)
            {
                /*if (is_pair == true)
                {*/
                is_pair2 = true;
                /* }*/
            }
        }
    }
    return (is_pair && is_pair2);
}

//int getSizeIntOfArray(int array[])
//{
//    int first = sizeof(array);
//    int second = sizeof(array[0]);
//    return first / second;
//}
int getMaxElementInArray(int array[], int arraySize)
{
    int maximum = array[0];
    int arraysize = 0;

    // TODO: Calculate array size/
    for (int c = 1; c < arraySize; c++)
    {
        if (array[c] > maximum)
        {
            maximum = array[c];
        }
    }
    return maximum;
}

// Rename to ScoreHand(...)
int getMaxNumberSameCard(Hand hand, int* cardCountArrayToScoreHand)
{
    /*printf("%d,%d,%d", indexForRejectedCards[0], indexForRejectedCards[1], indexForRejectedCards[2]);*/
    int cardCount[13] = { 0 };

    for (int i = 0; i < 5; i++)
    {
        cardCount[hand.player_hand[i].face_index]++;
    }
    for (int k = 0; k < 13; k++)
    {
        cardCountArrayToScoreHand[k] = cardCount[k];
    }
    return getMaxElementInArray(cardCount, 13);
}
//TODO: check address for indexForRejectedCards in lines 160 and 179
int scoreHand(Hand hand)
{
    int cardCount[13];
    int maxSameCard = getMaxNumberSameCard(hand, cardCount);
    int score;
    switch (maxSameCard)
    {
    case 4:
        score = 3;
        break;
    case 3:
        score = ScoreValueThreeOfAKind;
        break;
    case 2:
        // TODO Check for two pair.
        if (false)
        {
            score = 8;
            break;
        }
        else //pair
        {
            score = ScoreValuePair;
            break;
        }
    case 1:
        if (checkStraight(hand))
        {
            score = 8;
            break;
        }
        else
        {
            score = 10;
            break;
        }
    default:
        // TODO: Write there is an error in the logic
        score = INT_MAX;
        break;
    }

    return score;
}


bool checkStraight(Hand hand)
{
    bubble_sort(&hand, 5);
    for (int i = 1; i < 5; i++)
    {
        if (hand.player_hand[i].face_index - 1 != hand.player_hand[i - 1].face_index)
        {
            return false;
        }
    }
    return true;
}

void bubble_sort(Hand* hand, int num_items)
{
    int passes = 0, temp = 0, index = 0;

    for (passes = 1; passes < num_items; ++passes)
    {
        for (index = 0; index < num_items - passes; ++index)
        {
            if (hand->player_hand[index].face_index > hand->player_hand[index + 1].face_index)
            {
                //swap
                temp = hand->player_hand[index].face_index;
                hand->player_hand[index].face_index = hand->player_hand[index + 1].face_index;
                hand->player_hand[index + 1].face_index = temp;
            }
        }
    }
}