/**************************************************************** 
* Title: unittest3.c
* Author: Nicholas Schaffner
* Last Modified: 07/19/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This test suite tests the ambassadorCase function located in the dominion.c file.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int ambassadorCase(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

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

    printf("\n----------------- unittest3.c Testing Card: Ambassador ----------------\n");

    // Test 1
    printf("TEST 1: Player chooses 1 card to reveal.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.hand[0][0] = ambassador;
    testG.hand[0][1] = copper;

    ambassadorCase(1, 1, &testG, 0, 0);

    printf("The current player discarded 2 cards (1 ambassador + 1 copper).\n");
    printf("G: %d\n", G.handCount[0] - 2);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0] - 2, testG.handCount[0]); 

    printf("The supply count is the same as it was previously because 1 card was added and 1 card removed.\n");
    printf("G: %d\n", G.supplyCount[copper]);
    printf("testG: %d\n", testG.supplyCount[copper]);
    assertTrue(G.supplyCount[copper], testG.supplyCount[copper]);

    printf("There are 2 more cards in the played pile.\n");
    printf("G: %d\n", G.playedCardCount + 2);
    printf("testG: %d\n", testG.playedCardCount);
    assertTrue(G.playedCardCount + 2, testG.playedCardCount);

    // Test 2
    printf("TEST 2: Player chooses 2 cards to reveal.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.hand[0][0] = ambassador;
    testG.hand[0][1] = copper;
    testG.hand[0][2] = copper;

    ambassadorCase(1, 2, &testG, 0, 0);

    printf("The current player discarded 3 cards (1 ambassador + 2 copper).\n");
    printf("G: %d\n", G.handCount[0] - 3);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0] - 2, testG.handCount[0]); 

    printf("The supply count is one more because 2 cards were added and 1 card removed.\n");
    printf("G: %d\n", G.supplyCount[copper] + 1);
    printf("testG: %d\n", testG.supplyCount[copper]);
    assertTrue(G.supplyCount[copper] + 1, testG.supplyCount[copper]);

    printf("There are 3 more cards in the played pile.\n");
    printf("G: %d\n", G.playedCardCount + 3);
    printf("testG: %d\n", testG.playedCardCount);
    assertTrue(G.playedCardCount + 3, testG.playedCardCount);

    // Test 3
    printf("TEST 3: Player chooses 3 cards to reveal.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.hand[0][0] = ambassador;
    testG.hand[0][1] = copper;
    testG.hand[0][1] = copper;
    testG.hand[0][3] = copper;

    ambassadorCase(1, 3, &testG, 0, 0);

    printf("The current player discarded 0 cards.\n");
    printf("G: %d\n", G.handCount[0]);
    printf("testG: %d\n", testG.handCount[0]);
    assertTrue(G.handCount[0], testG.handCount[0]); 

    printf("The supply count is the same.\n");
    printf("G: %d\n", G.supplyCount[copper]);
    printf("testG: %d\n", testG.supplyCount[copper]);
    assertTrue(G.supplyCount[copper], testG.supplyCount[copper]);

    printf("There are 0 more cards in the played pile.\n");
    printf("G: %d\n", G.playedCardCount);
    printf("testG: %d\n", testG.playedCardCount);
    assertTrue(G.playedCardCount, testG.playedCardCount);

    printf("\n >>>>> Testing complete for Ambassador <<<<<\n\n");

    return 0;
}