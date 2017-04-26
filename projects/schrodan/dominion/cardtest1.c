/*
CS-362 Spring 2017
Daniel Schroeder
This is a unit test for the dominion card adventurer
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>	
#include "rngs.h"
#include "dominion.h"

int myk[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			 smithy, village, baron, great_hall};

//This function tests that Adventurer works correctly in base state
int testAdventurerNormal(struct gameState *state){
	
	int handSize = state->handCount[whoseTurn(state)];
	int deckSize = state->deckCount[whoseTurn(state)];
	
	
	state->hand[whoseTurn(state)][0] = adventurer; //make first card in hand an adventurer
	
	
	//printf("Current coins: %d\n", state->coins);
	int pastCoins = state->coins;
	int run = playCard(0, 0, 0, 0, state);
	
	//check that playCard worked
	if(run < 0){
		printf("playCard() Failed!\n");
		return 1;	
	}
	
	//assert that coins value increased
	if(pastCoins >= state->coins){
		printf("Coins did not increase\n");
		return 1;
	}
 	
 	//assert that adventurer was discarded
	if(state->hand[whoseTurn(state)][0] == 7){
		printf("Adventurer not discarded\n");
		
	}
	
	//assert deck decreased by 2 and hand increased by 1
	//Added 2 treasures, removed adventurer
	if(state->deckCount[whoseTurn(state)] != (deckSize - 2)){
		printf("Deck size is wrong\n");
		return 1;		
	}
	if(state->handCount[whoseTurn(state)] != (handSize + 1)){
		printf("Hand size is wrong\n");
		return 1;		
	}
		

	return 0;
}

//test function did not cover shuffle case
int testAdventurerShuffle(struct gameState *state){
	
	//set the deck to 1 treasure card
	//add 1 treasure card and 4 other cards to discard
	state->deckCount[whoseTurn(state)] = 1; 
	state->deck[whoseTurn(state)][0] = copper; //only deck card is copper
	state->discardCount[whoseTurn(state)] = 5;
	state->discard[whoseTurn(state)][0] = village; //add to discard
	state->discard[whoseTurn(state)][1] = village; //add to discard
	state->discard[whoseTurn(state)][2] = copper; //add to discard
	state->discard[whoseTurn(state)][3] = village; //add to discard
	state->discard[whoseTurn(state)][4] = village; //add to discard
	
	//after play advenurer is played
	//deck should have 4 cards
	//coins should change by 2
	//discard should be empty
	
	state->hand[whoseTurn(state)][0] = adventurer;

	int coinsOld = state->coins; 

	//printf("Discard: %d\nDeck: %d\nCoins: %d\n", discardOld, deckOld, coinsOld);	

	playCard(0, 0, 0, 0, state);
	//printf("NEW Discard: %d\nNEW Deck: %d\nNEW Coins: %d\n", state->discardCount[whoseTurn(state)], state->deckCount[whoseTurn(state)], state->coins);
	int discard = state->discardCount[whoseTurn(state)];
	int deck = state->deckCount[whoseTurn(state)];
	int coins = state->coins; 

	if((coins - coinsOld) != 2 || deck != 4 || discard != 0){
		printf("FALSE\n");
	}
	return 0;	
}

//test function did not cover non-treasure cards
int testAdventurerTempHand(struct gameState *state){
	
	state->deckCount[whoseTurn(state)] = 5; 
	state->deck[whoseTurn(state)][0] = copper; 
	state->deck[whoseTurn(state)][1] = village; 
	state->deck[whoseTurn(state)][2] = village; 
	state->deck[whoseTurn(state)][3] = village; 
	state->deck[whoseTurn(state)][4] = copper; 

	state->hand[whoseTurn(state)][0] = adventurer;
	playCard(0, 0, 0, 0, state);
	
	return 0;
}

//test function did not cover only one treasure in deck
int testAdventurerOneTreasure(struct gameState *state){
	int oldCoin = state->coins;
	state->deckCount[whoseTurn(state)] = 5; 
	state->deck[whoseTurn(state)][0] = copper; 
	state->deck[whoseTurn(state)][1] = village; 
	state->deck[whoseTurn(state)][2] = village; 
	state->deck[whoseTurn(state)][3] = village; 
	state->deck[whoseTurn(state)][4] = village; 

	state->hand[whoseTurn(state)][0] = adventurer;
	playCard(0, 0, 0, 0, state);
	
	if((state->coins - oldCoin) != 1){ //coins are wrong
		return 1;
	}

	//hand only gained one copper, adventurer is better
	return 0;
}


int main(int argc, char *argv[]){
	printf("\n------------------------------\nSTARTING CARD TEST 1\n\n");
	struct gameState G;

	SelectStream(2);
	PutSeed(3);
	
	int r;
	
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(2, myk, 3, &G);
	int test = testAdventurerNormal(&G);
	
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(2, myk, 3, &G);
	test = testAdventurerShuffle(&G);
		
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(2, myk, 3, &G);
	test = testAdventurerTempHand(&G);
	
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(2, myk, 3, &G);
	test = testAdventurerOneTreasure(&G);
	
	if(test == 0){
		printf("TEST SUCCESSFUL\n");
		printf("\nEND OF CARD TEST 1\n------------------------------\n");
		return 0;
	}
	printf("TEST FAILED\n");
	printf("\nEND OF CARD TEST 1\n------------------------------\n");
	return 0;
}


