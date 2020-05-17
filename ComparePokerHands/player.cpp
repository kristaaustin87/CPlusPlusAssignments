#include "player.h"
#include <random>
#include <iostream>


player::player(bool isNPC, int reserveSize): hand(PokerHands()), isComputerPlayer(isNPC), reserve(reserveSize),
                                             didFold(false){

}

void player::recieveCards(std::string card){
    cards.push_back(card);

    if(cards.size() == 5){
        score = hand.analyzeHand(cards);
    }
}

int player::bet() {
    int bet;
    if (isComputerPlayer){
        bet = computerPlayerBet();
    }
    else{
        bet = humanPlayerBet();
    }

    reserve -= bet;
    return bet;
}

int player::computerPlayerBet() {

    std::random_device seed;
    std::uniform_int_distribution<int> range(1,reserve);
    int bet = range(seed);
    std::cout<<"The next bet is: "<<bet<<std::endl;

    return bet;
}

int player::humanPlayerBet() {

    std::cout<<"Your hand is: "<<std::endl;
    printCards();

    int bet;
    bool isValidBet = false;

    while (!isValidBet){
        std::cout<<"Your current reserve is " << reserve <<std::endl << "Enter your bet: " << std::endl;
        std::cin>>bet;
        if (bet > 0 && bet <= reserve){
            isValidBet = true;
        }
        else{
            std::cout<<"That is not a valid bet!";
        }
    }

    return bet;
}

int player::analyzeHand() {
    return score;
}

std::vector<std::string>& player::getCards() {
    return cards;
}

void player::printCards() {
    for(int i = 0; i < 5; i++){
                std::cout << cards[i];
                std::cout << " ";
            }
    std::cout<<std::endl;
}

