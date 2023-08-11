#include <iostream>
#include <limits> // for managing invalid inputs
#include <Windows.h> // Sleep()

#include "classes.hpp"

int play_tictactoe(); // the tic tac toe game itself


int main() {

    bool replay = true;

    while (replay) {
        play_tictactoe();
        
        // make sure input is valid
        std::string answer;
        while ((std::cout << "\n Do you wish to replay? [y/n]\n") &&
        (!(std::cin >> answer) || !(answer == "y" || answer == "n"))) {
            std::cout << " Invalid input. ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');            
        }

        // apply answer
        if (answer == "n") {
            replay = false;
        }
    }

    std::cout << " Thank you for playing.\n\n";
    system("pause");
    return 0;
}


/* starts a game against a computer opponent moving optimally (minimax)
   returns the game score (-1, 0 or 1) */
int play_tictactoe() {
    srand(time(NULL)); // random seed
    float delay = 0.5;  // delay in seconds between text (for easier reading)

    GameBoard gameboard;
    // debugging
    /* GameBoard gameboard("O", "2", "3",
                        "4", "X", "6",
                        "7", "8", "9"); */
    // end debugging
    ComputerPlayer computerplayer;

    /*
    starts the turn cycle
    user goes first, computer goes second
    repeat until 3 Xs or Os in a row are registered
    */
    while (gameboard.check_end() == 2) {
        gameboard.show_state();
        Sleep(2000*delay);

        /*
        ***player turn***
        */

        // make sure input is valid
        int target_square;
        while ((std::cout << " Enter the square number for your mark:\n") &&
        (!(std::cin >> target_square) || target_square < 1 || target_square > 9) ||
        gameboard.get_entry(target_square) == "X" || gameboard.get_entry(target_square) == "O") {
            std::cout << " Invalid entry. ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        // if it is, place mark on chosen square
        gameboard.set_entry(target_square);
        
        // skip computer turn if game already over
        if (gameboard.check_end() != 2) {
            break;
        }

        gameboard.show_state();
        
        // ***computer turn***
        Sleep(1000*delay);
        std::cout << " The computer acts:\n";
        Sleep(1000*delay);
        computerplayer.execute_minimax(gameboard);
        Sleep(3000*delay);
    }        

    // print information on game end
    gameboard.show_state();
    Sleep(1000*delay);

    std::cout << "\n The game is over. ";
    if (gameboard.check_end() == -1) {
        std::cout << "The player wins. ";
    }
    else if (gameboard.check_end() == 0) {
        std::cout << "The game is a draw. ";
    }
    else if (gameboard.check_end() == 1) {
        std::cout << "The computer wins. ";
    }

    return gameboard.check_end();
}