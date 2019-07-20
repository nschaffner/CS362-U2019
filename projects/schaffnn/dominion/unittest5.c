/**************************************************************** 
* Title: unittest5.c
* Author: Nicholas Schaffner
* Last Modified: 07/13/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This test suite tests the mineCase function located in 
*               the dominion.c file.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int mineCase(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

void assertTrue(int a, int b){
    if (a == b){
        printf("PASS\n");
    }
    else{
        printf("FAIL\n");
    }
}

int main() {
    int seed = 1000;
    int numPlayers = 2;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    initializeGame(numPlayers, k, seed, &G);                                                             // Initialize game

    printf("\n----------------- unittest5.c Testing Card: Mine ----------------\n");

    // Test 1
    printf("TEST 1: Player uses a Copper card to gain a Copper card.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.hand[0][0] = mine;
    testG.hand[0][1] = copper;

    for(int i = 2; i < 4; i++){
        testG.hand[0][i] = estate;
    }

    mineCase(copper, copper, &testG, 0, 0);

    printf("The current player used a Copper card to gain a Copper card.\n");
    printf("Expected value: %d\n", copper);
    printf("testG: %d\n", testG.hand[0][1]);
    assertTrue(testG.hand[0][1], copper);    

    printf("The current player has the correct number of cards in their hand.\n");
    printf("G: %d\n", G.handCount[0]);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0] - 1, testG.handCount[0]);

    // Test 2
    printf("TEST 2: Player uses a Copper card to gain a Silver card.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.hand[0][0] = mine;
    testG.hand[0][1] = copper;

    for(int i = 2; i < 4; i++){
        testG.hand[0][i] = estate;
    }

    mineCase(copper, silver, &testG, 0, 0);

    printf("The current player used a Copper card to gain a Silver card.\n");
    printf("Expected value: %d\n", silver);
    printf("testG: %d\n", testG.hand[0][1]);
    assertTrue(testG.hand[0][1], silver);    

    printf("The current player has the correct number of cards in their hand.\n");
    printf("G: %d\n", G.handCount[0]);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0] - 1, testG.handCount[0]);

    // Test 3
    printf("TEST 3: Player uses a Copper card to try to gain a Gold card.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.hand[0][0] = mine;
    testG.hand[0][1] = copper;

    for(int i = 2; i < 4; i++){
        testG.hand[0][i] = estate;
    }

    mineCase(copper, gold, &testG, 0, 0);

    printf("The current player used a Copper card to gain a Gold card.\n");
    printf("Expected value: %d\n", copper);
    printf("testG: %d\n", testG.hand[0][1]);
    assertTrue(testG.hand[0][1], copper);    

    printf("The current player has the correct number of cards in their hand.\n");
    printf("G: %d\n", G.handCount[0]);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0], testG.handCount[0]);

    printf("\n >>>>> Testing complete for Mine <<<<<\n\n");

    return 0;
}
