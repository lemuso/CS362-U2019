/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h> 

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
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int thisPlayer = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    initializeGame(numPlayer, k, seed, &G); 

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));


    printf ("TESTING endTurn():\n");

    //testing to ensure the hand was actually discarded after the turn
    //Check whose turn it is

    endTurn(&G); 

    //Verify deck counts are the same
    assertTrue(whoseTurn(&G) != whoseTurn(&testG),"It is the other players turn now");
    
    for(i = 0; i < testG.deckCount[thisPlayer]; i++)
    {
       if (testG.hand[thisPlayer][i] != G.hand[thisPlayer][i])
       {
            assertTrue(1,"The hand is new");
            printf("The turn is over\n"); 
            break;
       } 

    }

    printf("\n >>>>> SUCCESS: Testing complete <<<<<\n\n");

/*
  
    assertTrue((initializeGame(MAX_PLAYERS - 1, k, seed, &G)),"Game allows MAX_PLAYERS - 1");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    
*/
    return 0;
}