#pragma warning (disable: 6031)
#ifndef LOOPS_H // guard code
#define LOOPS_H

#define _CRT_SECURE_NO_WARNINGS

#define SUITS 4
#define FACES 13
#define CARDS 52

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
    Card player_hand[5];

} Hand;

int runmenu();
int getint();
void displayrules();
void shuffle(int wDeck[][FACES]);
void deal(const int wDeck[][FACES], const char* wFace[], const char* wSuit[], Hand p1_hand, Hand dealer_hand);
void game_controller(const int deck[][FACES], const char* face[], const char* suit[], Hand p1_hand, Hand dealer_hand);
bool check_pair(Hand hand);
//bool checkTwoPairs(Hand hand, Card excludeCards);
int scoreHand(Hand hand);
bool checkStraight(Hand hand);
void bubble_sort(Hand* hand, int num_items);
int getMaxNumberSameCard(Hand hand);


enum ScoreValue { ScoreValueThreeOfAKind = 7, ScoreValuePair = 9};

//int getSizeIntOfArray(int array[]);

int getMaxElementInArray(int array[], int arraySize);

int getMaxNumberSameCard(Hand hand, int* cardCountArrayToScoreHand);

//int scoreHand(int maxSameCard, int* indexForRejectedCards[]);

//bool checkThreeOfaKind(Hand hand);
//bool checkStraight(Hand hand);
//bool checkFlush(Hand hand);
//bool checkFourOfaKind(Hand hand);



#endif