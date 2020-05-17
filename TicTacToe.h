#ifndef T3_TICTACTOE_H
#define T3_TICTACTOE_H

#include <string>

class TicTacToe{

public:
    //constructor
    TicTacToe();

    //movement function
    int move(int row, int col);

    //print the current board state
    //this implementation should allow this function to be used for client with terminal or GUI
    void printBoard();

    //check the game status
    int gameStatus(int row, int col);

    //computer side movement
    int computerMove();

private:
    //array to hold board state
    char gameBoard [3][3];

    enum states {
        WON,
        LOST,
        TIE,
        INVALID,
        INPROGRESS
    };

    //counter to track number of moves made
    int counter;

    //ints to track last moves
    int userRow;

    int userCol;

    int compRow;

    int compCol;
};

#endif //T3_TICTACTOE_H
