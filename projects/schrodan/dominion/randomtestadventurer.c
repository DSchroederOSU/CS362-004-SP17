//A random tester for Adventurer.
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

int assertTreasure(int card){
	if(card == gold || card == silver || card == copper){
		return 0;
	}
	printf("Test Failed: Did not draw treasure\n");
	return 1;
}

int testAdventurer(int p, struct gameState *game) {
	int h;
	for(h = 0; h < game->handCount[p]; h++){
		game->hand[p][h] = (int)floor(Random() * 26);
	
	}
	int d;
	for(d = 0; d < game->deckCount[p]; d++){
		game->deck[p][d] = (int)floor(Random() * 26);
	
	}
	int dis;
	for(dis = 0; dis < game->discardCount[p]; dis++){
		game->discard[p][dis] = (int)floor(Random() * 26);
	
	}
	struct gameState post;
	memcpy(&post, game, sizeof(struct gameState));
	

	if(post.handCount[p] == 0){
		post.hand[p][0] = 7;
		post.handCount[p] = 1;
	}
	post.hand[p][0] = 7;
	
	int oldcount = post.deckCount[p] + post.discardCount[p];
	int oldLastCard = post.hand[p][post.handCount[p]-1];
	playAdventurer(&post, 0, p);
	
	if(oldcount - (post.deckCount[p] + post.discardCount[p]) == 2){ //2 treasure cards were drawn
		assertTreasure(post.hand[p][post.handCount[p]-1]);
		assertTreasure(post.hand[p][post.handCount[p]-2]);
	}
	else if(oldcount - (post.deckCount[p] + post.discardCount[p]) == 1){ //1 treasure card was drawn
		assertTreasure(post.hand[p][post.handCount[p]-1]);
	}
	else{
		//no cards were drawn
		if(post.hand[p][post.handCount[p]-1] != oldLastCard){
			printf("Test Failed: Old Card Changed\nOld: %d New: %d\n", oldLastCard, post.hand[p][post.handCount[p]-1]);
		}
	}
	return 0;
  
	//test = playAdventurer(post, indexof, p);
  
}



int main () {

	int i, r, p;
	struct gameState G;

	SelectStream(2);
	PutSeed(3);
	
	
	for (i = 1; i < 2000; i++) {

			memset(&G, 23, sizeof(struct gameState));  
			r = initializeGame(2, k, i, &G);
			p = floor(Random() * 2);
			G.deckCount[p] = floor(Random() * MAX_DECK);
			G.discardCount[p] = floor(Random() * MAX_DECK);
			G.handCount[p] = floor(Random() * MAX_HAND);
			testAdventurer(p, &G);
	}

	return 0;
}
