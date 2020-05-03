#include "tests.h"
#include "poker.h"

#include<iostream> 
#include<string> // for string class 
using namespace std;


void Test_getMaxNumberSameCard()
{
    Hand testhand = { 0 };
    int indexForRejectedCards2[3] = { 5,6,8 };
    int countCardsTest[13] = { 5,6,8 };
    testhand.player_hand[0].face_index = 0;
    testhand.player_hand[1].face_index = 12;
    testhand.player_hand[2].face_index = 12;
    testhand.player_hand[3].face_index = 3;
    testhand.player_hand[4].face_index = 12;

    AreIntEqual(3, getMaxNumberSameCard(testhand, countCardsTest), "1. getMaxNumberSameCard did not return expected valu");
    testhand.player_hand[3].face_index = 0;
    AreIntEqual(3, getMaxNumberSameCard(testhand, countCardsTest), "2. getMaxNumberSameCard did not return expected value");
    testhand.player_hand[2].face_index = 4;
    AreIntEqual(2, getMaxNumberSameCard(testhand, countCardsTest), "3. getMaxNumberSameCard did not return expected value");
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
    AreIntEqual(ScoreValueThreeOfAKind, score, "Returned score was unexpected");
    std:string s = "tst";
    testhand.player_hand[4].face_index = 9;
    score = scoreHand(testhand);
    AreIntEqual(ScoreValuePair, score, "Returned score was unexpected");

    // TODO: Add additional tests
}

void Test_getMaxElementInArray()
{
    int testarray1[] = { 1,4,6,7,8 };
    AreIntEqual(8, getMaxElementInArray(testarray1, 5), " getMaxElementInArray did not return expected value");
    int testarray2[] = { 1,4,6,7,8,-12,0,42 };
    AreIntEqual(42, getMaxElementInArray(testarray2, 8), "getMaxElementInArray did not return expected value");
}

void AreArraysEqual(int expected[], int actual[], char*  message)
{
    if (actual != expected)
    {
        // TODO: Append expected and actual to the message to you ca read the problem in the output.
        print(message);
        printf("\n");
    };
}


void AreIntEqual(int expected, int actual, char*  message)
{
    if (actual != expected)
    {
        // TODO: Append expected and actual to the message to you ca read the problem in the output.
        print(message);
        printf("\n");
    };
}

void IsTrue(bool condition, char*  message)
{
    if (!condition)
    {
        // TODO: Append expected and actual to the message to you ca read the problem in the output.
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
    cout << message;
}