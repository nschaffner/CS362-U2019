/**************************************************************** 
* Title: randomtestcard1.c
* Author: Nicholas Schaffner
* Last Modified: 08/04/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This random test suite tests the baronRe function located in the dominion.c file provided by deanh.
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

void baronRe(struct gameState *state, int currentPlayer, int choice1);

int main() {
    srand(time(NULL));
    int testPassed = 0;
    int testFailed = 0;
    int currentPlayer;
    struct gameState G, testG;
    int playerChoice;
    int numPlayers = 0;
    int cardFound = 0;

    printf("\n----------------- randomtestcard1.c Testing Card: Baron -----------------\n");

    for(int i = 0; i < 100000; i++){
        for (int j = 0; j < sizeof(struct gameState); j++) {
            ((char*)&G)[j] = rand() % 256;
        }

        while(numPlayers == 0 || numPlayers == 1){
            numPlayers = rand() % 5;
        }

        currentPlayer = rand() % numPlayers;
        playerChoice = rand() % 2;
        printf("Players choice = %d\n", playerChoice);

        G.playedCardCount = rand() % MAX_DECK;
        G.handCount[currentPlayer] = rand() % 6;
        G.discardCount[currentPlayer] = rand() % MAX_DECK;
        G.coins = rand() % 100;
        G.numBuys = rand() % 20;

        if(numPlayers <= 2){
            G.supplyCount[estate] = rand() % 9;
        }
        else{
            G.supplyCount[estate] = rand() % 13;
        }

        for(int j = 0; j < G.handCount[currentPlayer]; j++){
            G.hand[currentPlayer][j] = rand() % NUM_TOTAL_K_CARDS;
        }

        memcpy(&testG, &G, sizeof(struct gameState));

        baronRe(&G, currentPlayer, playerChoice);

        if(playerChoice == 0){
            if(testG.supplyCount[estate] > 0){
                testG.numBuys++;
                testG.discard[currentPlayer][testG.discardCount[currentPlayer]] = estate;
                testG.supplyCount[estate]--;
                testG.discardCount[currentPlayer]++;
            }
        }
        else{
            cardFound = -1;

            for(int j = 0; j < testG.handCount[currentPlayer]; j++){
                if(testG.hand[currentPlayer][j] == estate){
                    cardFound = j;
                    break;
                }
            }

            if(cardFound == -1){
                if(testG.supplyCount[estate] > 0){
                    testG.numBuys++;
                    testG.discard[currentPlayer][testG.discardCount[currentPlayer]] = estate;
                    testG.supplyCount[estate]--;
                    testG.discardCount[currentPlayer]++;
                }
            }
            else{
                testG.numBuys++;
                testG.coins += 4;
                testG.playedCards[testG.playedCardCount] = estate;
                testG.playedCardCount++;
                testG.discard[currentPlayer][testG.discardCount[currentPlayer]] = estate;
                testG.discardCount[currentPlayer]++;
                
                for(int j = 0; j < testG.handCount[currentPlayer]; j++){
                    testG.hand[currentPlayer][j] = testG.hand[currentPlayer][j + 1];
                }
            }
        }

        printf("Expected coins = %d, Actual coins = %d\n", testG.coins, G.coins);
        printf("Expected numBuys = %d, Actual numBuys = %d\n", testG.numBuys, G.numBuys);
        printf("Expected Estate supplyCount = %d, Actual Estate supplyCount = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);

        if(memcmp(&G, &testG, sizeof(struct gameState)) == 0){
            printf("PASS\n");
            testPassed++;
        }
        else{
            printf("FAIL\n");
            testFailed++;
        }
    }
    
    printf("Number of tests passed: %d\n", testPassed);
    printf("Number of tests failed: %d\n", testFailed);
    printf("\n>>>>> Testing complete for Baron <<<<<\n\n");

    return 0;
}