#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 3;
// Check if the current player has won
bool check_win(char table[][SIZE])
{
    // Check the rows //[i=0 so and first row is 1]
    for (int i = 0; i < SIZE; i++)
    {
        if (table[i][0] == table[i][1] && table[i][1] == table[i][2] && table[i][0] != ' ')
        {
            return true;
        }
    }

    // Check the columns
    for (int j = 0; j < SIZE; j++)
    {
        if (table[0][j] == table[1][j] && table[1][j] == table[2][j] && table[0][j] != ' ')
        {
            return true;
        }
    }

    // Check the diagonals
    if (table[0][0] == table[1][1] && table[1][1] == table[2][2] && table[0][0] != ' ')
    {
        return true;
    }
    if (table[0][2] == table[1][1] && table[1][1] == table[2][0] && table[0][2] != ' ')
    {
        return true;
    }

    // If no win condition is met, return false
    return false;
}


// Display the tic-tac-toe table
void display_table(char table[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (table[i][j] == ' ') {
                cout << "_ ";
            } else {
                cout << table[i][j] << " ";
            }
        }
        cout << endl;
    }
}


// Check if the tic-tac-toe table is full
bool check_table_full(char table[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (table[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Check if the move made by player 1 is legal
bool check_legal_option(char table[][SIZE], int row, int col) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && table[row][col] == ' ') {
        return true;
    }
    return false;
}

// Generate a move for player 2
void generate_player2_move(char table[][SIZE]) 
{
    bool move_generated = false;
    while (!move_generated) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        if (table[row][col] == ' ') {
            table[row][col] = 'X';
            move_generated = true;
        }
    }
}

// Global constants
const char PLAYER_1_PIECE = 'O';
const char PLAYER_2_PIECE = 'X';

int main()

{
    cout<<"The current state of the game is: "<<endl;
    // Declare and initialize the game board
    char board[SIZE][SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

    // Seed the random number generator
    srand(time(NULL));

    // Game loop
    bool game_over = false;
    bool player1_turn = true;
    while (!game_over)
    {
        // Display the current state of the game
        display_table(board);

        // Check if the game is over
        if (check_table_full(board))
        {
            cout << "Game over, no player wins." << endl;
            game_over = true;
            break;
        }

        // Ask for the current player's move
        int row, col;
        if (player1_turn)
        {
            cout << "Player 1 enter your selection [row col], Press SpaceBar after entering row to enter col at valid location: ";
            cin >> row >> col;
            

            // Check if the move is legal
            while (!check_legal_option(board, row-1, col-1))
            {
                cout << "Invalid move. Please try again." << endl;
                cout << "Player 1 enter your selection [row col]: ";
                cin >> row >> col;
            }

            // Update the board with the current player's move
            board[row-1][col-1] = PLAYER_1_PIECE;
        }
        else
        {//cout << "Player 2 has entered [row col]" << row << col << endl;

            generate_player2_move(board);
        
             check_win(board);


            cout << "Player 2 has entered [row col]: " << endl;

        }

        // Check if the game is over
        if (check_table_full(board))
        {
            cout << "Game over, no player wins." << endl;
            game_over = true;
            break;
        }

        // Check if the current player has won
        bool win = false;
        char current_piece = player1_turn ? PLAYER_1_PIECE : PLAYER_2_PIECE;
        for (int i = 0; i<3; i++)
        {
            //chcek the rows
            if (board[i][0]==current_piece && board[i][1]== current_piece && board[i][2]==current_piece)
            {
                win = true;
                break;
            }
                    // Check the columns
        if (board[0][i] == current_piece && board[1][i] == current_piece && board[2][i] == current_piece)
        {
            win = true;
            break;
        }
    }

    // Check the diagonals
    if (board[0][0] == current_piece && board[1][1] == current_piece && board[2][2] == current_piece)
    {
        win = true;
    }
    if (board[0][2] == current_piece && board[1][1] == current_piece && board[2][0] == current_piece)
    {
        win = true;
    }

    // If the current player has won, print out a message and end the game
    if (win)
    {
        if (player1_turn)
        {
            cout << "Congratulations, Player 1 wins!" << endl;
        }
        else
        {
            cout << "Congratulations, Player 2 wins!" << endl;
        }
        game_over = true;
        break;
    }

    // Switch to the other player's turn
    player1_turn = !player1_turn;
}

return 0;
}
