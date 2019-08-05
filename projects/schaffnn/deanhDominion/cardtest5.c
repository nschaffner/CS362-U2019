/**************************************************************** 
* Title: cardtest5.c
* Author: Nicholas Schaffner
* Last Modified: 07/19/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This test suite tests the drawCard function located in the dominion.c file.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int drawCard(int player, struct gameState *state);

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
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int assertionStatus = 0;

    printf("\n----------------- cardtest5.c: drawCard ----------------\n");

    // Test 1
    printf("TEST 1: Player has 1 card in discard pile but no cards in deck or hand.\n");
    memset(&G, 0, sizeof(struct gameState));

    initializeGame(2, k, seed, &G);                                                             // Initialize game

    // Remove all cards from current player's hand
    for(int i = 0; i < 5; i++){
        G.hand[0][i] = -1;
    }

    G.handCount[0] = 0;

    // Remove all cards from current player's deck
    for(int i = 0; i < 5; i++){
        G.deck[0][i] = -1;
    }

    G.deckCount[0] = 0;

    G.discard[0][0] = estate;
    G.discardCount[0] = 1;

    drawCard(0, &G);

    if(G.handCount[0] == 1){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The drawCard function correctly drew a card.\n");
    assertTrue(assertionStatus);    

    if(G.deckCount[0] == 0){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The deckCount variable is currently 0.\n");
    assertTrue(assertionStatus);      

    if(G.discardCount[0] == 0){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The discardCount variable is currently 0.\n");
    assertTrue(assertionStatus);                                                

    // Test 2
    printf("TEST 2: Player has 5 cards in their deck and 4 cards in their current hand.\n");
    memset(&G, 0, sizeof(struct gameState));

    initializeGame(2, k, seed, &G);                                                             // Initialize game

    // Set the current player's hand to have 4 estate cards
    for(int i = 0; i < 4; i++){
        G.hand[0][i] = estate;
    }

    G.handCount[0] = 4;

    // Set the current player's deck to have 5 copper cards
    for(int i = 0; i < 5; i++){
        G.deck[0][i] = copper;
    }

    G.deckCount[0] = 5;

    G.discardCount[0] = 0;

    drawCard(0, &G);

    if(G.handCount[0] == 5){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The drawCard function correctly drew a card.\n");
    assertTrue(assertionStatus);    

    if(G.deckCount[0] == 4){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The deckCount variable was decremented by 1.\n");
    assertTrue(assertionStatus);      

    if(G.discardCount[0] == 0){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The discardCount variable is currently 0.\n");
    assertTrue(assertionStatus);

    // Test 3
    printf("TEST 3: Player has 0 cards in their current hand, deck and discard pile.\n");
    memset(&G, 0, sizeof(struct gameState));

    initializeGame(2, k, seed, &G);                                                             // Initialize game

    // Remove all cards from current player's hand
    for(int i = 0; i < 5; i++){
        G.hand[0][i] = -1;
    }

    G.handCount[0] = 0;

    // Remove all cards from current player's deck
    for(int i = 0; i < 5; i++){
        G.deck[0][i] = -1;
    }

    G.deckCount[0] = 0;

    // Remove all cards from current player's discard pile
    for(int i = 0; i < 5; i++){
        G.discard[0][i] = -1;
    }

    G.discardCount[0] = 0;

    drawCard(0, &G);

    if(G.handCount[0] == 0){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The drawCard function did not draw a card because there was no card to draw.\n");
    assertTrue(assertionStatus);    

    if(G.deckCount[0] == 0){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The deckCount variable remained at 0.\n");
    assertTrue(assertionStatus);      

    if(G.discardCount[0] == 0){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }

    printf("The discardCount variable remained at 0.\n");
    assertTrue(assertionStatus);

    printf("\n >>>>> Testing complete for drawCard <<<<<\n\n");

    return 0;
}
