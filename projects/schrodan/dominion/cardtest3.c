/*
CS-362 Spring 2017
Daniel Schroeder
This is a unit test for the dominion card great_hall
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>	
#include "rngs.h"
#include "dominion.h"

int myk[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			 smithy, village, baron, great_hall};

//This function tests that great_hall works correctly in base state
int testGreatHall(struct gameState *state){
	
	//handCount should remain the same (+1 card great_hall, -1 discard great_hall)
	//actions should remain the same
	//deck should decrease by 1
	
	int handSize = state->handCount[whoseTurn(state)];
	int deckSize = state->deckCount[whoseTurn(state)];
	int actions = state->numActions;
	int coinsOld = state->coins;
	
	state->hand[whoseTurn(state)][0] = great_hall; //make first card in hand a smithy
	
	int run = playCard(0, 0, 0, 0, state);
	
	//check that playCard worked
	if(run < 0){
		printf("playCard() Failed!\n");
		return 1;	
	}
	
	//assert that hand value remained the same
	if(state->handCount[whoseTurn(state)] != handSize){
		printf("Wrong number of cards in hand\n");
		return 1;
	}
 	
 	//assert that smithy was discarded
	if(state->hand[whoseTurn(state)][0] == great_hall){
		printf("Smithy not discarded\n");
		return 1;	
	}
	
	//assert deck decreased by 1 
	if(state->deckCount[whoseTurn(state)] != (deckSize - 1)){
		printf("Deck size is wrong\n");
		return 1;		
	}
	
	//assert actions stayed the same (+1)
	if(state->numActions != actions){
		printf("Number of actions is wrong\n");
		return 1;		
	}
	
	int cardDrawn = state->hand[whoseTurn(state)][state->handCount[whoseTurn(state)] - 1];
	
	int newCoins = 0;
	if( cardDrawn == copper )
		newCoins = 1;
	else if( cardDrawn == silver )
		newCoins = 2;
	else if( cardDrawn == gold )
		newCoins = 3;
	
	//ADDED AFTER INITAL TESTING
	//FOUND BUG
	//ASSERT THAT COINS do not change
	if((coinsOld + newCoins) != state->coins){
		printf("Coins did not remain the same\n");
		return 1;
	}

	return 0;
}

int main(int argc, char *argv[]){
	struct gameState G;

	SelectStream(2);
	PutSeed(3);
	
	int r;
	
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(2, myk, 3, &G);
	int test = testGreatHall(&G);
	
	if(test == 0)	
		return 0;
	return -1;
}


