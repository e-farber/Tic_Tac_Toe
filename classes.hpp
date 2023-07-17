#include <string>
#include <vector>
#include <deque>

using namespace std;


// store and access information about the game state
class GameBoard {
    
    string squares[9]; // index for 3x3 board (array)
    bool player_turn;  // true = player turn; false = computer turn
    int filled_squares;

    public:
        GameBoard(); // constructor
        ~GameBoard(); // destructor

        // ***methods***
        // getter functions
        string get_entry(int const &square_number);
        int get_filled_squares();
        vector<string> get_board_state();
        vector<int> get_empty_squares();
        bool get_player_turn();
        
        // setter functions
        void set_entry(int const &square_number);
        void switch_turn();

        // derived information
        void show_state();
        int check_end();
};


// stores methods for computer opponent
class ComputerPlayer {

    public:
        ComputerPlayer();
        ~ComputerPlayer();

        // methods
        void random_move(GameBoard &gameboard);

        //methods for minimax-algorithm
        vector<int> calc_best_move(GameBoard gameboard, vector<string> current_board_state);
        void execute_minimax(GameBoard &gameboard);
};