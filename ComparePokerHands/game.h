#ifndef POKERHANDS_GAME_H
#define POKERHANDS_GAME_H
#include <vector>
#include <string>
#include "player.h"


class game {

public:

    //should initialize deck
    game();

    //should initialize computer players & call dealCards
    void setUpGame();

    //should shuffle the deck & deal to players & call takeBets
    void dealCards();

    //should take bets/folds from players and increase bettingRounds counter & call compare
    void takeBets();

    //should compare hands & declare winner
    void compare();


    void shuffle();

private:

    //vector to hold players
    std::vector<player> players;

    //array of strings to hold cards + suits
    std::string deck[51];

    int numberAdditionalPlayers;

    int pot;

};


#endif //POKERHANDS_GAME_H
