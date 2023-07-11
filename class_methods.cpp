#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <ctime>

#include "classes.hpp"

using namespace std;

/*
first: definitions for GameBoard class
second: definitions for ComputerPlayer class (approx. line 150)
third: definitions for MiniMaxAlgorithm class (approx line 190)
*/


// ***constructor definition***
GameBoard::GameBoard() {
    for (int square_number = 0; square_number<=8; square_number++) { // fill squares with
        squares[square_number] = to_string(square_number +1);        // numbers 1 through 9
    }
    cout << "\nGameboard constructed.\n";

    player_turn = true;

    filled_squares = 0;
}


// ***destructor definition***
GameBoard::~GameBoard() {
    cout << "\nGameboard destroyed.\n";
}



// ***method definitions***
bool GameBoard::get_player_turn() {
    return player_turn;
}


// toggles GameBoard::player_turn
void GameBoard::switch_turn() {
    if (player_turn) {
        player_turn = false;
    } else {
        player_turn = true;
    }
}


// returns entry in chosen square number (1-9)
string GameBoard::get_entry(int const &square_number) { 
    return squares[square_number-1];
}


/*
changes entry in chosen square number (1 through 9) to "X" or "O"
and increments filled_squares by 1.
*/
void GameBoard::set_entry(int const &square_number) {
    if (player_turn) {
        squares[square_number-1] = "X"; // X if player acts
    }
    else {
        squares[square_number-1] = "O"; // O if computer acts
    }

    // increment filled_squares by 1
    filled_squares++;
    cout << "A mark was placed on square " << square_number << ".\n";
}


void GameBoard::show_state() {      // prints all entries in 3x3 form
    cout << "game state:\n";

    for (int square_number = 0; square_number <= 8; square_number++) {
        cout << squares[square_number];

        // grid lines and line breaks
        if (square_number == 2 || square_number == 5) {
            cout << "\n__|___|__" << endl;
        }
        else if (square_number == 8) {
            cout << endl << "  |   |   \n";
        }
        else {
            cout << " | ";
        }
    }
    cout << endl;
}

/*
return values:
-1  - player wins
0   - draw
1   - computer wins
2   - game not yet over
*/
int GameBoard::check_end() {
    // vertical check
    for (int square_number = 0; square_number <= 2; square_number++) {
        if (squares[square_number] == squares[square_number + 3] &&
        squares[square_number + 3] == squares[square_number + 6]) {
            if (player_turn) {
                return -1;
            }
            else {
                return 1;
            }
        }
    }

    // horizontal check
    for (int square_number = 0; square_number <= 6; square_number += 3) {
        if (squares[square_number] == squares[square_number + 1] &&
        squares[square_number + 1] == squares[square_number + 2]) {
            if (player_turn) {
                return -1;
            }
            else {
                return 1;
            }
        }
    }

    // diagonal checks
    if ((squares[0] == squares[4] && squares[4] == squares[8]) ||
    (squares[2] == squares[4] && squares[4] == squares[6])) {
        if (player_turn) {
                return -1;
            }
            else {
                return 1;
            }
    }

    // check if all squares full (game ends in a draw)
    if (filled_squares >= 9) {
        return 0;
    }
    
    // else (game is not yet over)
    return 2;
}




/*
definitions for ComputerPlayer class
*/

// ***ComputerPlayer constructor***
ComputerPlayer::ComputerPlayer() {
    cout << "\nComputer player joined the game.\n";
}


// ***ComputerPlayer destructor***
ComputerPlayer::~ComputerPlayer() {
    cout << "\nComputer player has left the game.\n";
}

// ***ComputerPlayer methods***
void ComputerPlayer::take_turn(GameBoard &gameboard) {

    // switch player turn
    gameboard.switch_turn();
    
    // random number 1-9
    int random_number = rand() % 9 + 1;

    // choose next empty square if chosen one is already marked 
    while (gameboard.get_entry(random_number) == "X" || gameboard.get_entry(random_number) == "O") {
        random_number = (random_number) % 9 + 1;
    }
    
    // place mark on randomly chosen square
    gameboard.set_entry(random_number);

    // switch turn if game is not yet over
    if (gameboard.check_end() == 2) {
        gameboard.switch_turn();
    }
}




/*
definitions for MiniMaxAlgorithm class
*/

// ***MiniMaxAlgorithm constructor***
MiniMaxAlgorithm::MiniMaxAlgorithm() {
    cout << "\nMiniMaxAlgorithm ready.\n";
}


// ***MiniMaxAlgorithm destructor***
MiniMaxAlgorithm::~MiniMaxAlgorithm() {
    cout << "\nEnd of MiniMaxAlgorithm.\n";
}


// ***MiniMaxAlgorithm methods***
void MiniMaxAlgorithm::execute() {

}
/*
TODO
1 Store the current state (values) of the tic-tac-toe board in an array.
  (For any empty cell, the cell’s index will get stored as its present content).
2 Get an array list of only the empty cells’ indexes.
3 Check and confirm if a specific player has won the game.
4 Recursively invoke minimax on each of the board’s empty cells.
5 Return a score for every possible move for both player X and player O.
6 Out of all the returned scores, choose the best one (the highest) that is
  guaranteed to minimize the human player’s possibilities of winning the game.
*/