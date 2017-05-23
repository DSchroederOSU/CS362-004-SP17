/*
CS-362 Spring 2017
Daniel Schroeder
This is a unit test for the dominion function getCost()
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>	
#include "rngs.h"
#include "dominion.h"

int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
	 smithy, village, baron, great_hall};

int values[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 
		  3, 5 ,3, 5, 3, 4, 2, 5, 4, 4, 4};	

//this test checks if getCost returns the correct value
int testGetCost(struct gameState *state){


	//test all cards
	int i; 
	for(i = curse; i < treasure_map + 1; i++){
		if(getCost(i) != values[i])
			return 1;
	}

	//test that faulty value returns -1
	if(getCost(100) != -1)
		return 1;

	return 0;
}


int main(int argc, char *argv[]){
	printf("\n------------------------------\nSTARTING UNIT TEST 4 ON FUNCTION GETCOST()\n\n");
	struct gameState G;

	SelectStream(2);
	PutSeed(3);
	
	int r;
	
	memset(&G, 23, sizeof(struct gameState));
		
	r = initializeGame(2, k, 3, &G);
		
	
	int test = testGetCost(&G);
	if(test == 0){
		printf("TEST SUCCESSFUL\n");
		printf("\nEND OF UNIT TEST 4\n------------------------------\n");
		return 0;
	}
	printf("TEST FAILED\n");
	printf("\nEND OF UNIT TEST 4\n------------------------------\n");			
	return 0;
}


