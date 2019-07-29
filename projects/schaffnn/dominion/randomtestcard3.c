/**************************************************************** 
* Title: randomtestcard3.c
* Author: Nicholas Schaffner
* Last Modified: 07/28/19
* OSU Email Address: schaffnn@oregonstate.edu
* Course Number/Section: CS362-400
* Description: This random test suite tests the tributeCase function located in the dominion.c file.
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

int tributeCase(struct gameState *state, int currentPlayer, int nextPlayer, int tributeRevealedCards[]);

int main() {
    srand(time(NULL));
    int seed = 1000;
    int testPassed = 0;
    int testFailed = 0;
    int currentPlayer, nextPlayer;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int tributeRevealedCards[2] = {-1, -1};
    int numPlayers = 0;

    printf("\n----------------- randomtestcard3.c Testing Card: Tribute -----------------\n");

    for(int i = 0; i < 1000000; i++){
        memset(&G, 0, sizeof(struct gameState));
        memset(&testG, 0, sizeof(struct gameState));

        while(numPlayers == 0 || numPlayers == 1){
            numPlayers = rand() % 5;
        }

        initializeGame(numPlayers, k, seed, &G);                                                             // Initialize game

        currentPlayer = rand() % numPlayers;

        if(currentPlayer + 1 < numPlayers){
            nextPlayer = currentPlayer + 1;
        }
        else{
            nextPlayer = 0;
        }

        G.playedCardCount = rand() % MAX_DECK;
        G.deckCount[currentPlayer] = rand() % MAX_DECK;
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

        G.numPlayers = numPlayers;
        G.whoseTurn = currentPlayer;

        memcpy(&testG, &G, sizeof(struct gameState));

        tributeCase(&G, currentPlayer, nextPlayer, tributeRevealedCards);
        
        if(testG.deckCount[nextPlayer] + testG.discardCount[nextPlayer] <= 1){
            if(testG.deckCount[nextPlayer] == 1){
                tributeRevealedCards[0] = testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1];
                testG.deckCount[nextPlayer]--;
            }
            else if(testG.discardCount[nextPlayer] == 1){
                tributeRevealedCards[0] = testG.discard[nextPlayer][testG.discardCount[nextPlayer] - 1];
                testG.discardCount[nextPlayer]--;               
            }
            else{
                ;                                                                                               /* No action taken because the next player doesn't have any cards to reveal */
            }     
        }
        else if(testG.deckCount[nextPlayer] == 0){
            testG.deckCount[nextPlayer] = testG.discardCount[nextPlayer] - 2;
            testG.discardCount[nextPlayer] = 0;                                                                
        }
        else{
            tributeRevealedCards[0] = testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1];
            testG.deckCount[nextPlayer]--;
            tributeRevealedCards[1] = testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1];
            testG.deckCount[nextPlayer]--;            
        }

        if(tributeRevealedCards[0] == tributeRevealedCards[1]){
            tributeRevealedCards[1] = -1;
        }

        for(int j = 0; j < 2; j++){
	        if (tributeRevealedCards[j] == copper || tributeRevealedCards[j] == silver || tributeRevealedCards[j] == gold){
	            testG.coins += 2;
	        }    
	        else if (tributeRevealedCards[j] == estate || tributeRevealedCards[j] == duchy || tributeRevealedCards[j] == province || tributeRevealedCards[j] == gardens || tributeRevealedCards[j] == great_hall){
	            if(testG.deckCount[currentPlayer] >= 2){
                    testG.handCount[currentPlayer] += 2;
                    testG.deckCount[currentPlayer] -= 2;
                }
                else if(testG.deckCount[currentPlayer] == 1){
                    if(testG.discardCount[currentPlayer] >= 1){
                        testG.handCount[currentPlayer] += 2;
                        testG.deckCount[currentPlayer] = testG.discardCount[currentPlayer] - 1;
                        testG.discardCount[currentPlayer] = 0;  
                    }
                    else{
                        testG.handCount[currentPlayer] += 1;
                        testG.deckCount[currentPlayer]--;                        
                    }
                }
                else{
                    if(testG.discardCount[currentPlayer] >= 2){
                        testG.handCount[currentPlayer] += 2;
                        testG.deckCount[currentPlayer] = testG.discardCount[currentPlayer] - 2;
                        testG.discardCount[currentPlayer] = 0;  
                    }
                    else if(testG.discardCount[currentPlayer] == 1){
                        testG.handCount[currentPlayer] += 1;
                        testG.deckCount[currentPlayer] = testG.discardCount[currentPlayer] - 1;
                        testG.discardCount[currentPlayer] = 0;  
                    }
                    else{
                        ;
                    }  
                }
	        }
	        else{                                                     
	            testG.numActions += 2;
	        }
        }

        printf("Expected numActions = %d, Actual numActions = %d\n", testG.numActions, G.numActions);
        printf("Expected coins = %d, Actual coins = %d\n", testG.coins, G.coins);
        printf("Expected handCount = %d, Actual handCount = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]);

        if(testG.numActions == G.numActions && testG.coins == G.coins && testG.handCount[currentPlayer] == G.handCount[currentPlayer]){
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
    printf("\n>>>>> Testing complete for Tribute <<<<<\n\n");

    return 0;
}