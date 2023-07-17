#include <iostream>
#include <stdlib.h>     //srand, rand
#include <ctime>
#include <algorithm> // max_element of deque

#include "classes.hpp"

using namespace std;

/*
first: definitions for GameBoard class
second: definitions for ComputerPlayer class (approx. line 200)
*/


// ***constructor definition***
GameBoard::GameBoard() {
    for (int square_number = 0; square_number <= 8; square_number++) { // fill squares with
        squares[square_number] = to_string(square_number +1);        // numbers 1 through 9
    }

    player_turn = false;
    filled_squares = 0;
}


// ***destructor definition***
GameBoard::~GameBoard() {
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

// returns entry in chosen square number (1-9)
int GameBoard::get_filled_squares() { 
    return filled_squares;
}


// returns list of string values containing the current entries of all squares
vector<string> GameBoard::get_board_state() {
    vector<string> current_board_state;

    for (auto &c: squares) {
        current_board_state.push_back(c);
    }
    return current_board_state;
}


// returns list of int values containing the entries (1-9) of currently empty squares (ascending order)
vector<int> GameBoard::get_empty_squares() {
    vector<int> empty_squares;

    for (auto &c : squares) {
        if (c != "X" && c != "O") {
            empty_squares.push_back(stoi(c));
        }
    }
    
    return empty_squares;
}


/*
changes entry in chosen square number (1 through 9) to "X" or "O" based on player_turn
and increments filled_squares by 1.
*/
void GameBoard::set_entry(int const &square_number) {
    switch_turn();

    if (player_turn) {
        squares[square_number-1] = "X"; // X if player acts
    }
    else {
        squares[square_number-1] = "O"; // O if computer acts
    }

    // increment filled_squares by 1 and confirm
    filled_squares++;
}


// prints all entries in 3x3 form
void GameBoard::show_state() {
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
checks if game is over and returns a score
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
// computer player makes a random move
void ComputerPlayer::random_move(GameBoard &gameboard) {
    
    // random number 1-9
    int random_number = rand() % 9 + 1;

    // choose next empty square if chosen one is already marked 
    while (gameboard.get_entry(random_number) == "X" || gameboard.get_entry(random_number) == "O") {
        random_number = (random_number) % 9 + 1;
    }
    
    // place mark on randomly chosen square
    gameboard.set_entry(random_number);
}


/*
***MinimaxAlgorithm methods***
*/ 

/*
1) checks if end state is reached
2) if not, checks all possible moves until end state is reached
3) on each level, returns list of {square choice, end result}
4) returns to higher level min result if end state was reached after player turn, else returns max result
5) following the same principle, each value on one level is compared and fed back on top
6) for the level the best move was originally to be calculated for, a list with {best square, best score} is returned
*/
vector<int> ComputerPlayer::calc_best_move(GameBoard gameboard, vector<string> current_board_state) {
    int game_score = gameboard.check_end(); // 2 if not yet over; -1, 0, 1 for game end

    if (game_score == 2) {
        vector<int> empty_squares = gameboard.get_empty_squares();
        vector<vector<int>> squares_and_scores;

        for (auto &empty_square_index : empty_squares) {
            GameBoard testing_board = gameboard;

            testing_board.set_entry(empty_square_index);
            vector<string> current_board_state = testing_board.get_board_state();

            int end_score = calc_best_move(testing_board, current_board_state)[1];

            squares_and_scores.push_back({empty_square_index, end_score});

        }

        int best_square;
        int best_score = 0;
        for (auto &square_and_score : squares_and_scores) {

            if (gameboard.get_player_turn()) {
                if (square_and_score[1] >= best_score) {
                best_score = square_and_score[1];
                best_square = square_and_score[0];
                }
            }

            else {
                if (square_and_score[1] <= best_score) {
                best_score = square_and_score[1];
                best_square = square_and_score[0];
                }
            }
        }
        return {best_square, best_score};
    
    }
    else {
        return {-13, game_score};
        // first entry doesn't matter; in case an end state is reached, only the game_score is fed back
    }
}


// calculates and executes a best possible move
void ComputerPlayer::execute_minimax(GameBoard &gameboard) {
    vector<string> current_board_state =  gameboard.get_board_state();

    // gameboard.switch_turn();

    if (gameboard.get_filled_squares() >= 2) {
        int square_number = calc_best_move(gameboard, current_board_state)[0];
        gameboard.set_entry(square_number);
        
        // confirm by printing message
        cout << "A mark was placed on square " << square_number << " by the ";
        if (gameboard.get_player_turn()) {
            cout << "player.\n";
        }
        else {
            cout << "computer.\n";
        }
    }
    // hard coding first choice to save computing time:
    // if computer moves first, place mark in random corner
    else if (gameboard.get_filled_squares() == 0) {  
        int corner_indexes[4] = {1, 3, 7, 9};
        int random_0_to_3 = rand() % 4;
        int square_number = corner_indexes[random_0_to_3];
        gameboard.set_entry(square_number);

        // confirm by printing message
        cout << "A mark was placed on square " << square_number << " by the ";
        if (gameboard.get_player_turn()) {
            cout << "player.\n";
        }
        else {
            cout << "computer.\n";
        }
    }
    /* if computer moves second, place mark in center if free
       if center is already full, place mark in random corner */
    else if (gameboard.get_filled_squares() == 1 && current_board_state[4] == "5") {
        gameboard.set_entry(5);

        // confirm by printing message
        cout << "A mark was placed on square 5 by the ";
        if (gameboard.get_player_turn()) {
            cout << "player.\n";
        }
        else {
            cout << "computer.\n";
        }
    }
    else if (gameboard.get_filled_squares() == 1 && current_board_state[4] != "5") {
        int corner_indexes[4] = {1, 3, 7, 9};
        int random_0_to_3 = rand() % 4;
        int square_number = corner_indexes[random_0_to_3];
        gameboard.set_entry(square_number);

                // confirm by printing message
        cout << "A mark was placed on square " << square_number << " by the ";
        if (gameboard.get_player_turn()) {
            cout << "player.\n";
        }
        else {
            cout << "computer.\n";
        }
    }
}