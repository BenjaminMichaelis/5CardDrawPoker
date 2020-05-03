// Authors: Deitel & Deitel - C How to Program

#include "poker.h"
#include "tests.h"

int main(void)
{
    Test_deal();
    Test_dealOneCard();
    Test_scoreHand();

    //getMaxNumberSameCard(p1_hand1, indexForRejectedCards1);
    Test_getMaxElementInArray();

    Test_getMaxNumberSameCard();

    Test_checkStraight();

    //return 0;

    int menuoption = -1;
    /* initialize suit array */
    const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

    /* initialize face array */
    const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Jack", "Queen", "King" };

    /* initalize deck array */
    int deck[4][13] = { 0 };


    Hand p1_hand = { 0 }; // - to initialize
    //p1_hand.player_hand[0]; // to access specific card modify index inside array (face or suit index) [][]
    Hand dealer_hand = { 0 };

    srand((unsigned)time(NULL)); /* seed random-number generator */

    
    do
    {
        menuoption = runmenu();
        switch (menuoption)
        {
        case 1:
            displayrules();
            break;
        case 2:
            system("cls");
            game_controller(deck,face,suit,p1_hand,dealer_hand);
            break;
        case 3:
            break;
        }

    } while (menuoption != 3);

    printf("Thank you for playing 5 card draw");

    return 0;
}



