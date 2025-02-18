#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);
void playBaron(int currentPlayer, int choice1, struct gameState *state); 
void playMinion(int choice1, int choice2, int currentPlayer, int handPos, struct gameState *state); 
int playAmbassador(int choice1, int choice2, int currentPlayer, int handPos, struct gameState *state); 
int playTribute(int* tributeRevealedCards, int currentPlayer, int nextPlayer, struct gameState *state); 
int playMine(int choice1, int choice2, int handPos, int currentPlayer, struct gameState *state); 

#endif
