#ifndef POKERHANDS_POKERCOMPARE_H
#define POKERHANDS_POKERCOMPARE_H
#include "PokerHands.h"
#include <vector>
#include <string>


class PokerCompare {

public:
    //constructor
    PokerCompare();

    //
    int compareTwoHands(std::vector<std::string> handOne,
    std::vector<std::string> handTwo);

    int evaluateValues(int value1, int value2);

private:

    //PokerHands objects stored here so they can be easily accessed by functions
    PokerHands PokerHandOne;
    PokerHands PokerHandTwo;

    //vars to check if threes and pairs have been checked
    bool checkThree;
    bool checkFour;
    int  checkPair;
    int highCardCounter;


};


#endif //POKERHANDS_POKERCOMPARE_H
