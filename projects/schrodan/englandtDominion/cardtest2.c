/*
CS-362 Spring 2017
Daniel Schroeder
This is a unit test for the dominion card smithy
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>	
#include "rngs.h"
#include "dominion.h"

int myk[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			 smithy, village, baron, great_hall};

//This function tests that Smithy works correctly in base state
int testSmithy(struct gameState *state){
	
	//handCount should increase by 2 (+3 smithy, -1 discard smithy)
	//actions should decrease by 1
	//deck should decrease by 3
	
	int handSize = state->handCount[whoseTurn(state)];
	int deckSize = state->deckCount[whoseTurn(state)];
	
	printf("DECK SIZE BEFORE PLAY: %d\n", deckSize);
	 	
	state->hand[whoseTurn(state)][0] = smithy; //make first card in hand a smithy
	
	int run = playCard(0, 0, 0, 0, state);
	
	//check that playCard worked
	if(run < 0){
		printf("playCard() Failed!\n");
		return 1;	
	}
	
	//assert that hand value increased
	if((state->handCount[whoseTurn(state)] - handSize) != 2){
		printf("Wrong number of cards in hand\n");
	}
 	
  	//assert that smithy was discarded
	if(state->hand[whoseTurn(state)][0] == smithy){
		printf("Smithy not discarded\n");
	}
	
	//drew 3 cards
	if(state->deckCount[whoseTurn(state)] != (deckSize - 3)){
		printf("Deck[0]: %d\n", state->deck[whoseTurn(state)][0]); 
		printf("Deck size is wrong\nCurrent: %d Should be: %d", state->deckCount[whoseTurn(state)], (deckSize-3));
		return 1;		
	}
	
	if(state->numActions != 0){
		printf("Number of actions is wrong\n");
		return 1;		
	}
		

	return 0;
}

int main(int argc, char *argv[]){
	printf("\n------------------------------\nSTARTING CARD TEST 2 ON SMITHY\n\n");
	struct gameState G;

	SelectStream(2);
	PutSeed(3);
	
	int r;
	
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(2, myk, 3, &G);
	int test = testSmithy(&G);
	
	if(test == 0){
		printf("TEST SUCCESSFUL\n");
		printf("\nEND OF CARD TEST 2\n------------------------------\n");
		return 0;
	}
	printf("TEST FAILED\n");
	printf("\nEND OF CARD TEST 2\n------------------------------\n");
	return 0;
}


