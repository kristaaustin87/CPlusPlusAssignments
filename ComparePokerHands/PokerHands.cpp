#include "PokerHands.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>


//constructor
PokerHands::PokerHands() : threeKindNumber(0), twoKindNumberOne(0), twoKindNumberTwo(0) {

}


int PokerHands::analyzeHand(std::vector<std::string> handInput) {

    //check the length of the string
    if (handInput.size() != 5 || !validateHand(handInput)){
        return hands::Invalid;
    }

    //split vector into two for processing
    char cardSuits[5];

    convertToTwo(handInput, cardSuits);

    //sort the array
    std::sort(sortedCards, sortedCards+5);


    //make sure each charter is within bounds
    if(!validateCards(cardSuits)){
        return hands::Invalid;
    }

    //vars to hold already met conditions
    bool flush = false;
    bool pair = false;
    bool threeKind = false;

    //check for flush condition
    if(cardSuits[0] == cardSuits[1] && cardSuits[1] == cardSuits[2]
       && cardSuits[2] == cardSuits[3] && cardSuits[3] == cardSuits[4]){
        flush = true;
    }

    //check for straight condition
    if(sortedCards[0]+1 == sortedCards[1] && sortedCards[1]+1 == sortedCards[2]
       && sortedCards[2]+1 == sortedCards[3] && sortedCards[3]+1 == sortedCards[4]){
        if(flush){
            return hands::StraightFlush;
        }
        return hands::Straight;
    }

    //if no streak found, but flush is true, there can be no matches
    if(flush){
        return hands::Flush;
    }

    //if no hands already found, look for matches
    for(int i = 0; i < 5; i++){
        //look for matches for each card
        int matches = lookForMatches(i) - i + 1;

        //handle matches
        switch(matches){
            case 4:
                fourKindNumber = sortedCards[i];
                //four matches can only be four of a kind
                return hands::FourofAKind;
            case 3:
                threeKindNumber = sortedCards[i];
                if (pair){
                    //if already found a pair, return full house
                    return hands::FullHouse;
                }
                if(i + 3 >= 2){
                    //if through all cards, return three of a kind
                    return hands::ThreeofAKind;
                }
                threeKind = true;
                break;
            case 2:
                //if no pairs, set the first pair to the current vlaue
                if(twoKindNumberOne == 0){
                    twoKindNumberOne = sortedCards[i];
                }
                if(threeKind){
                    //if already found three of a kind, return full house
                    return hands::FullHouse;
                }
                if(pair){
                    //if the new value is the higher pair, reset high pair value
                    if(twoKindNumberOne < sortedCards[i]){
                        twoKindNumberTwo = twoKindNumberOne;
                        twoKindNumberOne = sortedCards[i];
                    }
                    else{
                        twoKindNumberTwo = sortedCards[i];
                    }
                    //if already found a pair, return two pair
                    return hands::TwoPair;
                }
                if(i > 3){
                    //if through all cards, return pair
                    return hands::OnePair;
                }
                pair = true;
                break;
            case 1:
                if(pair){
                    return hands::OnePair;
                }
                else if(i >= 4){
                    //if no matches found return high card
                    return hands::HighCard + sortedCards[4];
                }
                break;
            default:
                break;
        }

        //skip the ones that are already matched
        i += matches - 1;
    }

    //for any that did not match any patters
    return hands::HighCard;
}

bool PokerHands::validateHand(std::vector<std::string> handInput){

    //make sure none of the cards are exactly the same
    for(int i = 0; i < 5; i++){
        for(int j = i+1; j < 5; j++){
            //make sure none of the cards are exactly the same and have the valid number of chars
            if(handInput[i] == handInput[j] || handInput[i].length() > 3
            || handInput[i].length() < 2){
                return false;
            }
        }
    }

    //return true if no cards match
    return true;

}

void PokerHands::convertToTwo(std::vector<std::string> handInput, char *cardSuits){

    for(int i = 0; i < 5; i ++){

        //to hold the substrings of the vector entries
        std::string number;
        std::string suit;

        //check to see if a 10 has been entered
        if(handInput[i].length() == 3){
            number = handInput[i].substr(0,2);
            suit = handInput[i].substr(2,1);
        }
        else{
            number = handInput[i].substr(0,1);
            suit = handInput[i].substr(1,1);

            //check if single value is K,Q,J, or A and set to number equivalent
            switch (number[0]) {
                case 'K' :
                    number = "13";
                    break;
                case 'Q' :
                    number = "12";
                    break;
                case 'J' :
                    number = "11";
                    break;
                case 'A' :
                    number = "1";
                    break;
                default :
                    break;
            }

        }

        //set the substrings into the arrays
        sortedCards[i] = stoi(number);
        cardSuits[i] = suit[0];
    }
}

bool PokerHands::validateCards(char *cardSuits) {

    //make sure numbers are within bounds
    if(sortedCards[0] < 1 || sortedCards[4] > 14){
        return false;
    }

    //make sure the suit matches one of the four
    for(int i = 0; i < 5; i++){
        if(cardSuits[i] != 'H' && cardSuits[i] != 'D' && cardSuits[i] != 'S' && cardSuits[i] != 'C'){
            return false;
        }
    }

    return true;
}

int PokerHands::lookForMatches(int counter) {

    //if cards match keep looking for matches
    if(sortedCards[counter] == sortedCards[counter+1]){
        counter++;
        counter = lookForMatches(counter);
    }

    return counter;
}

//add ten to not interfere with enums for all get values
int PokerHands::getHighCard(int counter) {
    return sortedCards[counter]+10;
}

int PokerHands::getthreeKindNumber(){
    return threeKindNumber+10;
}

int PokerHands::getTwoKindNumberOne(){
    return twoKindNumberOne+10;
}

int PokerHands::getTwoKindNumberTwo(){
    return twoKindNumberTwo+10;
}

int PokerHands::getFourKindNumber(){
    return fourKindNumber+10;
}

