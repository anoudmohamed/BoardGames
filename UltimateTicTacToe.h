
#ifndef FRIST_PROGECT_ULTIMATETICTACTOE_H
#define FRIST_PROGECT_ULTIMATETICTACTOE_H


#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

template <typename T>
class SmallBoard {
private:
    T board[3][3];

public:
    SmallBoard() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = ' ';
    }

    bool update_board(int x, int y, T symbol) {
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') {
            return false;
        }
        board[x][y] = symbol;
        return true;
    }

    T get_cell(int x, int y) const {
        return board[x][y];
    }

    void display_board() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << "---------\n";
        }
    }

    bool is_win() {
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return true;
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return true;
        }
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return true;
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return true;

        return false;
    }

    bool is_draw() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] == ' ')
                    return false;
        return true;
    }
};


template <typename T>
class UltimateTicTacToe : public Board<T> {
private:
    SmallBoard<T>* smallerBoards[3][3];
    T mainBoard[3][3];
    bool activeBoards[3][3];

public:
    UltimateTicTacToe() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                smallerBoards[i][j] = new SmallBoard<T>();
                mainBoard[i][j] = ' ';
                activeBoards[i][j] = true;
            }
        }
        this->rows = 3;
        this->columns = 3;
    }

    ~UltimateTicTacToe() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                delete smallerBoards[i][j];
    }

    bool update_board(int x, int y, T symbol) override {
        int mainX = x / 3, mainY = y / 3;
        int smallX = x % 3, smallY = y % 3;

        if (!activeBoards[mainX][mainY]) {
            return false;
        }

        if (smallerBoards[mainX][mainY]->update_board(smallX, smallY, symbol)) {
            if (smallerBoards[mainX][mainY]->is_win()) {
                mainBoard[mainX][mainY] = symbol;
                activeBoards[mainX][mainY] = false;
            }
            return true;
        }

        return false;
    }


    void display_board() override {
        for (int i = 0; i < 3; ++i) {
            for (int row = 0; row < 3; ++row) {
                for (int j = 0; j < 3; ++j) {
                    for (int col = 0; col < 3; ++col) {
                        cout << smallerBoards[i][j]->get_cell(row, col);
                        if (col < 2) cout << " ";
                    }
                    if (j < 2) cout << " | ";
                }
                cout << endl;
            }
            if (i < 2) cout << "-----------------------\n";
        }
    }

    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            if (mainBoard[i][0] != ' ' && mainBoard[i][0] == mainBoard[i][1] && mainBoard[i][1] == mainBoard[i][2])
                return true;
            if (mainBoard[0][i] != ' ' && mainBoard[0][i] == mainBoard[1][i] && mainBoard[1][i] == mainBoard[2][i])
                return true;
        }
        if (mainBoard[0][0] != ' ' && mainBoard[0][0] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][2])
            return true;
        if (mainBoard[0][2] != ' ' && mainBoard[0][2] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][0])
            return true;

        return false;
    }

    bool is_draw() override {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (mainBoard[i][j] == ' ')
                    return false;
        return true;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class UltimateHumanPlayer : public Player<T> {
public:
    UltimateHumanPlayer(string n, T symbol) : Player<T>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << " (" << this->getsymbol() << "), it's your turn.\n";

        while (true) {
            cout << "Enter your move as a single board position (row and column 0-8): ";
            cin >> x >> y;

            if (cin.fail() || x < 0 || x > 8 || y < 0 || y > 8) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter numbers between 0 and 8.\n";
            } else {
                break;
            }
        }
    }
};



#endif //FRIST_PROGECT_ULTIMATETICTACTOE_H
