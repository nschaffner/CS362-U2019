/**************************************************************** 
* Title: unittest4.c
* Author: Nicholas Schaffner
* Last Modified: 08/04/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This test suite tests the tributeRe function located in the dominion.c file provided by deanh.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void tributeRe(struct gameState *state, int currentPlayer, int tributeRevealedCards[]);

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
    int tributeRevealedCards[2] = {-1, -1};

    initializeGame(numPlayers, k, seed, &G);                                                             // Initialize game

    printf("\n----------------- unittest4.c Testing Card: Tribute ----------------\n");

    // Test 1
    printf("TEST 1: Next player reveals 2 Copper cards.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.deckCount[1] = 2;
    testG.deck[1][0] = copper;
    testG.deck[1][1] = copper;

    G.numActions = 0;
    testG.numActions = 0;

    G.coins = 0;
    testG.coins = 0;

    G.handCount[0] = 0;
    testG.handCount[0] = 0;

    tributeRe(&testG, 0, tributeRevealedCards);

    printf("The current player has 0 additional actions.\n");
    printf("G: %d\n", G.numActions);
    printf("testG: %d\n", testG.numActions);
    assertTrue(G.numActions, testG.numActions);    

    printf("The current player has 2 additional coins.\n");
    printf("G: %d\n", G.coins);
    printf("testG: %d\n", testG.coins);
    assertTrue(G.coins + 2, testG.coins);

    printf("The current player has 0 additional cards.\n");
    printf("G: %d\n", G.handCount[0]);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0], testG.handCount[0]);

    // Test 2
    printf("TEST 2: Next player reveals 1 Gold card and 1 Estate card.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    
    testG.deckCount[1] = 0;
    testG.discardCount[1] = 2;
    testG.deck[1][0] = gold;
    testG.deck[1][1] = estate;

    G.numActions = 0;
    testG.numActions = 0;

    G.coins = 0;
    testG.coins = 0;

    G.handCount[0] = 0;
    testG.handCount[0] = 0;

    tributeRe(&testG, 0, tributeRevealedCards);

    printf("The current player has 0 additional actions.\n");
    printf("G: %d\n", G.numActions);
    printf("testG: %d\n", testG.numActions);
    assertTrue(G.numActions, testG.numActions);    

    printf("The current player has 2 additional coins.\n");
    printf("G: %d\n", G.coins);
    printf("testG: %d\n", testG.coins);
    assertTrue(G.coins + 2, testG.coins);

    printf("The current player has 2 additional cards.\n");
    printf("G: %d\n", G.handCount[0]);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0] + 2, testG.handCount[0]);

    // Test 3
    printf("TEST 3: Next player reveals 1 Estate card.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    
    testG.deckCount[1] = 1;
    testG.discardCount[1] = 0;
    testG.deck[1][0] = estate;

    G.numActions = 0;
    testG.numActions = 0;

    G.coins = 0;
    testG.coins = 0;

    G.handCount[0] = 0;
    testG.handCount[0] = 0;

    tributeRe(&testG, 0, tributeRevealedCards);

    printf("The current player has 0 additional actions.\n");
    printf("G: %d\n", G.numActions);
    printf("testG: %d\n", testG.numActions);
    assertTrue(G.numActions, testG.numActions);

    printf("The current player has 0 additional coins.\n");
    printf("G: %d\n", G.coins);
    printf("testG: %d\n", testG.coins);
    assertTrue(G.coins, testG.coins);

    printf("The current player has 2 additional cards.\n");
    printf("G: %d\n", G.handCount[0]);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0] + 2, testG.handCount[0]);

    // Test 4
    printf("TEST 4: Next player reveals 1 Gold card.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.deckCount[1] = 0;
    testG.discardCount[1] = 1;
    testG.discard[1][0] = gold;

    G.numActions = 0;
    testG.numActions = 0;

    G.coins = 0;
    testG.coins = 0;

    G.handCount[0] = 0;
    testG.handCount[0] = 0;

    tributeRe(&testG, 0, tributeRevealedCards);

    printf("The current player has 0 additional actions.\n");
    printf("G: %d\n", G.numActions);
    printf("testG: %d\n", testG.numActions);
    assertTrue(G.numActions, testG.numActions);    

    printf("The current player has 2 additional coins.\n");
    printf("G: %d\n", G.coins);
    printf("testG: %d\n", testG.coins);
    assertTrue(G.coins + 2, testG.coins);

    printf("The current player has 0 additional cards.\n");
    printf("G: %d\n", G.handCount[0]);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0], testG.handCount[0]);

    printf("\n >>>>> Testing complete for Tribute <<<<<\n\n");

    return 0;
}
