//Programmer: Benjamin Michaelis
//Description: This is 5 Card Draw Poker run in the windows console - rules are from adopted from wikipedia
//Includes .c Unit Testing, tests.c

#include "poker.h"
#include "tests.h"

int main(void)
{
    runAllTests();

    int menuoption = -1;

    Hand p1_hand = { 0 }; // - to initialize
    //p1_hand.player_hand[0]; // to access specific card modify index inside array (face or suit index) [][]
    Hand dealer_hand = { 0 };

    srand((unsigned)time(NULL)); /* seed random-number generator */

    
    do
    {
        menuoption = runmenu(); //runs menu, checks for valid input
        switch (menuoption) //loops until 3(exit) is selected
        {
        case 1:
            displayrules(); // just displays the rules
            break;
        case 2:
            system("cls"); //clear screen
            game_controller(p1_hand,dealer_hand); //this controls all of the game
            break;
        case 3:
            break;
        }

    } while (menuoption != 3);

    printf("Thank you for playing 5 card draw");

    return 0;
}



