/*
CS-362 Spring 2017
Daniel Schroeder
This is a unit test for the dominion function buyCard()
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>	
#include "rngs.h"
#include "dominion.h"

int myk[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			 smithy, village, baron, great_hall};

//this function asserts that coins were decrimented properly
int assertCoins(struct gameState *first , struct gameState *last, int cards[50]){

	int original = first->coins;
	int new = last->coins;	

	int i;
	
	for(i=0; i < 50; i++){
		if(cards[i] != -1){
			new = new + getCost(cards[i]);
		}
	}

	if(new == original){ 
		return 0;
	}
	return 1;
	
}
//this function asserts that buys are decrimented properly
int assertBuys(struct gameState *first , struct gameState *last, int buys){

	int original = first->numBuys;
	int new = last->numBuys;	

	int i;
	
	for(i=0; i < buys; i++){
		new++;
	}

	if(new == original){ 
		return 0;
	}
	return 1;
	
}

//this function asserts that the card is in our available kindom cards k[10]
int cardAvailable(int card){
	int l;
	for(l = 0; l < 10; l++){
		if(myk[l] == card) return 0;	
	}
	return 1;

}

int getRandomCard(){
	int r = floor(Random() * 28);
	while(cardAvailable(r) == 1){
		r = floor(Random() * 28);
	}
	return r;
} 

void printDeck(struct gameState *game, int player){
	int i;
	for(i = 0; i < game->deckCount[player]; i++){
		printf("Position %d: card: %d\n", i, game->deck[player][i]);
	
	}
}

void testBuyCard(struct gameState *post){
	
	post->coins = 50;
	post->numBuys = 100; 
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));


	//buy a card as long as coins are sufficient

	int cardsPurchased[50];
	memset(cardsPurchased, -1, sizeof(int) * 50);

	int randomCard = getRandomCard();	
	int count = 0;
	int coins = post->coins;
	while(buyCard(randomCard, post) != -1){
		
		cardsPurchased[count] = randomCard;
		randomCard = getRandomCard();
		coins = post->coins;
		count++;
	}

	if(assertCoins(&pre, post, cardsPurchased) == 0)
		printf("Number of coins match\n");
	
	if(assertBuys(&pre, post, count) == 0)	
		printf("Number of buys match\n");
}
//this function asserts that buyCard fails when no buys are left
void testBuyLimit(struct gameState *state){
	state->coins = 100;
	state->numBuys = 1; 
	
	buyCard(getRandomCard(), state);
	if(buyCard(getRandomCard(), state) == -1)
		printf("Buy Limit Test Success\n");

}
//this function asserts that buyCard fails when no card of  
//a specific kind are available
void testCardLimit(struct gameState *state){
	state->coins = 1000;
	state->numBuys = 1000; 
	//kingdom cards
	int i, j;
	for(i = 0; i < 10; i++){
		//Victory Kindom Card
		if(myk[i] == gardens || myk[i] == great_hall){
			for(j = 0; j < 8; j++){
				buyCard(myk[i], state);
			}
			if(buyCard(myk[i], state) == -1)
				printf("Card Limit Reached Return Value: %d\n", -1); 

		}
		//Regular Kingdom Card
		else{
			for(j = 0; j < 10; j++){
				buyCard(myk[i], state);
			}
			if(buyCard(myk[i], state) == -1)
				printf("Card Limit Reached Return Value: %d\n", -1); 
		}
	}//end kingdom cards 
		
}


int main(int argc, char *argv[]){
	struct gameState G;

	SelectStream(2);
	PutSeed(3);
	
	int i, r;
	
	for(i = 0; i < MAX_DECK; i++){
		memset(&G, 23, sizeof(struct gameState));
		
		r = initializeGame(2, myk, i+2, &G);
		
		testBuyCard(&G);
			
	}
	
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(2, myk, 20, &G);
	testCardLimit(&G);
	
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(2, myk, 5, &G);
	testBuyLimit(&G);
	
	return 0;
}


