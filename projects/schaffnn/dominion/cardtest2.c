/**************************************************************** 
* Title: cardtest2.c
* Author: Nicholas Schaffner
* Last Modified: 07/19/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This test suite tests the shuffle function located in the dominion.c file.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int shuffle(int player, struct gameState *state);

void assertTrue(int a){
    if (a == 1){
        printf("PASS\n");
    }
    else{
        printf("FAIL\n");
    }
}

int main() {
    int seed = 10;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int assertionStatus = -1;
    int deck1[10];
    int deck2[10];
    int cardPos = 0;

    printf("\n----------------- cardtest2.c: shuffle ----------------\n");

    // Test 1
    printf("TEST 1: Create a deck for one player and shuffle it.\n");
    memset(&G, 0, sizeof(struct gameState));

    initializeGame(1, k, seed, &G);                                                             // Initialize game

    for(int i = 0; i < 10; i++){                                                                // For loop for capturing the cards at each position for Player 1                                                      
        deck1[cardPos] = G.deck[0][i];
        cardPos++;
    }

    shuffle(0, &G);                                                                             // Shuffling Player 1's cards

    for(int i = 0; i < 10; i++){
        if(deck1[i] != G.deck[0][i]){
            assertionStatus = 1;
        }
    }

    printf("The shuffle function correctly shuffled the first player's deck.\n");
    assertTrue(assertionStatus);

    // Test 2
    printf("TEST 2: Create decks for two players and shuffle each of them.\n");
    memset(&G, 0, sizeof(struct gameState));

    initializeGame(2, k, seed, &G);                                                             // Initialize game

    cardPos = 0;
    assertionStatus = -1;

    for(int i = 0; i < 10; i++){                                                                // For loop for capturing the cards at each position for Player 1                                                      
        deck1[cardPos] = G.deck[0][i];
        cardPos++;
    }

    shuffle(0, &G);                                                                             // Shuffling Player 1's cards

    for(int i = 0; i < 10; i++){
        if(deck1[i] != G.deck[0][i]){
            assertionStatus = 1;
        }
    }

    printf("The shuffle function correctly shuffled the first player's deck.\n");
    assertTrue(assertionStatus);

    cardPos = 0;
    assertionStatus = -1;

    for(int i = 0; i < 10; i++){                                                                // For loop for capturing the cards at each position for Player 1                                                      
        deck2[cardPos] = G.deck[1][i];
        cardPos++;
    }

    shuffle(1, &G);                                                                             // Shuffling Player 2's cards

    for(int i = 0; i < 10; i++){
        if(deck2[i] != G.deck[1][i]){
            assertionStatus = 1;
        }
    }

    printf("The shuffle function correctly shuffled the second player's deck.\n");
    assertTrue(assertionStatus);

    printf("\n >>>>> Testing complete for shuffle <<<<<\n\n");

    return 0;
}
