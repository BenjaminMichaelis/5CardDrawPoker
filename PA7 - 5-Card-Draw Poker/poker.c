#include "poker.h"

/* initialize suit array */
const char* g_suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

/* initialize face array */
const char* g_face[TOTAL_NUMBER_OF_FACES] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
    "Nine", "Ten", "Jack", "Queen", "King" };

/* initalize deck array */
int g_deckMultidimensionalArray[4][TOTAL_NUMBER_OF_FACES] = { 0 }; 

Card g_deck[TOTAL_NUMBER_OF_CARDS] = { 0 }; //deck of cards

//int cardCount[TOTAL_NUMBER_OF_FACES] = { 0 };

void game_controller(Hand player1Hand, Hand dealerHand)
{
    int cardCount[TOTAL_NUMBER_OF_FACES] = { 0 };
    int scorep1;
    int scorep2;
    shuffleDeck();
    deal(&player1Hand, &dealerHand);
    evaluateAndChangeDealersHand(&dealerHand, &cardCount);
    allowPlayerReplaceCards(&player1Hand);
    scorep1 = scoreHand(player1Hand, &cardCount);
    scorep2 = scoreHand(dealerHand, &cardCount);
    if (scorep1 < scorep2) //lowest score wins according to scoring in ScoreHand
    {
        printf("\nYou won the game!!\n");
    }
    if (scorep2 > scorep1) //lowest score wins
    {
        printf("\nThe computer won the game!!\n");
    }
    if (scorep1 == scorep2) // users tie (computer and player)
    {
        printf("\nYou have tied!!\n");
    }
    //printf("")

}


int runmenu() //display menu, return valid user inputted result
{
//TODO: implement do while loop in switch statement with default cases
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

int getint() //get an integer with scanf
{
    int number;
    scanf("%d", &number);
    return number;
}

char getChar() //get a character with scanf
{
    char character;
    scanf("%c", &character);
    return character;
}

void displayrules() //display rules on screen
{
    printf("Rules:\n");
    printf("Each player is dealt 5 cards that they can look at.\nYou will then have the opportunity to replace cards in your hand with new cards drawn\nthe player with the best hand will then win\n");
}

void swap(Card* a, Card* b) //switch one card with another for shuffling cards
{
    Card temp = *a;
    *a = *b;
    *b = temp;
}

Card* g_pNextCard;
int g_currentNextCardIndex; 
void shuffleDeck() //shuffles whole deck, deck is made up of the actual suits and faces (not just int like in starting code)
{
    g_currentNextCardIndex = 0;
    g_pNextCard = g_deck;
    int deckIndex = 0;
    for (int eachSuit = 0; eachSuit < TOTAL_NUMBER_OF_SUITS; eachSuit++)
    {
        for (int eachFaceCard = 0; eachFaceCard < TOTAL_NUMBER_OF_FACES; eachFaceCard++)
        {
            g_deck[deckIndex].suit_index = eachSuit; //
            g_deck[deckIndex].face_index = eachFaceCard;
            deckIndex++;
        }
    }

    for (int i = 0; i < TOTAL_NUMBER_OF_CARDS; i++) 
    {
        // Pick a random index from 0 to i  
        int j = rand() % (i + 1);

        // Swap arr[i] with the element  
        // at random index  
        swap(&g_deck[i], &g_deck[j]);
    }
}

Card pullNextCardFromDeck()
{
    // return the next card and increment the pointer.
    if (g_currentNextCardIndex++ > TOTAL_NUMBER_OF_CARDS)
    {
        perror("Invalid operation: Indexing off the end of the end of the deck.");
    }
    return *g_pNextCard++;
}

void deal(Hand* pPlayer1Hand, Hand* pPlayer2Hand) //deal 10 cards, 5 to each player
{
    for (int i = 0; i < NUMBER_OF_CARDS_IN_HAND; i++)
    {
        pPlayer1Hand->player_hand[i] = pullNextCardFromDeck();
        pPlayer2Hand->player_hand[i] = pullNextCardFromDeck();
    }
}

// This old starter (incomplete) code from the below authors sparked thoughts on how to approach this program.
// Authors: Deitel & Deitel - C How to Program
#ifdef OldCode
/* shuffle cards in deck */
void shuffle()
{
    int row = 0;    /* row number */
    int column = 0; /*column number */
    int card = 0;   /* card counter */

    /* for each of the 52 cards, choose slot of deck randomly */
    for (card = 1; card <= TOTAL_NUMBER_OF_CARDS; card++)
    {
        /* choose new random location until unoccupied slot found */
        do
        {
            row = rand() % TOTAL_NUMBER_OF_SUITS;
            column = rand() % TOTAL_NUMBER_OF_FACES;
        } while (g_deckMultidimensionalArray[row][column] != 0);

        /* place card number in chosen slot of deck */
        g_deckMultidimensionalArray[row][column] = card;
    }
}

int g_card = 0;
void dealOneCard(Hand hand, int indexToReplace)
{
    //int card = *cardPointer;
    int row = 0;    /* row number */
    int column = 0; /*column number */
    /* loop through rows of wDeck */
    for (row = 0; row < TOTAL_NUMBER_OF_SUITS; row++)
    {
        /* loop through columns of wDeck for current row */
        for (column = 0; column < TOTAL_NUMBER_OF_FACES; column++)
        {
            if (g_deckMultidimensionalArray[row][column] == g_card)
            {
                hand.player_hand[indexToReplace].face_index = column;
                hand.player_hand[indexToReplace].suit_index = row;
            }
        }
    }
    g_card++;
    //*cardPointer = card;
}

int getCardValue()
{
    return g_card;
}


/* deal cards in deck */
void deal(Hand p1_hand, Hand dealer_hand)
{
    int row = 0;    /* row number */
    int column = 0; /*column number */
    //card = *cardPointer;
    int cards_dealer = 0; //number of cards dealt dealer counter to keep track in array

    /* deals 2 hands worth of 5 cards each (5*2=10) */
    for (g_card = 1; g_card <= 10; g_card++)
    {
        /* loop through rows of wDeck */
        for (row = 0; row < TOTAL_NUMBER_OF_SUITS; row++)
        {
            /* loop through columns of wDeck for current row */
            for (column = 0; column < TOTAL_NUMBER_OF_FACES; column++)
            {
                /* if slot contains current card, deal card */
                if (g_deckMultidimensionalArray[row][column] == g_card && g_card <= NUMBER_OF_CARDS_IN_HAND)
                {
                    p1_hand.player_hand[g_card].face_index = column;
                    p1_hand.player_hand[g_card].suit_index = row;
                    printf("Card: %d: %5s of %-8s\n", g_card, g_face[column], g_suit[row]);
                    /*printf("%5s of %-8s%c", wFace[column], wSuit[row], card % 2 == 0 ? '\n' : '\t'); //print every card in deck if initialized properly with loops*/
                }
                else if (g_deckMultidimensionalArray[row][column] == g_card && g_card > NUMBER_OF_CARDS_IN_HAND)
                {
                    dealer_hand.player_hand[cards_dealer].face_index = column;
                    dealer_hand.player_hand[cards_dealer].suit_index = row;
                    cards_dealer++;
                }
            }
        }
    }
}
#endif OldCode


bool check_pair(Hand hand) 
{
    bool is_pair = false;
    int card = 0, card2 = 0; //pair =0
    for (card = 0; card < NUMBER_OF_CARDS_IN_HAND; card++)
    {
        for (card2 = 0; card2 < NUMBER_OF_CARDS_IN_HAND && card2 != card; card2++)
        {
            if (hand.player_hand[card].face_index == hand.player_hand[card2].face_index)
            {
                is_pair = true;
            }
        }
    }
    return is_pair;
}

bool checkTwoPairs(Hand hand, Card excludeCards[])  //
{
    bool is_pair = false, is_pair2 = false;
    int card = 0, card2 = 0, savecardpair1 = 0; //pair =0

    for (card = 0; card < NUMBER_OF_CARDS_IN_HAND; card++)
    {
        for (card2 = 0; card2 < NUMBER_OF_CARDS_IN_HAND && card2 != card; card2++) // doesn't equal the same card that the first pair was found with
        {
            if (hand.player_hand[card].face_index == hand.player_hand[card2].face_index &&
                hand.player_hand[savecardpair1].face_index != hand.player_hand[card].face_index)
            {
                is_pair2 = true;
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

int getMaxElementInArray(int array[], int arraySize) //get the highest number in array
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
int getMaxNumberSameCard(Hand hand, int* cardCountArrayToScoreHand[]) //count how many of each card there are and place in corrilated spot in array
{
    int cardCount[TOTAL_NUMBER_OF_FACES] = { 0 };

    for (int i = 0; i < NUMBER_OF_CARDS_IN_HAND; i++)
    {
        cardCount[hand.player_hand[i].face_index]++;
    }
    for (int k = 0; k < TOTAL_NUMBER_OF_FACES; k++)
    {
        cardCountArrayToScoreHand[k] = cardCount[k];
    }
    return getMaxElementInArray(cardCount, TOTAL_NUMBER_OF_FACES);
}

//TODO: check address for indexForRejectedCards in lines 160 and 179
int scoreHand(Hand hand, int* cardCount[]) //return score for 
{

    int maxSameCard = getMaxNumberSameCard(hand, cardCount);
    int score;
    switch (maxSameCard)
    {
    case 4:  //four of a kind
        score = ScoreValueFourOfAKind;
        break;
    case 3: //three of a kind
        score = ScoreValueThreeOfAKind;
        break;
    case 2: // at least one pair
        if (checkTwoPair(cardCount))// two pair
        {
            score = ScoreValueTwoPair;
            break;
        }
        else //pair
        {
            score = ScoreValuePair;
            break;
        }
    case 1:
        if (checkFlush(hand))
        {
            score = ScoreValueFlush;
            break;
        }
        else if (checkStraight(hand))
        {
            score = ScoreValueStraight;
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

void evaluateAndChangeDealersHand(Hand* pPlayer2Hand, int* cardCount) //evaluate quality of dealers hand and switch out cards from deck to try and obtain better score
{
    int score = scoreHand(*pPlayer2Hand, cardCount);
    int index = -1, index2 = -1, tracker = 0;
    if (score == ScoreValueFourOfAKind) //lowest score is best (did it off of ranking of quality of hand, so because 4 of kind is the 3rd best had in poker, it gets 3 points, etc
    {
        return;
    }
    else if (score == ScoreValueFlush)
    {
        return;
    }
    else if (score == ScoreValueStraight)
    {
        return;
    }
    else if (score == ScoreValueThreeOfAKind)
    {
        for (int i = 0; i < 5; i++)
        {
            if (cardCount[i] == 3) 
            {
                index = i;
                break;
            }
        }
        for (int j = 0; j < 5; j++) // replace all cards except the 3 that are the same
        {
            if (pPlayer2Hand->player_hand[j].face_index != index)
            {
                pPlayer2Hand->player_hand[j] = pullNextCardFromDeck();
            }
        }
    }
    else if (score == ScoreValueTwoPair) //replace the one card that isn't in either of the two pairs
    {
            for (int i = 0; i < 5; i++)
            {
                if (cardCount[i] == 2)
                {
                    if (tracker == 0)
                    {
                        index = i;
                    }
                    else if (tracker == 1)
                    {
                        index2 = i;
                    }
                    tracker++;
                }
            }

        for (int j = 0; j < 5; j++)
        {
            if (pPlayer2Hand->player_hand[j].face_index != index || pPlayer2Hand->player_hand[j].face_index != index2) //replace card thats not in eithe of the 2 pairs
            {
                pPlayer2Hand->player_hand[j] = pullNextCardFromDeck();
            }
        }
    }
    else if (score == ScoreValuePair) //replace all cards not in pair
    {
        {
            for (int i = 0; i < 5; i++)
            {
                if (cardCount[i] == 2)
                {
                    index = i;
                    break;
                }
            }
            for (int j = 0; j < 5; j++)
            {
                if (pPlayer2Hand->player_hand[j].face_index != index)
                {
                    pPlayer2Hand->player_hand[j] = pullNextCardFromDeck();
                }
            }
        }
    }
}

void allowPlayerReplaceCards(Hand* pPlayer1Hand) // take in user input for cards to be replaced, and replace it from deck
{
    int numberCardsYouHaveReplaced = 0;
    char charinput;
    int replaceCard, column, row;
    for (int j = 0; j < 5; j++)
    {
        column = pPlayer1Hand->player_hand[j].face_index;
        row = pPlayer1Hand->player_hand[j].suit_index;
        printf("Card: %d: %5s of %-8s\n", j, g_face[column], g_suit[row]);
    }
    printf("Do you want to replace a card (Y or N)?\n");
    charinput = getchar();
    scanf("%c", &charinput);
    if (charinput == 'Y' || charinput == 'y')
    {
        for (int i = 0; i < 5 && (charinput == 'Y' || charinput == 'y'); i++)
        {
            do
            {
                printf("What card number do you want to replace?\n");
                replaceCard = getint();
            } while (replaceCard > 4 || replaceCard < 0);
            pPlayer1Hand->player_hand[replaceCard] = pullNextCardFromDeck(); //actually get next card from deck and replace card in hand with it
            printf("Do you want to replace another card (Y or N)?\n");
            getchar();
            charinput = getchar();
        }
    }
    else
    {
        return;
    }
}

bool checkStraight(Hand hand) //check if straight exists
{
    bubble_sort(&hand, NUMBER_OF_CARDS_IN_HAND);
    for (int i = 1; i < NUMBER_OF_CARDS_IN_HAND; i++)
    {
        if (hand.player_hand[i].face_index - 1 != hand.player_hand[i - 1].face_index)
        {
            return false;
        }
    }
    return true;
}

bool checkFlush(Hand hand) // check if flush (all same suit) exists
{
    for (int i = 1; i < NUMBER_OF_CARDS_IN_HAND; i++)
    {
        if (hand.player_hand[i].suit_index != hand.player_hand[i - 1].suit_index)
        {
            return false;
        }
    }
    return true;
}

void bubble_sort(Hand* hand, int num_items) //sort cards in hand to be in order
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

bool checkTwoPair(int * cardCount[]) //check if two pairs exist
{
    int numberOfPairs = 0;
    for (int i = 0; i < TOTAL_NUMBER_OF_FACES; i++)
    {
        if (cardCount[i] >= 2)
        {
            numberOfPairs++;
        }
    }
    if (numberOfPairs >= 2)
    {
        return true;
    }
    else
    {
    return false;
    }
}
