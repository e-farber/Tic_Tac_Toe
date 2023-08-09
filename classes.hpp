#include <string>
#include <vector>
#include <deque>


// store and access information about the game state
class GameBoard {
    
    std::string squares[9]; // index for 3x3 board (array)
    bool player_turn;  // true = player turn; false = computer turn
    int filled_squares;

    public:
        GameBoard(); // default constructor
        GameBoard(std::string first, std::string second, std::string third,   // parametrized constructor
                   std::string fourth, std::string fifth, std::string sixth,
                   std::string seventh, std::string eigth, std::string ninth, bool comp_starts = false);
        ~GameBoard(); // destructor

        // ***methods***
        // getter functions
        std::string get_entry(int const &square_number);
        int get_filled_squares();
        std::vector<std::string> get_board_state();
        std::vector<int> get_empty_squares();
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
        std::vector<int> calc_best_move(
            GameBoard gameboard,
            std::vector<std::string> current_board_state,
            int recdep = 0
        );

        void execute_minimax(GameBoard &gameboard);
};