#include <iostream>
#include <limits> // for managing invalid inputs
#include <Windows.h> // Sleep()

#include "classes.hpp"

using namespace std;

int play_tictactoe(); // the tic tac toe game itself


int main() {

    bool replay = true;

    while (replay) {
        play_tictactoe();
        
        // make sure input is valid
        string answer;
        while ((cout << "Do you wish to replay? [y/n]\n") &&
        (!(cin >> answer) || !(answer == "y" || answer == "n"))) {
            cout << "Invalid input. ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');            
        }

        // apply answer
        if (answer == "n") {
            replay = false;
        }
    }

    cout << "Thank you for playing.\n\n";
    system("pause");
    return 0;
}


/* starts a game against a computer opponent moving optimally (minimax)
   returns the game score (-1, 0 or 1) */
int play_tictactoe() {
    srand(time(NULL)); // random seed
    float delay = 0.5;  // delay in seconds between text (for easier reading)

    GameBoard gameboard;
    ComputerPlayer computerplayer;

    /*
    starts the turn cycle
    user goes first, computer goes second
    repeat until 3 Xs or Os in a row are registered
    */
    while (gameboard.check_end() == 2) {
        cout << "\nCurrent ";
        gameboard.show_state();
        Sleep(2000*delay);

        /*
        ***player turn***
        */

        // make sure input is valid
        int target_square;
        while ((cout << "Enter the square number for your mark:\n") &&
        (!(cin >> target_square) || target_square < 1 || target_square > 9) ||
        gameboard.get_entry(target_square) == "X" || gameboard.get_entry(target_square) == "O") {
            cout << "Invalid entry. ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // if it is, place mark on chosen square
        gameboard.set_entry(target_square);
        
        // skip computer turn if game already over
        if (gameboard.check_end() != 2) {
            break;
        }

        // ***computer turn***
        Sleep(1000*delay);
        cout << "The computer acts:\n";
        Sleep(1000*delay);
        computerplayer.execute_minimax(gameboard);
        Sleep(2000*delay);
    }        

    Sleep(1000*delay);

    // print information on game end
    cout << "\nThe game is over. ";
    if (gameboard.check_end() == -1) {
        cout << "The player wins. ";
    }
    else if (gameboard.check_end() == 0) {
        cout << "The game is a draw. ";
    }
    else if (gameboard.check_end() == 1) {
        cout << "The computer wins. ";
    }
    cout << "End ";
    gameboard.show_state();

    return gameboard.check_end();
}