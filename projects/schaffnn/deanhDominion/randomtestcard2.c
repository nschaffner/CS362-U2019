/**************************************************************** 
* Title: randomtestcard2.c
* Author: Nicholas Schaffner
* Last Modified: 08/04/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This random test suite tests the minionRe function located in the dominion.c file provided by deanh.
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

void minionRe(struct gameState *state, int currentPlayer, int choice1, int choice2, int handPos);

int main() {
    srand(time(NULL));
    int seed = 1000;
    int testPassed = 0;
    int testFailed = 0;
    int currentPlayer;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int playerChoice1, playerChoice2;
    int numPlayers = 0;
    int cardPos = 0;

    printf("\n----------------- randomtestcard2.c Testing Card: Minion -----------------\n");

    for(int i = 0; i < 100000; i++){
        memset(&G, 0, sizeof(struct gameState));
        memset(&testG, 0, sizeof(struct gameState));

        while(numPlayers == 0 || numPlayers == 1){
            numPlayers = rand() % 5;
        }

        initializeGame(numPlayers, k, seed, &G);                                                             // Initialize game

        currentPlayer = rand() % numPlayers;
        playerChoice1 = rand() % 2;
        playerChoice2 = rand() % 2;

        printf("Players choice1 = %d\n", playerChoice1);
        printf("Players choice2 = %d\n", playerChoice2);

        G.playedCardCount = rand() % MAX_DECK;
        G.coins = rand() % 100;
        G.numBuys = rand() % 20;
        G.numActions = rand() % 20;

        for(int j = 0; j < numPlayers; j++){
            G.handCount[j] = rand() % 6;
            for(int k = 0; k < G.handCount[j]; k++){
                G.hand[j][k] = rand() % NUM_TOTAL_K_CARDS;
            }

            G.deckCount[j] = rand() % MAX_DECK;
            for(int k = 0; k < G.deckCount[j]; k++){
                G.deck[j][k] = rand() % NUM_TOTAL_K_CARDS;
            }

            G.discardCount[j] = rand() % MAX_DECK;
            for(int k = 0; k < G.discardCount[j]; k++){
                G.discard[j][k] = rand() % NUM_TOTAL_K_CARDS;
            }
        }

        if(G.handCount[currentPlayer] == 0){
            cardPos = 0;
        }
        else{
            cardPos = rand() % G.handCount[currentPlayer];
        }

        G.hand[currentPlayer][cardPos] = minion;

        G.numPlayers = numPlayers;
        G.whoseTurn = currentPlayer;

        memcpy(&testG, &G, sizeof(struct gameState));

        minionRe(&G, currentPlayer, playerChoice1, playerChoice2, cardPos);

        if(playerChoice1 == 1){
            testG.numActions++;
            testG.playedCards[testG.playedCardCount] = testG.hand[currentPlayer][cardPos];
            testG.playedCardCount++;
            testG.hand[currentPlayer][cardPos] = -1;
            testG.handCount[currentPlayer]--;
            testG.coins += 2;
        }
        else{
            testG.numActions++;
            testG.playedCardCount = testG.playedCardCount + testG.handCount[currentPlayer];

            if(testG.deckCount[currentPlayer] >= 4){
                testG.handCount[currentPlayer] = 4;
                testG.deckCount[currentPlayer] = testG.deckCount[currentPlayer] - 4;
            }
            else if(testG.discardCount[currentPlayer] >= 4){
                testG.handCount[currentPlayer] = 4;
                testG.deckCount[currentPlayer] = testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer] - 4;
                testG.discardCount[currentPlayer] = 0;
            }
            else if(testG.discardCount[currentPlayer] + testG.deckCount[currentPlayer] >= 4){
                testG.handCount[currentPlayer] = 4;
                testG.deckCount[currentPlayer] = testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer] - 4;
                testG.discardCount[currentPlayer] = 0;
            }
            else{
                testG.handCount[currentPlayer] = testG.discardCount[currentPlayer] + testG.deckCount[currentPlayer];
                testG.deckCount[currentPlayer] = 0;
                testG.discardCount[currentPlayer] = 0;
            }
            
            for(int j = 0; j < numPlayers; j++){
                if(j != currentPlayer){
                    if(testG.handCount[j] > 4){
                        if(testG.deckCount[j] >= 4){
                            testG.handCount[j] = 4;
                            testG.deckCount[j] = testG.deckCount[j] - 4;
                        }
                        else if(testG.discardCount[j] >= 4){
                            testG.handCount[j] = 4;
                            testG.deckCount[j] = testG.deckCount[j] + testG.discardCount[j] - 4;
                            testG.discardCount[j] = 0;
                        }
                        else if(testG.discardCount[j] + testG.deckCount[j] >= 4){
                            testG.handCount[j] = 4;
                            testG.deckCount[j] = testG.deckCount[j] + testG.discardCount[j] - 4;
                            testG.discardCount[j] = 0;
                        }
                        else{
                            testG.handCount[j] = (testG.discardCount[j] + testG.deckCount[j]);
                            testG.deckCount[j] = 0;
                            testG.discardCount[j] = 0;
                        }
                    }
                }
            }
        }

        printf("Expected numActions = %d, Actual numActions = %d\n", testG.numActions, G.numActions);
        printf("Expected handCount = %d, Actual handCount = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]);
        printf("Expected coins = %d, Actual coins = %d\n", testG.coins, G.coins);

        if(testG.numActions == G.numActions && testG.handCount[currentPlayer] == G.handCount[currentPlayer] && testG.coins == G.coins){
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
    printf("\n>>>>> Testing complete for Minion <<<<<\n\n");

    return 0;
}