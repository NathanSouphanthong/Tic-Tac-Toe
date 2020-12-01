// *****************************************
// Student Name: Nathan Souphanthong, Carl Lerdorf
// Assignment 2
// a4_q1
//
// I hereby declare that this code, submitted for credit for the course SYDE121, is a product of my own efforts.
// This coded solution has not been plagiarized from other sources and has not been knowingly plagiarized by others.
//
// Project: Tic Tac Toe Simulator
// Purpose: Create a 4X4 tic tac toe 2 player game.
//
//*********************************************

/*
 
 Testing scenarios:
 - Horizontal win (for X player and O player)
 - Vertical win (for X player and O player)
 - Diagonal win from top left to bottom right (for X player and O player)
 - Diagonal win from top right to bottom left (for X player and O player)
 - Player continuing to play
 - Player ending game
 - Checked to see if player input updated the board
 -check to see if first turn alternates after every repeat game
 -Checked if invalid inputs would cause the program to break
 */

#include <iostream>
#include <iomanip>
using namespace std;


//global variable constants
const int X_PLAYER = 1;
const int O_PLAYER = 2;

//function declaration
void execute_tic_tac_toe();
//PURPOSE: execute game loop
//  INPUT: none
//  OUTPUT: none

void print_board(char board[4][4]);
//PURPOSE: Print formatted board to the consle
//  INPUT: board - char array 4x4 to represent game board
//  OUTPUT: void board values outputted to consle

bool check_sum(int sum, int& winner);
//PURPOSE:check if the sum of 4 characters corresponds to X or O
//  INPUT: sum - integer value of the ascii sum of the rows
//          winner - int variable that records winner of game
//  OUTPUT: bool - true if there was a win present on the board, also changed
//          winner int variable by reference to corresponding winner

bool check_horizontal(char board[4][4], int& winner);
//PURPOSE: check every horizontal row sum to determine if a winner was found
//  INPUT:board - char array 4x4 to represent game board
//        winner - int variable that records winner of game
//  OUTPUT:bool - true if winner was found

bool check_vertical(char board[4][4], int& winner);
//PURPOSE:check every vertical column sum to determine if a winner was found
//  INPUT:board - char array 4x4 to represent game board
//        winner - int variable that records winner of game
//  OUTPUT:bool - true if winner was found

bool check_diagonal(char board[4][4], int& winner);
//PURPOSE:check every diagonal row sum to determine if a winner was found
//  INPUT:board - char array 4x4 to represent game board
//         winner - int variable that records winner of game
//  OUTPUT:bool - true if winner was found

char get_user_input(int player_num,char board[4][4]);
//PURPOSE: gather acceptable user input [1-16] and check if it can be applied to board
//  INPUT: player_num - int number to represent the player X or O's turn
//         board - char array 4x4 to represent game board
//  OUTPUT:char  - returns the char that the user selected for the board

bool check_win(char board[4][4], int& winner);
//PURPOSE: check if a horizontal, vertical or diagonal win was found
//  INPUT: board - char array 4x4 to represent game board
//         winner - int variable that records winner of game
//  OUTPUT: bool - returns true if either a horizontal, vertical or diagonal win was found

void update_board(char character_to_update, int player,char board[4][4]);
//PURPOSE: update board with the char that player X or O selected
//  INPUT: character_to_update - char value that corresponds to position on the board to update
//         player - integer variable that represents either X or O turn
//         board - char array 4x4 to represent game board
//  OUTPUT: void

void reset_board(char board[4][4]);
//PURPOSE: repopulate board with numbers [1-16]
//  INPUT: board - char array 4x4 to represent game board
//  OUTPUT: void


int main() {
    execute_tic_tac_toe();
}

//The main loop of the game, manages turns and the game
void execute_tic_tac_toe(){
    char board[4][4];
    int winner = 0;  // 0 = nobody,  1 = X_PLAYER,  2 = O_PLAYER
    int player_turn;
    int player_first = X_PLAYER;
    int moves_count = 1;
    bool continue_game = true;
    bool is_winner = false;
    
    //populate array with numbers [1-16]
    reset_board(board);
    
    while(continue_game){//continuous game loop
        
        //assign first turn based on player_first variable
        player_turn = player_first == X_PLAYER ? X_PLAYER : O_PLAYER;
        
        
        while(is_winner == false && moves_count <= 16){ //check if //winner is found or moves exceeded limit
            if(player_turn == X_PLAYER){ //x player turn
                print_board(board);
                update_board(get_user_input(X_PLAYER,board),X_PLAYER,board);
                is_winner = check_win(board, winner);
                player_turn = O_PLAYER;
                
            }else if(player_turn == O_PLAYER){ //y player turn
                print_board(board);
                update_board(get_user_input(O_PLAYER,board),O_PLAYER,board);
                is_winner = check_win(board, winner);
                player_turn = X_PLAYER;
            }
            moves_count++;
        }
        
        //check for winning condition
        if(is_winner == false && moves_count >= 16){
            cout << "It's a Tie!\n";
        }else if(is_winner == true && winner == X_PLAYER){
            cout << "X Player Wins!\n";
        }else if(is_winner == true && winner == O_PLAYER) {
            cout << "O Player Wins!\n";
        }
        //output board with the final result
        print_board(board);
        
    
        //check if player wants to continue game
        cout << "Would you like to continue playing (Enter \'N' to Exit or any key to continue): ";
        char y_or_n;
        cin >> y_or_n;
        
        if(y_or_n == 'N'){
            continue_game = false;
        }else{
            //reset game parameters to start a new game
            moves_count = 1;
            reset_board(board);
            is_winner = false;
            winner = 0;
            
            //change who has the first turn at the next game if game is replayed
            player_first = player_first == X_PLAYER ? O_PLAYER: X_PLAYER;
        }
    }
}

void print_board(char board[4][4]) {
    for(int i = 0; i <16; i++) {
        char c = board[i/4][i%4];
        string fill = "";
        if (i%4>0) {
            if (int(c) > 9 && int(c) < 17)
                fill = "   ";
            else
                fill = "    ";
        } else if (int(c) < 10 || int(c) > 16)
            fill = " ";
        
        cout << fill << (c >= 'O' ? string(1, c) : to_string(int(c))) << (i % 4 == 3 ? "\n" : "");
    }
    cout<<endl;
}

//Checks if a sum of 4 characters corresponds to an X or an O
bool check_sum(int sum, int& winner) {
    switch (sum) {
        case 4*'X': //X wins
            winner = X_PLAYER;
            return true;
        case 4*'O': //O wins
            winner = O_PLAYER;
            return true;
    }
    return false;
}

bool check_horizontal(char board[4][4], int& winner) { //Adds the row together to see if it equals a number corresponding to a player's symbol
    
    for (int i = 0; i < 4; i++) {
        int sum = 0;
        
        for (int j = 0; j < 4; j++)
        sum+=board[i][j];
        
        if (check_sum(sum,winner)) return true;
        
    }
    return false;
}

bool check_vertical(char board[4][4], int& winner) { //Same as check_horizontal() but for collums
    for (int i = 0; i < 4; i++) {
        int sum = 0;
        
        for (int j = 0; j < 4; j++)
        sum+=board[j][i];
        
        if (check_sum(sum,winner)) return true;
        
    }
    return false;
}

bool check_diagonal(char board[4][4], int& winner) { //Adds the two diagonals together individually and checks each one
    
    int sum = 0;
    
    for (int i = 0; i < 4; i++)
    sum+=board[i][i];
    
    if (check_sum(sum,winner)) return true;
    
    sum = 0;
    
    for (int i = 0; i < 4; i++)
    sum+=board[3-i][i];
    
    if (check_sum(sum,winner)) return true;
    
    return false;
}

char get_user_input(int player_num, char board[4][4]){ //Will keep asking for user input until user inputs acceptable number
    int input;
    bool acceptable_input = false;
    
    do{
        cout << "Enter number [1-16] player " << (player_num == X_PLAYER ? "X" : "O") << ": ";
        cin >> input;
        if(input >= 1 && input <= 16){
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    if((int)board[i][j] == (char)input) {
                        acceptable_input = true;
                    }
                }
            }
        }
    }while(acceptable_input == false);
    
    cout << endl;
    return (char)input;
}

bool check_win(char board[4][4], int& winner) { //returns true if a player has won
    return (check_horizontal(board, winner) || check_vertical(board,winner) || check_diagonal(board,winner));
}

//Will update a particular character according to the player's input
void update_board(char character_to_update, int player, char board[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(board[i][j] == character_to_update){
                if(player == X_PLAYER){
                    board[i][j] = 'X';
                } else if (player == O_PLAYER){
                    board[i][j] = 'O';
                }
            }
        }
    }
}

//Resets the board to just numbers [1, 16]
void reset_board(char board[4][4]){
    for (int i = 0; i < 16; i++)
    board[i/4][i%4] = i+1;
}


