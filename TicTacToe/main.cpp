#include <iostream>
#include "TicTacToe.h"

int main() {

    //var to hold status
    int cont = 4;

    //vars to hold user input
    int rowInput;
    int colInput;

    //create new game instance
    TicTacToe newGame;

    //use a do/while loop to keep game running until the end
    do{
        //request user input
        std::cout << "Please enter the row of the desired move:";
        std::cin >> rowInput;

        //request user input
        std::cout << "Please enter the column of the desired move:";
        std::cin >> colInput;

        cont = newGame.move((rowInput-1), (colInput-1));

        if(cont == 3){
            std::cout << "Invalid move! Please select an empty space." << std::endl;
            continue;
        }

        newGame.printBoard();


    }while(cont  > 2);

    switch(cont){
        case 0 :
            std::cout << "You have won!" << std::endl;
            break;
        case 1 :
            std::cout << "You have lost!" << std::endl;
            break;
        case 2 :
            std::cout << "It's a tie!" << std::endl;
            break;
        default :
            break;
    }

    return 0;
}
