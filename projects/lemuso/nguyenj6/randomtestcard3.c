/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * randomtestcard3: randomtestcard3.c dominion.o rngs.o
 *      gcc -o randomtestcard3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h> 


#define DEBUG 0
#define NOISY_TEST 0

void assertTrue(bool condition, char *msg)
{
  if(!(condition))
  {
    if(NOISY_TEST == 1)
    {
      printf("%s:\n is not true!\n", msg);
    }
  }
}

void checkTribute(int* tributeRevealedCards, int p, int nextPlayer, struct gameState *post){
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int handPos= 0;

  callTribute(post, handPos); 

	if (pre.deckCount[p] > 0) {
    	pre.handCount[p]++;
    	pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
    	pre.deckCount[p]--;
  	} 
  	else if (pre.discardCount[p] > 0) {
    	memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
    	memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
    	pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
    	pre.handCount[p]++;
    	pre.deckCount[p] = pre.discardCount[p]-1;
    	pre.discardCount[p] = 0;	
	}

  assertTrue(memcmp(&pre, post, sizeof(struct gameState)) == 0, "Pre and Post did not match");

}

int main () {

  int i, j, n, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  int tributeRevealedCards[2] = {1,2};
  int nextPlayer = 0; 

  struct gameState G;

  printf ("Testing Tribute.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    G.numPlayers = floor(Random() * 4);
    G.whoseTurn = floor(Random() * (G.numPlayers + 1));
    p = G.whoseTurn; 
    //Ensure the game runs with realistic boundaries
    for(j = 0; j < G.numPlayers; j++)
    {
      G.deckCount[j] = floor(Random() * MAX_DECK); 
      G.discardCount[j] = floor(Random() * MAX_DECK);
      G.handCount[j] = floor(Random() * MAX_HAND);
    }     

    if(p == 0)
    {
        nextPlayer = 1; 
    }
    else
    {
      nextPlayer = 0; 
    }

    
    G.playedCardCount = 0; 

    for(i = 0; i < G.numPlayers; i++)
    {
      
      for(j = 0; j < G.deckCount[i]; j++)
      {
        G.deck[i][j] = floor(Random() * (treasure_map + 1)); 
      }
      for(j = 0; j < G.discardCount[i]; j++)
      {
        G.discard[i][j] = floor(Random() * (treasure_map + 1)); 
      }
      for(j = 0; j < G.handCount[i]; j++)
      {
        G.hand[i][j] = floor(Random() * (treasure_map + 1)); 
      }
      
    }
    //printf("Test: %d\n",G.deck[nextPlayer][G.deckCount[nextPlayer] -1 ]);
    checkTribute(tributeRevealedCards, p, nextPlayer, &G); 
  }

  printf ("ALL TESTS OK\n");

  //exit(0);
  int r; 

  printf ("SIMPLE FIXED TESTS.\n");
  for (p = 0; p < 2; p++) {
    for (deckCount = 0; deckCount < 5; deckCount++) {
      for (discardCount = 0; discardCount < 5; discardCount++) {
	for (handCount = 0; handCount < 5; handCount++) {
	  memset(&G, 23, sizeof(struct gameState)); 
	  r = initializeGame(2, k, 1, &G);
	  G.deckCount[p] = deckCount;
	  memset(G.deck[p], 0, sizeof(int) * deckCount);
	  G.discardCount[p] = discardCount;
	  memset(G.discard[p], 0, sizeof(int) * discardCount);
	  G.handCount[p] = handCount;
	  memset(G.hand[p], 0, sizeof(int) * handCount - 1);
	  checkTribute(tributeRevealedCards, p, nextPlayer, &G); 
	}
      }
    }
  }

  return 0;
}