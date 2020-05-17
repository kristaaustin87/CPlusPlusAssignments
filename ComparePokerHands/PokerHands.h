#ifndef POKERHANDS_POKERHANDS_H
#define POKERHANDS_POKERHANDS_H
#include <vector>
#include <string>


class PokerHands {

public:

    //constructor
    PokerHands();

    //logic to determine the hand
    int analyzeHand(std::vector<std::string> handInput);

    //process input of each card to make sure they are valid
    bool validateHand(std::vector<std::string> handInput);

    //replace K,Q,J,A with number for sorting and analysis
    void convertToTwo(std::vector<std::string> handInput, char cardSuits[]);

    //validate cards are within bounds and suits are one of the four
    bool validateCards(char cardSuits[]);

    //look for same numbers
    int lookForMatches(int counter);

    //get the high card for equal matches
    int getHighCard(int counter);

    //get the high card for three kind matches
    int getthreeKindNumber();

    //get the high card for two kind matches
    int getTwoKindNumberOne();
    int getTwoKindNumberTwo();

    int getFourKindNumber();

private:

    //list of hands in ranking order
    enum hands {
        Invalid,
        HighCard,
        OnePair,
        TwoPair,
        ThreeofAKind,
        Straight,
        Flush,
        FullHouse,
        FourofAKind,
        StraightFlush,
    };

    int sortedCards[5];

    int threeKindNumber;

    int twoKindNumberOne;

    int twoKindNumberTwo;

    int fourKindNumber;

};


#endif //POKERHANDS_POKERHANDS_H
