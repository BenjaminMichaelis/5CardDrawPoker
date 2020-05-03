#include "tests.h"
#include "poker.h"

void runAllTests()
{
    Test_shuffleDeck();
    Test_deal();
    Test_scoreHand();
    Test_getMaxElementInArray();
    Test_getMaxNumberSameCard();
    Test_checkStraight();
}


void Test_shuffleDeck()
{
    Card deck[TOTAL_NUMBER_OF_CARDS] = { 0 };
    bool success;
    // If (by some miracle) they aren't shuffled, try again
    for (int i = 0; i < 4; i++)
    {
        shuffleDeck();
        for (int eachCardInDeck = 0; eachCardInDeck < TOTAL_NUMBER_OF_CARDS; eachCardInDeck++)
        {
            deck[eachCardInDeck] = pullNextCardFromDeck();
        }
        if (success = allItemsAreUniqueAndShuffled(deck, TOTAL_NUMBER_OF_CARDS))
        {
            break;
        }
    }
    if (!success)
    {
        printTestFailed("Unable to successfully shuffle the cards.");
    }
}



void Test_deal()
{
    bool success = false;
    shuffleDeck();
    Hand player1Hand = { 0 };
    Hand dealerHand = { 0 };

    // If (by some miracle) they aren't shuffled, try again
    for (int i = 0; i < 4; i++)
    {
        deal(&player1Hand, &dealerHand);
        if (success = (allItemsAreUniqueAndShuffled(player1Hand.player_hand, NUMBER_OF_CARDS_IN_HAND)
            && allItemsAreUniqueAndShuffled(dealerHand.player_hand, NUMBER_OF_CARDS_IN_HAND)))
        {
            break;
        }
    }
    if (!success)
    {
        printTestFailed("Unable to successsfully deal cards.");
    }
}

bool allItemsAreUniqueAndShuffled(Card* pDeck, int length)
{
    bool duplicateItemExists = false;
    int countFaceCardChangeByMoreThan1 = 0;
    int countSuitChanged = 0;
    int lastSuit = 0;
    int lastFaceCard = 0;
    char duplicateCardsMessage[1024 * 2] = { 0 };
    sprintf(duplicateCardsMessage, "%s", "There are duplicate items: ");
    for (int eachCardInDeck = 0; eachCardInDeck < length; eachCardInDeck++)
    {
        for (int i = 0; i < eachCardInDeck; i++)
        {
            if (i != eachCardInDeck)
            {
                if ((pDeck[i].suit_index == pDeck[eachCardInDeck].suit_index)
                    && (pDeck[i].face_index == pDeck[eachCardInDeck].face_index))
                {
                    sprintf(duplicateCardsMessage, "%s[%d][%d], ", duplicateCardsMessage, pDeck[eachCardInDeck].suit_index, pDeck[eachCardInDeck].face_index);
                    duplicateItemExists = true;
                    break;
                }
            }
        }
        if (lastSuit != pDeck[eachCardInDeck].suit_index)
        {
            countSuitChanged++;
        }
        if (lastFaceCard + 1 != pDeck[eachCardInDeck].face_index
            && lastFaceCard - 1 != pDeck[eachCardInDeck].face_index)
        {
            countFaceCardChangeByMoreThan1++;
        }
        lastSuit = pDeck[eachCardInDeck].suit_index;
        lastFaceCard = pDeck[eachCardInDeck].face_index;
    }
    AssertIsTrue(!duplicateItemExists, duplicateCardsMessage);

    return (countSuitChanged > length / TOTAL_NUMBER_OF_FACES || countFaceCardChangeByMoreThan1 > length / TOTAL_NUMBER_OF_SUITS);
}

void Test_getMaxNumberSameCard()
{
    Hand testHand = { 0 };
    int actualCountCards[TOTAL_NUMBER_OF_FACES] = { 0 };

    setHand(&testHand, (int[]) { 0, 12, 12, 3, 12 }, NUMBER_OF_CARDS_IN_HAND);

    resetArray(actualCountCards, TOTAL_NUMBER_OF_FACES);
    AssertIntsAreEqual(3, getMaxNumberSameCard(testHand, actualCountCards), "1. getMaxNumberSameCard did not return expected value");
    AssertArraysAreEqual((int[]) { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3 }, actualCountCards, "4. getMaxNumberSameCard did not return expected value", TOTAL_NUMBER_OF_FACES);

    // {0, 12, 12, 0, 12 };
    testHand.player_hand[3].face_index = 0;
    resetArray(actualCountCards, TOTAL_NUMBER_OF_FACES);
    AssertIntsAreEqual(3, getMaxNumberSameCard(testHand, actualCountCards), "2. getMaxNumberSameCard did not return expected value");
    AssertArraysAreEqual((int[]) { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 }, actualCountCards, "5. getMaxNumberSameCard did not return expected value", TOTAL_NUMBER_OF_FACES);

    // {0, 12, 4, 0, 12 };
    testHand.player_hand[2].face_index = 4;
    resetArray(actualCountCards, TOTAL_NUMBER_OF_FACES);
    AssertIntsAreEqual(2, getMaxNumberSameCard(testHand, actualCountCards), "3. getMaxNumberSameCard did not return expected value");
    AssertArraysAreEqual((int[]) { 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2 }, actualCountCards, "6. getMaxNumberSameCard did not return expected value", TOTAL_NUMBER_OF_FACES);
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
    testhand.player_hand[0].face_index = 0;
    testhand.player_hand[1].face_index = 12;
    testhand.player_hand[2].face_index = 12;
    testhand.player_hand[3].face_index = 3;
    testhand.player_hand[4].face_index = 12;
    score = scoreHand(testhand);
    AssertIntsAreEqual(ScoreValueThreeOfAKind, score, "1. Returned score was unexpected");
    testhand.player_hand[4].face_index = 9;
    score = scoreHand(testhand);
    AssertIntsAreEqual(ScoreValuePair, score, "2. Returned score was unexpected");
    testhand.player_hand[4].face_index = 3;
    score = scoreHand(testhand);
    AssertIntsAreEqual(ScoreValueTwoPair, score, "3. Returned score was unexpected");
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
    AssertIntsAreEqual(ScoreValueFlush, score, "4. Returned score was unexpected");
    testhand.player_hand[3].suit_index = 2;
    score = scoreHand(testhand);
    AssertIntsAreEqual(ScoreValueStraight, score, "5. Returned score was unexpected");
}

void Test_getMaxElementInArray()
{
    int testarray1[] = { 1,4,6,7,8 };
    AssertIntsAreEqual(8, getMaxElementInArray(testarray1, 5), " getMaxElementInArray did not return expected value");
    int testarray2[] = { 1,4,6,7,8,-12,0,42 };
    AssertIntsAreEqual(42, getMaxElementInArray(testarray2, 8), "getMaxElementInArray did not return expected value");
}

void Test_checkStraight()
{
    Hand testhand = { 0 };
    testhand.player_hand[0].face_index = 0;
    testhand.player_hand[1].face_index = 12;
    testhand.player_hand[2].face_index = 12;
    testhand.player_hand[3].face_index = 3;
    testhand.player_hand[4].face_index = 12;
    AssertIsTrue(!checkStraight(testhand), "checkStraight Unexpectedly returned true");

    int i = NUMBER_OF_CARDS_IN_HAND;
    testhand.player_hand[0].face_index = i++;
    testhand.player_hand[1].face_index = i++;
    testhand.player_hand[2].face_index = i++;
    testhand.player_hand[3].face_index = i++;
    testhand.player_hand[4].face_index = i++;
    AssertIsTrue(checkStraight(testhand), "checkStraight Unexpectedly returned true");

    testhand.player_hand[0].face_index = 8;
    testhand.player_hand[1].face_index = 5;
    testhand.player_hand[2].face_index = 6;
    testhand.player_hand[3].face_index = 9;
    testhand.player_hand[4].face_index = 7;
    AssertIsTrue(checkStraight(testhand), "checkStraight Unexpectedly returned true");
}

void printTestFailed(const char* message)
{
    char localMessage[254];
    // TODO: Append expected and actual to the message to you can read the problem in the output.
    sprintf(localMessage, "%s%s%s%s", "\033[1;31m", message, "", "\033[0m");
    printf(localMessage);
}

void AssertArraysAreEqual(int expected[], int actual[], const char* message, int length)
{
    char localMessage[1024 * 2];
    char actualText[1024];
    char expectedText[1024];
    bool arraysDiffer = false;
    for (int i = 0; i < length; i++)
    {
        if (actual[i] != expected[i] && !arraysDiffer)
        {
            sprintf(localMessage, "Arrays different starting at index %d: ", i);
            sprintf(actualText, "%s", "...");
            sprintf(expectedText, "%s", "...");
            arraysDiffer = true;
        }
        if (arraysDiffer)
        {
            sprintf(actualText, "%s%d, ", actualText, actual[i]);
            sprintf(expectedText, "%s%d, ", expectedText, actual[i]);
        }
    }
    if (arraysDiffer)
    {
        sprintf(localMessage, "%s{%s} != {%s}", localMessage, expectedText, actualText);
        printTestFailed(localMessage);
    }
}


void AssertIntsAreEqual(int expected, int actual, const char* message)
{
    if (actual != expected)
    {
        // TODO: Append expected and actual to the message to you can read the problem in the output.
        printTestFailed(message);
        printf("\n");
    };
}

void AreIntNotEqual(int expected, int actual, const char* message)
{
    if (actual == expected)
    {
        char localMessage[254];
        // TODO: Append expected and actual to the message to you can read the problem in the output.
        sprintf(localMessage, "%s (Expected = %d, Actual= %d)", message, expected, actual);
        printTestFailed(localMessage);
        //printf("\n");
    };
}

void AssertIsTrue(bool condition, const char* message)
{
    if (!condition)
    {
        // TODO: Append expected and actual to the message to you can read the problem in the output.
        printTestFailed(message);
        printf("\n");
    };
}
