/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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


    printf ("TESTING shuffle():\n");

    //testing for shuffling to ensure the deck is actually being shuffled. 
    shuffle(thisPlayer, &testG); 
    //Verify deck counts are the same
    assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer],"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
    
    for(i = 0; i < testG.deckCount[thisPlayer]; i++)
    {
       if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i])
       {
            assertTrue(1,"The decks are shuffled");
            printf("The decks are shuffled\n"); 
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