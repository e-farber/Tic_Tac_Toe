#include <string>

using namespace std;


// store and access information about the game state
class GameBoard {
    
    string squares[9]; // index for 3x3 board
    bool player_turn;  // true = player turn; false = computer turn
    int filled_squares;

    public:
        GameBoard(); // constructor
        ~GameBoard(); // destructor

        // methods
        string get_entry(int const &square_number);
        bool get_player_turn();
        void set_entry(int const &square_number);
        void switch_turn();
        void show_state();
        int check_end();
};


// acts as a simple computer opponent (random moves)
class ComputerPlayer {

    public:
        ComputerPlayer();
        ~ComputerPlayer();

        // methods
        void take_turn(GameBoard &gameboard);
};


// minimizes loss chance, maximizes win chance 
class MiniMaxAlgorithm {

    public:
        MiniMaxAlgorithm();
        ~MiniMaxAlgorithm();

        // methods
        void execute();

};