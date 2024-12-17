#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

template <typename T>
class Tic_Tac_Toe_Board:public Board<T> {
public:
    Tic_Tac_Toe_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    int count_sequence(T symbol);

};

template <typename T>
class Tic_Tac_Toe_Player : public Player<T> {
public:
    Tic_Tac_Toe_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Tic_Tac_Toe_Random_Player : public RandomPlayer<T>{
public:
    Tic_Tac_Toe_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};


//---------------------------------------Implementation:

// Constructor for X_O_Board
template <typename T>
Tic_Tac_Toe_Board<T>::Tic_Tac_Toe_Board() {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Tic_Tac_Toe_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

//show the current state of the board
template <typename T>
void Tic_Tac_Toe_Board<T>::display_board() {
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

template <typename T>
//counting the number of three-in-a-row to decide who is the winner
int Tic_Tac_Toe_Board<T>::count_sequence(T symbol){
    int counter = 0;
    //finding the success sequence horizontally
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->columns-2; j++){
            if(this->board[i][j] == symbol && this->board[i][j+1] == symbol && this->board[i][j+2] == symbol)
                ++counter;       
        }
    }
    //finding the success sequence vertically
    for(int i = 0; i < this->rows-2; i++){
        for(int j = 0; j < this->columns; j++){
            if(this->board[i][j] == symbol && this->board[i+1][j] == symbol && this->board[i+2][j] == symbol)
                ++counter;       
        }
    }
    //finding the success sequence in diagonal
    for(int i = 0; i < this->rows-2; i++){
        for(int j = 0; j < this->columns-2; j++){
            if(this->board[i][j] == symbol && this->board[i+1][j+1] == symbol && this->board[i+2][j+2] == symbol)
                ++counter;       
        }
    }
    //finding the success sequence in anti_diagonal
    for(int i = 0; i < this->rows-2; i++){
        for(int j = 2; j < this->columns; j++){
            if(this->board[i][j] == symbol && this->board[i+1][j-1] == symbol && this->board[i+2][j-2] == symbol)
                ++counter;       
        }
    }

    return counter;


}
template <typename T>
bool Tic_Tac_Toe_Board<T>::is_win(){
    if(this->n_moves == 24){
        if(count_sequence('O') > count_sequence('X')){
            return true;
        }
        if(count_sequence('O') < count_sequence('X')){
            return true;
        }
    }
    else {
            return false;
        }
    
}

template <typename T>
bool Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 24 && !is_win());
}

template <typename T>
bool Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//implementation of the Player constructor
template <typename T>
Tic_Tac_Toe_Player<T>::Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Tic_Tac_Toe_Random_Player<T>::Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 4
    y = rand() % this->dimension;
}




#endif //_5X5X_O_H