#ifndef POKERHANDS_PLAYER_H
#define POKERHANDS_PLAYER_H
#include "PokerHands.h"
#include <vector>



class player {

public:

    //should initialize hand, reserve, & mark human or computer
    player(bool isComputerPlayer, int reserveSize);

    //should accept cards during deal
    void recieveCards(std::string card);

    //should determine if comp or player and send to proper bet & subtract from reserve
    int bet();

    //should return random int
    int computerPlayerBet();

    //should prompt for bet
    int humanPlayerBet();

    int analyzeHand();

    std::vector<std::string> &getCards();

    void printCards();

private:

    int reserve;

    //to hold hand analysis info
    PokerHands hand;

    int score;

    //to hold cards vector during dealing
    std::vector<std::string> cards;

    bool isComputerPlayer;

    bool didFold;

};


#endif //POKERHANDS_PLAYER_H
