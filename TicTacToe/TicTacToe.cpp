#include "TicTacToe.h"
#include <iostream>

TicTacToe::TicTacToe() : gameBoard{'-','-','-','-','-','-','-','-','-'}, counter(0){

}

int TicTacToe::move(int row, int col){

    //check that the move is valid
    if(gameBoard[row][col] == '-'){

        //if valid move, set move on board
        gameBoard[row][col] = 'X';
        userRow = row;
        userCol = col;
        counter++;

        //check the current game status
        int status =  gameStatus(userRow, userCol);

        //if still in progress, computer moves
        if (status == 4){
            return computerMove();
        }

        //if game ending status, return proper flag to main
        else{
            return status;
        }
    }

    //if invalid move, return invalid flag to main
    else{
        return states::INVALID;
    }
}

void TicTacToe::printBoard(){

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << gameBoard[i][j];
            std::cout << ' ';
        }
        std::cout << '\n';
    }

}

int TicTacToe::gameStatus(int row, int col) {

    //check counter to see if enough moves have been made for a match to occur
    if(counter < 4){
        return states::INPROGRESS;
    }
    //check the row and column where placement occurred for three matches
    else if((gameBoard[row][0] == gameBoard[row][1] && gameBoard[row][1] == gameBoard[row][2])
    || (gameBoard[0][col] == gameBoard[1][col] && gameBoard[1][col] == gameBoard[2][col])){
        if(gameBoard[row][col] == 'X'){
            return states::WON;
        }
        else{
            return states::LOST;
        }
    }

    //check for matches in diagonals
    else if(row == col || abs(row-col)==2){
        if((gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2])
           || (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0])){
            if(gameBoard[row][col] == 'X'){
                return states::WON;
            }
            else{
                return states::LOST;
            }
        }
    }

    //check for full board
    else if(counter == 9){
        return states::TIE;
    }

    //if none of the above, game still in progress
    return states::INPROGRESS;

}

int TicTacToe::computerMove() {
    //variable to track if computer has made a move
    bool moved = false;
    //in first move place in center or corner
    if(counter == 1){
        if(gameBoard[1][1] == '-'){
            compRow = 1;
            compCol = 1;
        }
        else{
            compRow = 0;
            compCol = 0;
        }
        moved = true;
    }

    if(!moved){
        //set move in open spot of last move row
        for(int j = 0; j < 3; j++){
            if(gameBoard[compRow][j] == '-'){
                compCol = j;
                moved = true;
                break;
            }
        }
    }

    //if no move to be made in row, try column
    if (!moved) {
        for (int i = 0; i < 3; i++) {
            if (gameBoard[i][compCol] == '-') {
                compRow = i;
                moved = true;
                break;
            }
        }
    }

    //if no move made above, find first empty space
    if (!moved){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if (gameBoard[i][j] == '-'){
                    compRow = i;
                    compCol = j;
                    break;
                }
            }
        }
    }

    //set move
    gameBoard[compRow][compCol] = 'O';
    //increase the counter
    counter++;

    return gameStatus(compRow, compCol);
}




