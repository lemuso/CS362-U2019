/*
* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h> 
#include <stdlib.h>
#include <time.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

void assertTrue(bool condition, char *msg)
{
    if(!(condition))
    {
        
    #if (NOISY_TEST == 1)
        printf("%s:\n is not true!\n", msg);
    #endif
    }
}


int main() {
    srand(time(0)); 
    int i;
    int seed = 0;
    int numPlayer = 2;
    //int thisPlayer = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    int aWins = 0; 
    int bWins = 0; 

    int players[MAX_PLAYERS]; 

    printf ("TESTING getWinners():\n");

    //testing to ensure the same player is not a winner everytime. 

    for(i = 0; i < 20; i++)
    {       
            seed=rand(); 
            initializeGame(numPlayer, k, seed, &G);
            getWinners(players,&G); 
            if(players[0] == 1)
            {
                aWins++; 
            }
            if(players[1] == 1)
            {
                bWins++; 
            }
            memset(&G, 23, sizeof(struct gameState));   // clear the game state
    }

    printf("A Wins: %d \n B Wins: %d\n",aWins,bWins); 
    printf("\n >>>>> SUCCESS: Testing complete <<<<<\n\n");

/*
  
    assertTrue((initializeGame(MAX_PLAYERS - 1, k, seed, &G)),"Game allows MAX_PLAYERS - 1");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    
*/
    return 0;
}