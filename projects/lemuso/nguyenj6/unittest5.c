/*
 * unittest5.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest5: unittest5.c dominion.o rngs.o
 *      gcc -o unittest5 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h> 

#define TESTCARD "Mine"

void assertTrue(bool condition, char *msg)
{
	if(!(condition))
	{
		printf("%s:\n is not true!\n", msg);
	}
}

int main() {

    int newCards = 0;
    int discarded = 0;
    int xtraCoins = 0;
    int shuffledCards = 0;

    //int i, j, m;s
    int handpos = 1;
    int choice1 = 0; 
    int choice2 = 0;
    //int choice3 = 0; 
    //int bonus = 0;
    //int remove1, remove2;
   
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    //int nextPlayer = 1; 
    //int tributeRevealedCards[2] = {1,2};
	struct gameState G, testG;

	int k[10] = {adventurer, copper, council_room, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = copper; choice2=embargo --------------
	printf("TEST 1:discard a copper, add an embargo \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
 
	choice1 = copper; 
	choice2 = embargo; 

	callMine(&testG, choice1, choice2, handpos);

	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
	assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");

	// ----------- TEST 2: choice1 = copper; choice2=mine --------------
	printf("TEST 2:discard a copper, add an mine \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
 
	choice1 = copper; 
	choice2 = mine; 

	

	if (callMine(&testG, choice1, choice2, handpos) >= 1)
	{

		xtraCoins = 0;
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
		printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
		printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
		assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
		assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
		assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	}
	
	else{
		printf("The function retured with an error and passed this test\n");
	}
	return 0;
}

