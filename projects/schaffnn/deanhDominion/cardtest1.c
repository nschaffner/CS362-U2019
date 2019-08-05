/**************************************************************** 
* Title: cardtest1.c
* Author: Nicholas Schaffner
* Last Modified: 07/19/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This test suite tests the initializeGame function located in the dominion.c file.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);

void assertTrue(int a){
    if (a < 0){
        printf("FAIL\n");
    }
    else{
        printf("PASS\n");
    }
}

int main() {
    int seed = 1000;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int initiationStatus = 0;
    int assertionStatus = 0;

    printf("\n----------------- cardtest1.c: initializeGame ----------------\n");

    // Test 1
    printf("TEST 1: Initialize a game with 1 player.\n");
    memset(&G, 0, sizeof(struct gameState));

    initiationStatus = initializeGame(1, k, seed, &G);                                                             // Initialize game

    assertTrue(initiationStatus);    

    // Test 2
    printf("TEST 2: Initialize a game with 2 players.\n");
    memset(&G, 0, sizeof(struct gameState));

    initiationStatus = initializeGame(2, k, seed, &G);                                                             // Initialize game

    assertTrue(initiationStatus);  

    if(G.supplyCount[curse] == 10){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Curse cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[estate] == 8){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Estate cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[province] == 8){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Province cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[copper] == 46){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Copper cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[gold] == 30){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Gold cards has been initialized.\n");
    assertTrue(assertionStatus);

    // Test 3
    printf("TEST 3: Initialize a game with 3 players.\n");
    memset(&G, 0, sizeof(struct gameState));

    initiationStatus = initializeGame(3, k, seed, &G);                                                             // Initialize game

    assertTrue(initiationStatus);  

    if(G.supplyCount[curse] == 20){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Curse cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[estate] == 12){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Estate cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[province] == 12){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Province cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[copper] == 39){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Copper cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[gold] == 30){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Gold cards has been initialized.\n");
    assertTrue(assertionStatus);  

    // Test 4
    printf("TEST 4: Initialize a game with 6 players.\n");
    memset(&G, 0, sizeof(struct gameState));

    initiationStatus = initializeGame(6, k, seed, &G);                                                             // Initialize game

    assertTrue(initiationStatus);  

    if(G.supplyCount[curse] == 30){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Curse cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[estate] == 12){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Estate cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[province] == 12){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Province cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[copper] == 18){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Copper cards has been initialized.\n");
    assertTrue(assertionStatus);

    if(G.supplyCount[gold] == 30){
        assertionStatus = 1;
    } 
    else{
        assertionStatus = -1;
    }

    printf("Correct number of Gold cards has been initialized.\n");
    assertTrue(assertionStatus);

    printf("\n >>>>> Testing complete for initializeGame <<<<<\n\n");

    return 0;
}
