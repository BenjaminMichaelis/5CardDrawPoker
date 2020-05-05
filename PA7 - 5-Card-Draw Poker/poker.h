#pragma warning (disable: 6031)
#ifndef LOOPS_H // guard code
#define LOOPS_H

#define _CRT_SECURE_NO_WARNINGS

#define TOTAL_NUMBER_OF_SUITS 4
#define TOTAL_NUMBER_OF_FACES 13
#define TOTAL_NUMBER_OF_CARDS (TOTAL_NUMBER_OF_FACES*TOTAL_NUMBER_OF_SUITS)
#define NUMBER_OF_CARDS_IN_HAND 5

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <stdbool.h>
#include <Bits.h>
#include <string.h>

typedef struct card
{
    int suit_index;
    int face_index;
} Card;

typedef struct hand
{
    Card player_hand[NUMBER_OF_CARDS_IN_HAND];

} Hand;

int runmenu();
int getint();
void displayrules();
void swap(Card* a, Card* b);
void shuffleDeck();
#ifdef OldCode
void shuffle(int wDeck[][TOTAL_NUMBER_OF_FACES]);
void dealOneCard(Hand hand, int indexToReplace);
int getCardValue();
#endif OldCode
Card pullNextCardFromDeck();
void deal(Hand* player1Hand, Hand* dealerHand);
void game_controller(Hand p1_hand, Hand dealer_hand);
bool check_pair(Hand hand);
//bool checkTwoPairs(Hand hand, Card excludeCards);
int scoreHand(Hand hand, int* cardCountArrayToScoreHand[]);
void evaluateAndChangeDealersHand(Hand* pPlayer2Hand);
void allowPlayerReplaceCards(Hand* pPlayer1Hand);
bool checkStraight(Hand hand);
bool checkFlush(Hand hand);
void bubble_sort(Hand* hand, int num_items);
bool checkTwoPair(int * cardCount[]);
enum ScoreValue { ScoreValueThreeOfAKind = 7, ScoreValuePair = 9, ScoreValueTwoPair = 8, ScoreValueStraight = 6, ScoreValueFlush = 5, ScoreValueFourOfAKind = 3};

//int getSizeIntOfArray(int array[]);

int getMaxElementInArray(int array[], int arraySize);
int getMaxNumberSameCard(Hand hand, int* cardCountArrayToScoreHand[]);

//int scoreHand(int maxSameCard, int* indexForRejectedCards[]);

//bool checkThreeOfaKind(Hand hand);
//bool checkStraight(Hand hand);
//bool checkFlush(Hand hand);
//bool checkFourOfaKind(Hand hand);



#endif