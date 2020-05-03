#include "poker.h"

void Test_getMaxElementInArray();

void setHand(Hand* pHand, int values[], int length);

void resetArray(int array[], int length);

void Test_scoreHand();

void AssertIntsAreEqual(int expected, int actual, const char*  message);

void AreIntNotEqual(int expected, int actual, const char* message);

void AssertIsTrue(bool actual, const char* message);

void Test_checkStraight();


void printTestFailed(const char* message);

void runAllTests();

void Test_shuffleDeck();

bool allItemsAreUniqueAndShuffled(Card * pDeck, int length);

void Test_deal();

void Test_getMaxNumberSameCard();

void AssertArraysAreEqual(int expected[], int actual[], const char* message, int length);

