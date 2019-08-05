/*
 * unittest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h> 

#define TESTCARD "baron"

void assertTrue(bool condition, char *msg)
{
	if(!(condition))
	{
		printf("%s:\n is not true!\n", msg);
	}
}

int main() {

    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    //int i, j, m;
    //int handpos = 0;
    int choice1 = 0; 
    //int choice2 = 0;
    //int choice3 = 0; 
    //int bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1 = +2 cards --------------
	printf("TEST 1: choice1 = 1 = Discard an estate and + 4 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	callBaron(&testG,choice1);

	xtraCoins = 4;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
	assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");


	// ----------- TEST 2: choice1 = 0 = +1 card --------------
	printf("TEST 2: choice1 = 0 = Gain an estate card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	callBaron(&testG,choice1);
	discarded = 0; 
	newCards = 1; 
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
	assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}

