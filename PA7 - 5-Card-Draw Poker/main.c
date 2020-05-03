// Authors: Deitel & Deitel - C How to Program
//include resources/help from: Stackoverflow.com, Mark Michaelis
//This is PA7 - 5 Card Draw Poker - rules are from wikipedia,
//code started with starter code from Deitel & Deitel

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
        menuoption = runmenu();
        switch (menuoption)
        {
        case 1:
            displayrules();
            break;
        case 2:
            system("cls");
            game_controller(p1_hand,dealer_hand);
            break;
        case 3:
            break;
        }

    } while (menuoption != 3);

    printf("Thank you for playing 5 card draw");

    return 0;
}



