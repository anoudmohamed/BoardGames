#ifndef _4X4X_O_H
#define _4X4X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

template <typename T>
class X_O_Board:public Board<T> {
public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

// #include <iostream>
// #include <iomanip>
// #include <cctype>  // for toupper()

// using namespace std;

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    //initialize "O" in the board
    for(int j = 0; j < this->columns; j++){
        if(j == 0 || j == 2){
            this->board[0][j] = 'O';
        }
        if(j == 1 || j == 3){
            this->board[3][j] = 'O';
        }
    }
    //initialize "X" in the board
    for(int j = 0; j < this->columns; j++){
        if(j == 0 || j == 2){
            this->board[3][j] = 'X';
        }
        if(j == 1 || j == 3){
            this->board[0][j] = 'X';
        }
    }

    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
            return true;
        }
        else if(mark != 0){
            cout << "\nPlease enter the position of your token that you want to move, (0 to 3) separated by spaces: ";
            int i, j;
            cin >> i >> j;
            // Validate selected token position
            if(this->board[i][j] == 0 || this->board[i][j] != mark){
                cout << "Move is not valid";
                return false;
            }
            // Check if the move is to an adjacent cell
                if(x == i-1 && y == j){
                    this->n_moves++;
                    this->board[x][y] = toupper(mark);
                    this->board[i][j] = 0;
                    return true;
                }
                if(x == i && y == j+1){
                    this->n_moves++;
                    this->board[x][y] = toupper(mark);
                    this->board[i][j] = 0;
                    return true;
                }
                if(x == i+1 && y == j){
                    this->n_moves++;
                    this->board[x][y] = toupper(mark);
                    this->board[i][j] = 0;
                    return true;
                }
                if(x == i && y == j-1){
                    this->n_moves++;
                    this->board[x][y] = toupper(mark);
                    this->board[i][j] = 0;
                    return true;
                }
                else{
                    cout << "Move is not valid";
                    return false; // Move is not valid
                }
            
        }
    }
    cout << "Move is not valid";
    return false; // Move is not valid
}

// Display the board and the pieces on it
template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 20 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 3) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 3
    y = rand() % this->dimension;
}







#endif //_4X4X_O_H