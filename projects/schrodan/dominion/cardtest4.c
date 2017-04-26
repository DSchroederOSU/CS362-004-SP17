/*
CS-362 Spring 2017
Daniel Schroeder
This is a unit test for the dominion card salvager
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>	
#include "rngs.h"
#include "dominion.h"

int myk[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			 smithy, village, baron, great_hall};

//This function tests that salvager works correctly in base state
int testSmithy(struct gameState *state){
	
	//buys should increase by 1
	//coins should increase by trashed card
	//hand should decrease by 2 (-1 trash, -1 discard)
	
	int handSize = state->handCount[whoseTurn(state)];
	int coinsOld = 5;
	int buysOld = state->numBuys;
	state->hand[whoseTurn(state)][0] = salvager; //make first card in hand a smithy
	state->hand[whoseTurn(state)][1] = silver; //make second card in hand is a silver to trash
	state->hand[whoseTurn(state)][2] = copper; //make 3rd card in hand a copper
	state->hand[whoseTurn(state)][3] = copper; //make 4th card in hand is a copper
	state->hand[whoseTurn(state)][4] = copper; //5th first card in hand a copper 
	
	int run = playCard(0, 1, 0, 0, state);
	
	//check that playCard worked
	if(run < 0){
		printf("playCard() Failed!\n");
		 
	}
	
	//assert that hand value decreased by 2
	if((handSize - state->handCount[whoseTurn(state)]) != 2){
		printf("Wrong number of cards in hand\n");
		 return 1;
	}
 	
 	//assert that salvager was discarded
	if(state->hand[whoseTurn(state)][0] == salvager){
		printf("Salvager not discarded\n");
		return 1;
	}
	
	
	//assert that coins increased by 3 (value of silver)
	if((state->coins - coinsOld) != 1){
		printf("Coins value is wrong\n");
		return 1;
		 	
	}
	
	if(state->numBuys != (buysOld + 1)){
		printf("Number of buys is wrong\n");
		return 1; 		
	}
		

	return 0;
}

int main(int argc, char *argv[]){
	printf("\n------------------------------\nSTARTING CARD TEST 4\n\n");
	struct gameState G;

	SelectStream(2);
	PutSeed(3);
	
	int r;
	
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(2, myk, 3, &G);
	int test = testSmithy(&G);
	
	if(test == 0){
		printf("TEST SUCCESSFUL\n");
		printf("\nEND OF CARD TEST 4\n------------------------------\n");
		return 0;
	}
	printf("TEST FAILED\n");
	printf("\nEND OF CARD TEST 4\n------------------------------\n");
	return 0;
}


