/**************************************************************** 
* Title: cardtest3.c
* Author: Nicholas Schaffner
* Last Modified: 07/19/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This test suite tests the endTurn function located in the dominion.c file.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int endTurn(struct gameState *state);

void assertTrue(int a){
    if (a == 1){
        printf("PASS\n");
    }
    else{
        printf("FAIL\n");
    }
}

int main() {
    int seed = 1000;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int assertionStatus = 0;
    int currentPlayer = 0;

    printf("\n----------------- cardtest3.c: endTurn ----------------\n");

    // Test 1
    printf("TEST 1: Test the endTurn function.\n");
    memset(&G, 0, sizeof(struct gameState));

    initializeGame(2, k, seed, &G);                                                             // Initialize game

    memcpy(&testG, &G, sizeof(struct gameState));

    endTurn(&testG);

    assertionStatus = 1;                                                                     

    // Test whether all the cards in the current player's hand were discarded
    for(int i = 0; i < 5; i++){
        if(testG.hand[0][i] != -1){
            assertionStatus = -1;
        }
    }

    printf("The endTurn function correctly discarded all of the current player's hand.\n");
    assertTrue(assertionStatus);

    // Test whether the current player's handCount was reset to 0
    if(testG.handCount[0] == 0){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The endTurn function correctly set the current player's handCount to 0.\n");
    assertTrue(assertionStatus);

    // Test whether endTurn has successfully progressed to the next player's turn
    if(currentPlayer == 0){
        if(G.whoseTurn + 1 == testG.whoseTurn){
            assertionStatus = 1;
        }
        else{
            assertionStatus = -1;
        }
    }
    else{
        if(G.whoseTurn - 1 == testG.whoseTurn){
            assertionStatus = 1;
        }
        else{
            assertionStatus = -1;
        }
    }

    printf("The endTurn function correctly progressed to the next player's turn.\n");
    assertTrue(assertionStatus);

    // Test whether the next player has 5 cards in their current hand by checking their handCount variable
    if(testG.handCount[testG.whoseTurn] == 5){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The endTurn function correctly drew 5 cards for the next player.\n");
    assertTrue(assertionStatus);

    // Test how many coins the next player has in their hand. The maximum amount of coins that the current player can have in their hand is 5 since each player starts with Copper cards
    if(testG.coins <= 5){                                                 
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The endTurn function correctly set the number of coins for the next player.\n");
    assertTrue(assertionStatus);

    printf("\n >>>>> Testing complete for endTurn <<<<<\n\n");

    return 0;
}
