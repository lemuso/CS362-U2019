/*
 * unittest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest3: unittest2.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h> 

#define TESTCARD "Ambassador"

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

    //int i, j, m;
    int handpos = 1;
    int choice1 = 0; 
    int choice2 = 0;
    //int choice3 = 0; 
    //int bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;

	int k[10] = {adventurer, copper, council_room, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1 = +2 coins --------------
	printf("TEST 1: choice1 = -1 = Should not change the game state at all\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = -1;
	discarded = 0; 
	playAmbassador(choice1, choice2, thisPlayer, handpos, &testG);

	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
	assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");


	// ----------- TEST 2: choice1 = 0 = +1 card --------------
	printf("TEST 2: choice1 = handpos = No change in game state  \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = handpos;
	choice2 = 1;
	discarded = 0; 
	newCards = 0; 
	xtraCoins = 0; 
	//shuffledCards = G.deckCount[thisPlayer] + discarded; 

	playAmbassador(choice1, choice2, thisPlayer, handpos, &testG);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
	assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");

	// ----------- TEST 3: choice1 = 0 = +1 card --------------
	printf("TEST 3: choice1 = 2 and choice2 = 2 = The player desides to reveal card position 2 and chooses to move 2 cards into the supply pile  \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 2;
	choice2 = 2;
	discarded = 2; 
	newCards = 0; 
	xtraCoins = 0; 
	//shuffledCards = G.deckCount[thisPlayer] + discarded; 

	playAmbassador(choice1, choice2, thisPlayer, handpos, &testG);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
	assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");

		// ----------- TEST 4: choice1 = 0 = +1 card --------------
	printf("TEST 4: choice1 = 2 and choice2 = 2 = The player desides to reveal card position 2 and chooses to move 1 card into the supply pile  \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 2;
	choice2 = 1;
	discarded = 1; 
	newCards = 0; 
	xtraCoins = 0; 
	//shuffledCards = G.deckCount[thisPlayer] + discarded; 

	playAmbassador(choice1, choice2, thisPlayer, handpos, &testG);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
	assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	

	return 0;
}

