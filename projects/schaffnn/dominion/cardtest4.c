/**************************************************************** 
* Title: cardtest4.c
* Author: Nicholas Schaffner
* Last Modified: 07/19/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This test suite tests the getWinners function located in the dominion.c file.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int getWinners(int players[MAX_PLAYERS], struct gameState *state);

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
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int playerArr[2] = {-1, -1};

    printf("\n----------------- cardtest4.c: getWinners ----------------\n");

    // Test 1
    printf("TEST 1: Player 1 wins.\n");
    memset(&G, 0, sizeof(struct gameState));

    initializeGame(2, k, seed, &G);                                                             // Initialize game

    // Set the current player's hand, deck and discardCount variables to 5
    G.handCount[0] = 5;
    G.deckCount[0] = 5;
    G.discardCount[0] = 5;

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's hand to a province 
        G.hand[0][i] = province;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's deck to an estate
        G.deck[0][i] = estate;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's discard pile to an estate
        G.discard[0][i] = estate;
    }
    
    // Set the next player's hand, deck and discardCount variables to 5
    G.handCount[1] = 5;
    G.deckCount[1] = 5;
    G.discardCount[1] = 5;

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's hand to an estate 
        G.hand[1][i] = estate;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's deck to an estate
        G.deck[1][i] = estate;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's discard pile to an estate
        G.discard[1][i] = estate;
    }

    getWinners(playerArr, &G);
                                                                   
    // Test whether player 1 won the game
    printf("Player 1 won the game.\n");
    assertTrue(playerArr[0], 1);

    // Test whether player 2 lost the game
    printf("Player 2 lost the game.\n");
    assertTrue(playerArr[1], 0);

    // Test 2
    printf("TEST 2: Player 2 wins.\n");
    memset(&G, 0, sizeof(struct gameState));

    initializeGame(2, k, seed, &G);                                                             // Initialize game

    // Set the current player's hand, deck and discardCount variables to 5
    G.handCount[0] = 5;
    G.deckCount[0] = 5;
    G.discardCount[0] = 5;

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's hand to a estate
        G.hand[0][i] = estate;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's deck to an estate
        G.deck[0][i] = estate;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's discard pile to an estate
        G.discard[0][i] = estate;
    }
    
    // Set the next player's hand, deck and discardCount variables to 5
    G.handCount[1] = 5;
    G.deckCount[1] = 5;
    G.discardCount[1] = 5;

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's hand to an province 
        G.hand[1][i] = province;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's deck to an estate
        G.deck[1][i] = estate;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's discard pile to an estate
        G.discard[1][i] = estate;
    }

    getWinners(playerArr, &G);
                                                                   
    // Test whether player 2 won the game
    printf("Player 2 won the game.\n");
    assertTrue(playerArr[1], 1);

    // Test whether player 1 lost the game
    printf("Player 1 lost the game.\n");
    assertTrue(playerArr[0], 0);

    // Test 3
    printf("TEST 3: Tie score but player 2 wins because they had less turns.\n");
    memset(&G, 0, sizeof(struct gameState));

    initializeGame(2, k, seed, &G);                                                             // Initialize game

    // Set the current player's hand, deck and discardCount variables to 5
    G.handCount[0] = 5;
    G.deckCount[0] = 5;
    G.discardCount[0] = 5;

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's hand to a estate
        G.hand[0][i] = estate;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's deck to an estate
        G.deck[0][i] = estate;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's discard pile to an estate
        G.discard[0][i] = estate;
    }
    
    // Set the next player's hand, deck and discardCount variables to 5
    G.handCount[1] = 5;
    G.deckCount[1] = 5;
    G.discardCount[1] = 5;

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's hand to an estate 
        G.hand[1][i] = estate;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's deck to an estate
        G.deck[1][i] = estate;
    }

    for(int i = 0; i < 5; i++){                                                                 // Set each card in the current player's discard pile to an estate
        G.discard[1][i] = estate;
    }

    getWinners(playerArr, &G);
                                                                   
    // Test whether player 2 won the game
    printf("Player 2 won the game.\n");
    assertTrue(playerArr[1], 1);

    // Test whether player 1 lost the game
    printf("Player 1 lost the game.\n");
    assertTrue(playerArr[0], 0);

    printf("\n >>>>> Testing complete for getWinners <<<<<\n\n");

    return 0;
}
