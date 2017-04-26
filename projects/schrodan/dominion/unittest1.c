/*
CS-362 Spring 2017
Daniel Schroeder
This is a unit test for the dominion function shuffle()
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>	
#include "rngs.h"
#include "dominion.h"

//compare two cards (ints) and returns 1 for true, 
int assert_equals(struct gameState *first , struct gameState *last, int player){
	int i;
	
	for(i = 0; i < MAX_DECK; i++){	
		//printf("Testing DECK[%d] = %d\n against two[%d]: %d\n", i,
	 	//first->deck[player][i], i, last->deck[player][i]);
		
		if(first->deck[player][i] != last->deck[player][i]){
			printf("Difference at index %d\n", i);
			return 0;
		}
	}	
	printf("No Differences in Decks\n");
	return 1;
}

void printDeck(struct gameState *game, int player){
	int i;
	for(i = 0; i < game->deckCount[player]; i++){
		printf("Position %d: card: %d\n", i, game->deck[player][i]);
	
	}
}
void testShuffle(int player, struct gameState *post){
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));


	int test;
	test = shuffle(player, post);
	if(test == 0 && pre.deckCount > 0)
		assert_equals(&pre, post, 1);	
}



int main(int argc, char *argv[]){
	struct gameState G;

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			 smithy, village, baron, great_hall};

	SelectStream(2);
	PutSeed(3);
	
	int i, r;
	
	for(i = 0; i < MAX_DECK; i++){
		memset(&G, 23, sizeof(struct gameState));
		
		r = initializeGame(2, k, i+2, &G);
		
		G.deckCount[1] = i;
		int k;
		for(k = 0; k < i; k++){
			G.deck[1][k] = floor(Random() * 12);
		}
		
		testShuffle(1, &G);
	}
	return 0;
}


