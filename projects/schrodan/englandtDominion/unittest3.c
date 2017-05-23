/*
CS-362 Spring 2017
Daniel Schroeder
This is a unit test for the dominion function handCard()
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>	
#include "rngs.h"
#include "dominion.h"

int myk[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			 smithy, village, baron, great_hall};

//this test asserts that handCard returns the card value 
//at the specified hand position
int testHandCard(struct gameState *state){

	int numCards = numHandCards(state);
	int i;
	
	//build a known hand of cards 1,2,3,4,5
	state->hand[whoseTurn(state)][0] = 1;
	state->hand[whoseTurn(state)][1] = 2;
	state->hand[whoseTurn(state)][2] = 3;
	state->hand[whoseTurn(state)][3] = 4;
	state->hand[whoseTurn(state)][4] = 5;


	for(i = 0; i < numCards; i++){
		if(handCard(i, state) != (i + 1))
			return -1; 
	}
	
	//add card 10 to top of deck
	state->deck[whoseTurn(state)][state->deckCount[whoseTurn(state)] - 1] = 10;
	//draw card 10
	drawCard(whoseTurn(state), state);

	//test is handCard returns the 10 from the top of the deck	
	if(handCard(numCards, state) != 10){
		printf("Drawn card test failed\n");
		return -1;		
	}

	//test what happens on a faulty index
	int test = handCard(10, state);
		printf("This should be a non-valid index: %d\n", test);
			


	//return 0 to say tests successful	
	return 0;
}

int main(int argc, char *argv[]){
	printf("\n------------------------------\nSTARTING UNIT TEST 3 ON FUNCTION HANDCARD()\n\n");

	struct gameState G;

	SelectStream(2);
	PutSeed(3);
	
	int r;
	
	memset(&G, 23, sizeof(struct gameState));
		
	r = initializeGame(2, myk, 3, &G);
		
	int test = testHandCard(&G);
	if(test == 0){
		printf("TEST SUCCESSFUL\n");
		printf("\nEND OF UNIT TEST 3\n------------------------------\n");
		return 0;
	}
	printf("TEST FAILED\n");
	printf("\nEND OF UNIT TEST 3\n------------------------------\n");
	return 0;
}


