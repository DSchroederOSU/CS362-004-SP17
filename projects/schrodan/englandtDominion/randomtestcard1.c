//A random tester for Smithy.
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
int success = 0;
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

int assertSmithy(struct gameState *pre, struct gameState *post, int p){
	if(pre->deckCount[p] > 2){
		if(post->deckCount[p] != (pre->deckCount[p] - 3)){
			printf("deckCount before: %d\n", pre->deckCount[p]);
			printf("deckCount after: %d\n", post->deckCount[p]);
			
			printf("Test Failed: 3 cards not drawn from deck\n");
			return 1;
		}
	}
	else if((pre->deckCount[p] + pre->discardCount[p]) > 2){
		if((post->deckCount[p] + post->discardCount[p]) != (pre->deckCount[p] + pre->discardCount[p] - 3)){
			printf("deckCount before: %d\n", pre->deckCount[p]);
			printf("Test Failed: 3 cards not drawn from deck\n");
			return 1;
		}
	}
	if(post->handCount[p] != pre->handCount[p] + 2)
		printf("New handcount: %d Old handcount: %d\n", post->handCount[p], pre->handCount[p]);	
	
	success++;
	return 0;


}

int testSmithy(int p, struct gameState *post) {
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

	post->hand[p][0] = 13; //give player a smithy
	int run = playCard(0, 0, 0, 0, post);
	assertSmithy(&pre, post, whoseTurn(post));

	return 0;

}



int main () {

	int i, r, p;
	struct gameState G;

	SelectStream(2);
	PutSeed(3);
	
	
	for (i = 1; i < 1000; i++) {

			memset(&G, 23, sizeof(struct gameState)); 
			r = initializeGame(2, k, i, &G);
			p = floor(Random() * 2);
			G.deckCount[p] = floor(Random() * MAX_DECK);
			G.discardCount[p] = floor(Random() * MAX_DECK);
			G.handCount[p] = floor(Random() * MAX_HAND);
			int index = floor(Random() * G.handCount[p]);
			G.hand[p][index] = 7; //give player adventurer at random index
			testSmithy(p, &G);
	}
	printf("Total successes: %d\n", success);
	return 0;
}
