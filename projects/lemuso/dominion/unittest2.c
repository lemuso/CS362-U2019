/*
 * unittest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h> 

#define TESTCARD "minion"

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
    int handpos = 0;
    int choice1 = 0; 
    int choice2 = 0;
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

	// ----------- TEST 1: choice1 = 1 = +2 coins --------------
	printf("TEST 1: choice1 = 1 = +2 Coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 0;
	discarded = 0; 
	playMinion(choice1, choice2, thisPlayer, handpos, &testG);

	xtraCoins = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
	assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");


	// ----------- TEST 2: choice1 = 0 = +1 card --------------
	printf("TEST 2: choice2 = player discards his hand, chooses 4 cards and each other player with at least 5 cards in hand discards his hand and draws 4 cards. \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 0;
	choice2 = 1;
	discarded = G.handCount[thisPlayer]; 
	newCards = 4; 
	xtraCoins = 0; 
	//shuffledCards = G.deckCount[thisPlayer] + discarded; 

	playMinion(choice1, choice2, thisPlayer, handpos, &testG);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
	assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}

