#include "PokerCompare.h"
#include "PokerHands.h"
#include <iostream>

//constructor
PokerCompare::PokerCompare() : checkThree(false), checkPair(0), highCardCounter(5), checkFour(false),
PokerHandOne(), PokerHandTwo(){
}

int PokerCompare::compareTwoHands(std::vector<std::string> handOne,
                            std::vector<std::string> handTwo){

    //iterate through possibilities to find ranks
    return evaluateValues(PokerHandOne.analyzeHand(handOne), PokerHandTwo.analyzeHand(handTwo));

}

int PokerCompare::evaluateValues(int value1, int value2){

    int evaluator;

    //check if valid
    if(value1 == 0 || value2 == 0){
        evaluator =  -1;
    }

    //if the hands are different
    else if(value1 > value2){
        evaluator = 2;
    }
    else if(value1 < value2){
        evaluator = 1;
    }

    //if the hands are the same, need to do further checks

    //check four of a kind if not already
    else if(value1 == 8 && !checkFour){
        checkFour = true;
        evaluator = evaluateValues(PokerHandOne.getFourKindNumber(), PokerHandTwo.getFourKindNumber());
    }

    else if(!checkThree && (value1 ==7 || value1 ==4)){
        checkThree = true;
        evaluator = evaluateValues(PokerHandOne.getthreeKindNumber(), PokerHandTwo.getthreeKindNumber());
    }

    else if(checkPair == 0 && (value1 == 7 || value1 == 3 || value1 == 2)){
        checkPair += value1;
        evaluator = evaluateValues(PokerHandOne.getTwoKindNumberOne(), PokerHandTwo.getTwoKindNumberOne());
    }

    else if(checkPair == 3){
        checkPair++;
        evaluator = evaluateValues(PokerHandOne.getTwoKindNumberTwo(), PokerHandTwo.getTwoKindNumberTwo());
    }

    else if(highCardCounter != 0){
        highCardCounter--;
        evaluator = evaluateValues(PokerHandOne.getHighCard(highCardCounter),
                PokerHandTwo.getHighCard(highCardCounter));
    }

    else{
        //if nothing caught above, values are equal
        return 0;
    }

    return evaluator;

}