#ifndef PYRAMIDALTICTACTOE_H
#define PYRAMIDALTICTACTOE_H
#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Pyramic_X_O_Board : public Board<T> {
public:
    Pyramic_X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    T get_winner();

private:
    vector<int> row_sizes = {1, 3, 5};
    T winner;
};

template <typename T>
Pyramic_X_O_Board<T>::Pyramic_X_O_Board() {
    this->rows = row_sizes.size();
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[row_sizes[i]];
        for (int j = 0; j < row_sizes[i]; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    this->winner = 0;
}

template <typename T>
bool Pyramic_X_O_Board<T>::update_board(int x, int y, T mark) {
    if (x < 0 || x >= this->rows || y < 0 || y >= row_sizes[x] || this->board[x][y] != 0) {
        return false;
    }
    this->board[x][y] = toupper(mark);
    this->n_moves += (mark == 0 ? -1 : 1);
    return true;
}

template <typename T>
void Pyramic_X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << string((5 - row_sizes[i]) * 2, ' ');
        for (int j = 0; j < row_sizes[i]; j++) {
            char cell = this->board[i][j];
            cout << "[" << (cell == 0 ? ' ' : cell) << "]";
        }
        cout << endl;
    }
}
template <typename T>
bool Pyramic_X_O_Board<T>::is_win() {

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= row_sizes[i] - 3; j++) {
            char symbol = this->board[i][j];
            if (symbol != 0 &&
                symbol == this->board[i][j + 1] &&
                symbol == this->board[i][j + 2]) {
                this->winner = symbol;
                return true;
            }
        }
    }


    for (int col = 0; col < row_sizes.back(); col++) {
        for (int row = 0; row <= this->rows - 3; row++) {
            if (col < row_sizes[row] && col < row_sizes[row + 1] && col < row_sizes[row + 2]) {
                char symbol = this->board[row][col];
                if (symbol != 0 &&
                    symbol == this->board[row + 1][col] &&
                    symbol == this->board[row + 2][col]) {
                    this->winner = symbol;
                    return true;
                }
            }
        }
    }


    if (this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[0][0] != 0) {
        this->winner = this->board[0][0];
        return true;
    }
    if (this->board[0][1] == this->board[1][1] && this->board[1][1] == this->board[2][1] && this->board[0][1] != 0) {
        this->winner = this->board[0][1];
        return true;
    }
    if (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != 0) {
        this->winner = this->board[0][2];
        return true;
    }


    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) {
        this->winner = this->board[0][0];
        return true;
    }


    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0) {
        this->winner = this->board[0][2];
        return true;
    }

    return false;
}

template <typename T>
bool Pyramic_X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Pyramic_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
T Pyramic_X_O_Board<T>::get_winner() {
    return this->winner;
}

#endif