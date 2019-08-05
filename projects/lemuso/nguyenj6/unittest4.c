/*
 * unittest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h> 

#define TESTCARD "Tribute"

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
    int nextPlayer = 1; 
    int tributeRevealedCards[2] = {1,2};
	struct gameState G, testG;

	int k[10] = {adventurer, copper, council_room, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1 = +2 coins --------------
	printf("TEST 1:One of the revealed cards is a treasure, adding +2 to current player\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
 
	tributeRevealedCards[0] = gardens;
	tributeRevealedCards[1] = copper;

	callTribute(&testG, choice1, choice2, handpos); 

	xtraCoins = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,"testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded");
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,"testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards");
	assertTrue(testG.coins == G.coins + xtraCoins,"testG.coins == G.coins + xtraCoins");

	// ----------- TEST 1: choice1 = 1 = +2 coins --------------
	printf("TEST 2:revealed cards is not a treasure, not adding +2 to current player\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
 
	tributeRevealedCards[0] = smithy;
	tributeRevealedCards[1] = gardens;


	callTribute(&testG, choice1, choice2, handpos); 

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

