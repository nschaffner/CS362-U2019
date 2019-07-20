/**************************************************************** 
* Title: unittest2.c
* Author: Nicholas Schaffner
* Last Modified: 07/19/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This test suite tests the minionCase function located in the dominion.c file.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int minionCase(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

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

    printf("\n----------------- unittest2.c Testing Card: Minion ----------------\n");

    // Test 1
    printf("TEST 1: Player chooses +2 coins.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    minionCase(1, 0, &testG, 0, 0);

    printf("The current player has one more action.\n");
    printf("G: %d\n", G.numActions);
    printf("testG: %d\n", testG.numActions);
    assertTrue(G.numActions + 1, testG.numActions);    

    printf("The current player has the correct amount of coins.\n");
    printf("G: %d\n", G.coins);
    printf("testG: %d\n", testG.coins);    
    assertTrue(G.coins + 2, testG.coins);

    printf("The current player didn't discard any cards.\n");
    printf("G: %d\n", G.handCount[0]);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0], testG.handCount[0]);

    printf("The next player didn't discard any cards.\n");
    printf("G: %d\n", G.handCount[1]);
    printf("testG: %d\n", testG.handCount[1]);
    assertTrue(G.handCount[1], testG.handCount[1]);

    // Test 2
    printf("TEST 2: Player chooses to discard their hand and opponent has 5 cards in their hand.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.handCount[1] = 5;

    for(int i = 0; i < 5; i++){                                                                     // For loop to assign 5 baron cards to the next player's hand
        testG.hand[1][i] = baron;
    }

    minionCase(0, 1, &testG, 0, 0);

    printf("The current player has one more action.\n");
    printf("G: %d\n", G.numActions);
    printf("testG: %d\n", testG.numActions);
    assertTrue(G.numActions + 1, testG.numActions);    

    printf("The current player has the correct amount of coins.\n");
    printf("G: %d\n", G.coins);
    printf("testG: %d\n", testG.coins); 
    assertTrue(G.coins, testG.coins);

    printf("The current player discarded their current hand and got 4 new cards.\n");
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(testG.handCount[0], 4);

    printf("The next player discarded their hand and got 4 new cards.\n");
    printf("testG: %d\n", testG.handCount[1]);
    assertTrue(testG.handCount[1], 4);

    // Test 3
    printf("TEST 3: Player chooses to discard their hand and opponent has 3 cards in their hand.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.handCount[1] = 3;

    for(int i = 0; i < 3; i++){                                                                     // For loop to assign 3 baron cards to the next player's hand
        testG.hand[1][i] = baron;
    }

    minionCase(0, 1, &testG, 0, 0);

    printf("The current player has one more action.\n");
    printf("G: %d\n", G.numActions);
    printf("testG: %d\n", testG.numActions);
    assertTrue(G.numActions + 1, testG.numActions);    

    printf("The current player has the correct amount of coins.\n");
    printf("G: %d\n", G.coins);
    printf("testG: %d\n", testG.coins); 
    assertTrue(G.coins, testG.coins);

    printf("The current player discarded their current hand and got 4 new cards.\n");
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(testG.handCount[0], 4);

    printf("The next player didn't discard any cards.\n");
    printf("testG: %d\n", testG.handCount[1]);
    assertTrue(testG.handCount[1], 3);

    printf("\n >>>>> Testing complete for Minion <<<<<\n\n");

    return 0;
}