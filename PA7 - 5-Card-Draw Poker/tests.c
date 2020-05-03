#include "tests.h"
#include "poker.h"


void Test_deal()
{
    printf("%d\n", getCardValue());
    const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

    /* initialize face array */
    const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Jack", "Queen", "King" };

    /* initalize deck array */
    int deck[4][13] = { 0 };
    /* card counter */
    int card = 0;
    Hand p1_hand = { 0 }; // - to initialize
    Hand dealer_hand = { 0 };

    deal(deck, face, suit, p1_hand, dealer_hand);
    card = getCardValue();
    AreIntEqual(11, card, "1. deal did not return expected value");
    printf("%d\n", getCardValue());
}

void Test_dealOneCard()
{
    const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

    /* initialize face array */
    const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Jack", "Queen", "King" };

    /* initalize deck array */
    int deck[4][13] = { 0 };
    int card = 11;   /* card counter */

    Hand p1_hand = { 0 }; // - to initialize


    dealOneCard(deck, face, suit, p1_hand, 3);
    card = getCardValue();
    AreIntEqual(12, card, "1. dealOneCard did not return expected value");
    p1_hand.player_hand[3].face_index = 3;
    dealOneCard(deck, face, suit, p1_hand, 3);
    card = getCardValue();
    AreIntNotEqual(3, p1_hand.player_hand[3].face_index, "2. dealOneCard did not return expected value");
    AreIntEqual(13, card, "3. dealOneCard did not return expected value");

}

void Test_getMaxNumberSameCard()
{
    Hand testHand = { 0 };
    int actualCountCards[13] = { 0 };
    
    int faceIndices[] = { 0,12,12,3,12 };
    setHand(&testHand, faceIndices, 5);

    resetArray(actualCountCards, 13);
    AreIntEqual(3, getMaxNumberSameCard(testHand, actualCountCards), "1. getMaxNumberSameCard did not return expected value");
    AreArraysEqual((int[]){ 1,0,0,1,0,0,0,0,0,0,0,0,3 }, actualCountCards, "4. getMaxNumberSameCard did not return expected value", 13);

    // {0, 12, 12, 0, 12 };
    testHand.player_hand[3].face_index = 0;
    resetArray(actualCountCards, 13);
    AreIntEqual(3, getMaxNumberSameCard(testHand, actualCountCards), "2. getMaxNumberSameCard did not return expected value");
    AreArraysEqual((int[]) { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 }, actualCountCards, "5. getMaxNumberSameCard did not return expected value", 13);

    // {0, 12, 4, 0, 12 };
    testHand.player_hand[2].face_index = 4;
    resetArray(actualCountCards, 13);
    AreIntEqual(2, getMaxNumberSameCard(testHand, actualCountCards), "3. getMaxNumberSameCard did not return expected value");
    AreArraysEqual((int[]) { 2,0,0,0,1,0,0,0,0,0,0,0,2 }, actualCountCards, "6. getMaxNumberSameCard did not return expected value", 13);
}

void setHand(Hand* pHand, int values[], int length)
{
    for (int i = 0; i < length; i++)
    {
        pHand->player_hand[i].face_index = values[i];
    }
}


void resetArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        array[i] = 0;
    }
}

void Test_scoreHand()
{
    int score;
    Hand testhand = { 0 };
    int indexForRejectedCards1[3] = { 5,6,8 };
    testhand.player_hand[0].face_index = 0;
    testhand.player_hand[1].face_index = 12;
    testhand.player_hand[2].face_index = 12;
    testhand.player_hand[3].face_index = 3;
    testhand.player_hand[4].face_index = 12;
    score = scoreHand(testhand);
    AreIntEqual(ScoreValueThreeOfAKind, score, "1. Returned score was unexpected");
    testhand.player_hand[4].face_index = 9;
    score = scoreHand(testhand);
    AreIntEqual(ScoreValuePair, score, "2. Returned score was unexpected");
    testhand.player_hand[4].face_index = 3;
    score = scoreHand(testhand);
    AreIntEqual(ScoreValueTwoPair, score, "3. Returned score was unexpected");
    testhand.player_hand[0].face_index = 0;
    testhand.player_hand[1].face_index = 1;
    testhand.player_hand[2].face_index = 2;
    testhand.player_hand[3].face_index = 3;
    testhand.player_hand[4].face_index = 4;
    testhand.player_hand[0].suit_index = 1;
    testhand.player_hand[1].suit_index = 1;
    testhand.player_hand[2].suit_index = 1;
    testhand.player_hand[3].suit_index = 1;
    testhand.player_hand[4].suit_index = 1;
    score = scoreHand(testhand);
    AreIntEqual(ScoreValueFlush, score, "4. Returned score was unexpected");
    testhand.player_hand[3].suit_index = 2;
    score = scoreHand(testhand);
    AreIntEqual(ScoreValueStraight, score, "5. Returned score was unexpected");
}

void Test_getMaxElementInArray()
{
    int testarray1[] = { 1,4,6,7,8 };
    AreIntEqual(8, getMaxElementInArray(testarray1, 5), " getMaxElementInArray did not return expected value");
    int testarray2[] = { 1,4,6,7,8,-12,0,42 };
    AreIntEqual(42, getMaxElementInArray(testarray2, 8), "getMaxElementInArray did not return expected value");
}

void AreArraysEqual(int expected[], int actual[], const char*  message, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (actual[i] != expected[i])
        {
            printf("Index: %d\t", i);
            printf("Actual: %d\t", actual[i]);
            printf("Expected: %d\t", expected[i]);
            // TODO: Append expected and actual to the message to you can read the problem in the output.
            print(message);
            printf("\n\n");
        }
    }
}


void AreIntEqual(int expected, int actual, const char*  message)
{
    if (actual != expected)
    {
        // TODO: Append expected and actual to the message to you can read the problem in the output.
        print(message);
        printf("\n");
    };
}

void AreIntNotEqual(int expected, int actual, const char* message)
{
    if (actual == expected)
    {
        // TODO: Append expected and actual to the message to you can read the problem in the output.
        print(message);
        printf("\n");
    };
}

void IsTrue(bool condition, const char*  message)
{
    if (!condition)
    {
        // TODO: Append expected and actual to the message to you can read the problem in the output.
        print(message);
        printf("\n");
    };
}


void Test_checkStraight()
{
    Hand testhand = { 0 };
    testhand.player_hand[0].face_index = 0;
    testhand.player_hand[1].face_index = 12;
    testhand.player_hand[2].face_index = 12;
    testhand.player_hand[3].face_index = 3;
    testhand.player_hand[4].face_index = 12;
    IsTrue(!checkStraight(testhand), "checkStraight Unexpectedly returned true");

    int i = 5;
    testhand.player_hand[0].face_index = i++;
    testhand.player_hand[1].face_index = i++;
    testhand.player_hand[2].face_index = i++;
    testhand.player_hand[3].face_index = i++;
    testhand.player_hand[4].face_index = i++;
    IsTrue(checkStraight(testhand), "checkStraight Unexpectedly returned true");
    
    testhand.player_hand[0].face_index = 8;
    testhand.player_hand[1].face_index = 5;
    testhand.player_hand[2].face_index = 6;
    testhand.player_hand[3].face_index = 9;
    testhand.player_hand[4].face_index = 7;
    IsTrue(checkStraight(testhand), "checkStraight Unexpectedly returned true");
}

void print(const char* message)
{
    printf(message);
}