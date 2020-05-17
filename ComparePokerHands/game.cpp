#include "game.h"
#include <string>
#include <iostream>
#include "player.h"
#include <random>
#include "PokerCompare.h"

game::game() : pot(0) {

    for(int i = 0; i < 52; i++){

        //get card and suit based on location in deck
        int cardNubmer = (i % 13) + 1;
        int cardSuit = i / 13;

        std::string suitLetter;
        switch(cardSuit){
            case 0:
                suitLetter = 'H';
                break;
            case 1:
                suitLetter = 'D';
                break;
            case 2:
                suitLetter = 'S';
                break;
            case 3:
                suitLetter = 'C';
                break;
        }

        std::string cardString;
        switch(cardNubmer){
            case 1:
                cardString = 'A';
                break;
            case 11:
                cardString = 'J';
                break;
            case 12:
                cardString = 'Q';
                break;
            case 13:
                cardString = 'K';
                break;
            default:
                cardString = std::to_string(cardNubmer);
        }

        deck[i] = cardString + suitLetter;
    }
}

void game::setUpGame() {

    //prompt for reserve size
    int reserveSize;

    std::cout<<"Please enter the size of the desired starting amount for each player: "<< std::endl;
    std::cin>>reserveSize;

    //add human player
    players.push_back(player(false, reserveSize));

    //prompt for amount of additional players
    int additionalPlayers = 0;

    while(additionalPlayers <= 0 || additionalPlayers > 6) {
        std::cout << "Please enter the number of additional computer players between 1 and 6: " << std::endl;
        std::cin >> additionalPlayers;
    }

    for(int i = 1; i <= additionalPlayers; i++){
        players.push_back(player(true, reserveSize));
    }

    dealCards();
}

void game::shuffle() {
    for(int i = 51; i > 0; i--){
        std::random_device seed;
        std::uniform_int_distribution<int> range(0,i);
        int targetPosition = range(seed);
        if(deck[i] != deck[targetPosition]){
            swap(deck[i], deck[targetPosition]);
        }
    }
}

void game::dealCards() {
    shuffle();

    int cardCounter = 0;
    int playerCount = players.size();

    //to count out five rounds of dealing
    while(cardCounter < 5){

        //to track position in the player vector
        int playerPosition = 0;

        for(int i = cardCounter * playerCount; i < (cardCounter * playerCount) + playerCount; i ++){

            players[playerPosition].recieveCards(deck[i]);

            playerPosition++;
        }

        cardCounter++;
    }

    takeBets();
}

void game::takeBets() {

    for(player p : players){
        int bet = p.bet();
        pot += bet;
    }

    std::cout<<"The pot is: "<<pot<<std::endl;

    compare();
}

void game::compare() {

    int highScore = 0;
    int highScorePlayer;

    PokerCompare compareHands;

    for(int i = 0; i < players.size(); i++){

        int currentScore = players[i].analyzeHand();

        if(currentScore > highScore){
            highScore = currentScore;
            highScorePlayer = i;
        }

        else if(currentScore == highScore){
            int evaluator = compareHands.compareTwoHands(players[i].getCards(),
                    players[highScorePlayer].getCards());
            if(evaluator == 2){
                highScore = currentScore;
                highScorePlayer = i;
            }
        }

        players[i].printCards();
    }

    std::cout<<"The winner is Player "<<highScorePlayer + 1<<std::endl;
}
