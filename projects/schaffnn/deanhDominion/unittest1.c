/**************************************************************** 
* Title: unittest1.c
* Author: Nicholas Schaffner
* Last Modified: 08/04/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This test suite tests the baronRe function located in the dominion.c file provided by deanh.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void baronRe(struct gameState *state, int currentPlayer, int choice1);

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
    int numPlayers = 2;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int assertionStatus = 0;

    initializeGame(numPlayers, k, seed, &G);                                                             // Initialize game

    printf("\n----------------- unittest1.c Testing Card: Baron ----------------\n");

    // Test 1
    printf("TEST 1: Player chooses to discard with no Estate cards in current hand.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.handCount[0] = 5;

    for(int i = 0; i < 5; i++){                                                                     // For loop to assign 5 baron cards to the current player's hand
        testG.hand[0][i] = baron;
    }

    baronRe(&testG, 0, 1);

    printf("Does the current player have the correct amount of coins?\n");
    printf("G: %d\n", G.coins);
    printf("testG: %d\n", testG.coins);
    if(G.coins == testG.coins){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("Does the current player have the correct amount of numBuys?\n");
    printf("G: %d\n", G.numBuys + 1);
    printf("testG: %d\n", testG.numBuys);
    if(G.numBuys + 1 == testG.numBuys){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("Does the supply pile have the correct amount of Estate cards?\n");
    printf("G: %d\n", supplyCount(estate, &G));
    printf("testG: %d\n", supplyCount(estate, &testG));
    if(supplyCount(estate, &G) - 1 == supplyCount(estate, &testG)){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    // Test 2
    printf("TEST 2: Player chooses to discard with one Estate card in current hand.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.handCount[0] = 5;

    testG.hand[0][0] = estate;

    for(int i = 1; i < 5; i++){                                                                     // For loop to assign 4 baron cards to the current player's hand
        testG.hand[0][i] = baron;
    }

    baronRe(&testG, 0, 1);

    printf("Does the current player have the correct amount of coins?\n");
    printf("G: %d\n", G.coins + 4);
    printf("testG: %d\n", testG.coins);
    if(G.coins + 4 == testG.coins){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("Does the current player have the correct amount of numBuys?\n");
    printf("G: %d\n", G.numBuys + 1);
    printf("testG: %d\n", testG.numBuys);
    if(G.numBuys + 1 == testG.numBuys){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("Does the supply pile have the correct amount of Estate cards?\n");
    printf("G: %d\n", supplyCount(estate, &G));
    printf("testG: %d\n", supplyCount(estate, &testG));
    if(supplyCount(estate, &G) == supplyCount(estate, &testG)){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    // Test 3
    printf("TEST 3: Player chooses to discard with two Estate cards in current hand.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.handCount[0] = 5;

    testG.hand[0][0] = estate;
    testG.hand[0][1] = estate;

    for(int i = 2; i < 5; i++){                                                                     // For loop to assign 3 baron cards to the current player's hand
        testG.hand[0][i] = baron;
    }

    baronRe(&testG, 0, 1);

    printf("Does the current player have the correct amount of coins?\n");
    printf("G: %d\n", G.coins + 4);
    printf("testG: %d\n", testG.coins);
    if(G.coins + 4 == testG.coins){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("Does the current player have the correct amount of numBuys?\n");
    printf("G: %d\n", G.numBuys + 1);
    printf("testG: %d\n", testG.numBuys);
    if(G.numBuys + 1 == testG.numBuys){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("Does the supply pile have the correct amount of Estate cards?\n");
    printf("G: %d\n", supplyCount(estate, &G));
    printf("testG: %d\n", supplyCount(estate, &testG));
    if(supplyCount(estate, &G) == supplyCount(estate, &testG)){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    // Test 4
    printf("TEST 4: Player chooses not to discard with no Estate cards in current hand.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.handCount[0] = 5;

    for(int i = 0; i < 5; i++){                                                                     // For loop to assign 5 baron cards to the current player's hand
        testG.hand[0][i] = baron;
    }

    baronRe(&testG, 0, 0);

    printf("Does the current player have the correct amount of coins?\n");
    printf("G: %d\n", G.coins);
    printf("testG: %d\n", testG.coins);
    if(G.coins == testG.coins){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("Does the current player have the correct amount of numBuys?\n");
    printf("G: %d\n", G.numBuys + 1);
    printf("testG: %d\n", testG.numBuys);
    if(G.numBuys + 1 == testG.numBuys){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("Does the supply pile have the correct amount of Estate cards?\n");
    printf("G: %d\n", supplyCount(estate, &G) - 1);
    printf("testG: %d\n", supplyCount(estate, &testG));
    if(supplyCount(estate, &G) - 1 == supplyCount(estate, &testG)){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    // Test 5
    printf("TEST 5: Player chooses not to discard with one Estate card in current hand. \n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.handCount[0] = 5;

    testG.hand[0][0] = estate;

    for(int i = 1; i < 5; i++){                                                                     // For loop to assign 4 baron cards to the current player's hand
        testG.hand[0][i] = baron;
    }

    baronRe(&testG, 0, 0);

    printf("Does the current player have the correct amount of coins?\n");
    printf("G: %d\n", G.coins);
    printf("testG: %d\n", testG.coins);
    if(G.coins == testG.coins){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("Does the current player have the correct amount of numBuys?\n");
    printf("G: %d\n", G.numBuys + 1);
    printf("testG: %d\n", testG.numBuys);
    if(G.numBuys + 1 == testG.numBuys){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("Does the supply pile have the correct amount of Estate cards?\n");
    printf("G: %d\n", supplyCount(estate, &G) - 1);
    printf("testG: %d\n", supplyCount(estate, &testG));
    if(supplyCount(estate, &G) - 1 == supplyCount(estate, &testG)){
        assertionStatus = 1;
    }
    else{
        assertionStatus = -1;
    }
    assertTrue(assertionStatus);

    printf("\n >>>>> Testing complete for Baron <<<<<\n\n");

    return 0;
}