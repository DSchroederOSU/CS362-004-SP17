//A random tester for playGreatHall
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1
int badaction;
int badcoin;
int k[10] = {adventurer, council_room, feast, gardens, mine,
		   remodel, smithy, village, baron, great_hall};

void printHand(int player, struct gameState *game){
	int i;
	for(i = 0; i < game->handCount[player]; i++){
		printf("Hand[%d]: %d\n", i, game->hand[player][i]);
	}

}
void printDeck(int player, struct gameState *game){
	int i;
	for(i = 0; i < game->deckCount[player]; i++){
		printf("Deck[%d]: %d\n", i, game->deck[player][i]);
	}

}
void printDiscard(int player, struct gameState *game){
	int i;
	for(i = 0; i < game->discardCount[player]; i++){
		printf("Discard[%d]: %d\n", i, game->discard[player][i]);
	}

}

int testplayGreatHall(int p, struct gameState *post) {
	int h;
	for(h = 0; h < post->handCount[p]; h++){
		post->hand[p][h] = (int)floor(Random() * 26);
	
	}
	int d;
	for(d = 0; d < post->deckCount[p]; d++){
		post->deck[p][d] = (int)floor(Random() * 26);
	
	}
	int dis;
	for(dis = 0; dis < post->discardCount[p]; dis++){
		post->discard[p][dis] = (int)floor(Random() * 26);
	
	}
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	post->hand[p][0] = 16; //give player a great_hall
	playGreatHall(post, 0, p);
	
	
	if(post->numActions != (pre.numActions + 1))
		badaction++;
	if(post->coins != pre.coins)
		badcoin++;
	
		
	return 0;
  
	//test = playAdventurer(post, indexof, p);
  
}



int main () {

	int i, r, p;
	struct gameState G;

	SelectStream(2);
	PutSeed(3);
	badaction = 0;
	badcoin = 0;
	for (i = 1; i < 1000; i++) {

			memset(&G, 23, sizeof(struct gameState)); 
			r = initializeGame(2, k, i, &G);
			p = floor(Random() * 2);
			G.deckCount[p] = floor(Random() * MAX_DECK);
			G.discardCount[p] = floor(Random() * MAX_DECK);
			G.handCount[p] = floor(Random() * MAX_HAND);
		 	testplayGreatHall(p, &G);
	}
	if(badaction > 0)
		printf("Test Failed!\nNumber of action + 1 failures: %d\n", badaction);
	if(badcoin > 0)
		printf("Test Failed!\nNumber of coin change failures: %d\n", badcoin);
	
	return 0;
}
