#include <iostream>
#include <stdlib.h>     //srand, rand
#include <ctime>

#include "classes.hpp"

/*
first: definitions for GameBoard class
second: definitions for ComputerPlayer class (approx. line 240)
*/

// ***constructor definition***
GameBoard::GameBoard() {
    for (int square_number = 0; square_number <= 8; square_number++) { // fill squares with
        squares[square_number] = std::to_string(square_number +1);        // numbers 1 through 9
    }

    player_turn = false;
    filled_squares = 0;
}

GameBoard::GameBoard (std::string first, std::string second, std::string third,
                   std::string fourth, std::string fifth, std::string sixth,
                   std::string seventh, std::string eighth, std::string ninth, bool comp_starts) {

    squares[0] = first;
    squares[1] = second;
    squares[2] = third;
    squares[3] = fourth;
    squares[4] = fifth;
    squares[5] = sixth;
    squares[6] = seventh;
    squares[7] = eighth;
    squares[8] = ninth;

    player_turn = comp_starts;

    filled_squares = 0;
    for (auto &it: squares) {
        if (it == "X" || it == "O") {
            filled_squares++;
        }
    }
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
std::string GameBoard::get_entry(int const &square_number) { 
    return squares[square_number-1];
}

// returns amount of filled squares (int)
int GameBoard::get_filled_squares() { 
    return filled_squares;
}


// returns list of string values containing the current entries of all squares
std::vector<std::string> GameBoard::get_board_state() {
    std::vector<std::string> current_board_state;

    for (auto &c: squares) {
        current_board_state.push_back(c);
    }
    return current_board_state;
}


// returns vector of int values containing the entries (1-9) of currently empty squares (ascending order)
std::vector<int> GameBoard::get_empty_squares() {
    std::vector<int> empty_squares;

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
    system("cls"); // clear output

    if (filled_squares == 0) {
        std::cout << " Welcome!\n";
    }
    else {
        std::cout << std::endl;
    }

    if (check_end() != 2) {
        std::cout << " End game state:\n";
    }
    else {
        std::cout << " Current game state:\n";
    }
    
    for (int square_number = 0; square_number <= 8; square_number++) {
        
        // shift right by 10 spaces for easier readability
        if (square_number == 0 || square_number == 3 || square_number == 6) {
            std::cout << "          ";
        }

        // entries
        std::cout << squares[square_number];

        // grid lines and line breaks
        if (square_number == 2 || square_number == 5) {
            std::cout << "\n          __|___|__" << std::endl;
        }
        else if (square_number == 8) {
            std::cout << std::endl << "            |   |   \n";
        }
        else {
            std::cout << " | ";
        }
    }
    std::cout << std::endl;
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
    // std::cout << "\nComputer player joined the game.\n";
}


// ***ComputerPlayer destructor***
ComputerPlayer::~ComputerPlayer() {
    // std::cout << "\nComputer player has left the game.\n";
}


// ***ComputerPlayer methods***
// computer player makes a random move      ### unused in favor of minimax algorithm ###
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
std::vector<int> ComputerPlayer::calc_best_move(GameBoard gameboard, std::vector<std::string> current_board_state, int recdep) {
    int game_score = gameboard.check_end(); // 2 if not yet over; -1, 0, 1 for game end

    if (game_score == 2) {
        std::vector<int> empty_squares = gameboard.get_empty_squares();
        std::vector<std::vector<int>> squares_and_scores;
        squares_and_scores.reserve(40320); /* 40320 = 8!, which is approximately the amount of moves
        needed to be stored max. TODO Easy to optimize by exchanging 8! with (9 - filled_squares)! */

        for (auto &empty_square_index : empty_squares) {
            GameBoard testing_board = gameboard;

            testing_board.set_entry(empty_square_index);
            std::vector<std::string> current_board_state = testing_board.get_board_state();

            // debugging
            /* std::string depth(recdep*7, ' ');
            std::cout << depth;
            if (gameboard.get_player_turn()) {
                std::cout << "O on " << empty_square_index << std::endl;
            }
            else {
                std::cout << "X on " << empty_square_index << std::endl;
            } */
            // end debugging
            

            int end_score = calc_best_move(testing_board, current_board_state, recdep + 1)[1];

            squares_and_scores.push_back({empty_square_index, end_score});
            
            // debugging
            /* std::cout << depth << "[RD " << recdep << "] Squares and scores: {";
            for (auto &it : squares_and_scores) {
                std::cout << ", {" << it[0] << ", " << it[1] << "}";
            }
            std::cout << "}" << std::endl; */
            // end debugging
        }

        /* TODO: possible optimization: stop following path after loss has already occured
        and check next path instead */

        int best_square = squares_and_scores[0][0];
        int best_score = squares_and_scores[0][1];
        for (auto &square_and_score : squares_and_scores) {

            /* player marks (default 'X') get assigned scores by minimizing
            -> decide how to react by choosing maximum player score */
            if (gameboard.get_player_turn()) {
                if (square_and_score[1] > best_score) {
                best_score = square_and_score[1];
                best_square = square_and_score[0];

                // debugging
                /* std::string depth(recdep*7, ' ');
                std::cout << depth << "[max] updating feedback to " << best_score
                          << " from square " << best_square << std::endl; */
                // end debugging
                }
            }

            /* AI marks (default 'O') get assigned scores by maximizing
            -> decide how to react by choosing minimum AI score */
            else {
                if (square_and_score[1] < best_score) {
                best_score = square_and_score[1];
                best_square = square_and_score[0];

                // debugging
                /* std::string depth(recdep*7, ' ');
                std::cout << depth << "[min] updating feedback to " << best_score
                          << " from square " << best_square << std::endl; */
                // end debugging
                }
            }
        }

        // debugging
        /* std::string depth(recdep*7, ' ');
        std::cout << depth << "feeding back " << best_score << std::endl; */
        // end debugging

        return {best_square, best_score};
    }


    else {
        return {-13, game_score}; /* first entry (-13) doesn't matter;
        in case an end state is reached, only the game_score is fed back */
    }
}



// calculates and executes a best possible move
void ComputerPlayer::execute_minimax(GameBoard &gameboard) {
    std::vector<std::string> current_board_state =  gameboard.get_board_state();

    int square_number = calc_best_move(gameboard, current_board_state)[0];
    gameboard.set_entry(square_number);
    
    // confirm by printing message
    std::cout << " A mark was placed on square " << square_number << " by the ";
    if (gameboard.get_player_turn()) {
        std::cout << "player.\n";
    }
    else {
        std::cout << "computer.\n";
    }
    // TODO: possible optimization: hard-code first decision (e.g. if center -> edge, if edge -> corner)
}