
#ifndef FRIST_PROGECT_NUMERICALTICTACTOE_H
#define FRIST_PROGECT_NUMERICALTICTACTOE_H

#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include "BoardGame1_Classes.h"

using namespace std;

class NumericalTicTacToe : public GameBoard<int> {
private:
    set<int> used_numbers;

public:
    NumericalTicTacToe(int rows = 3, int columns = 3) {
        this->rows = rows;
        this->columns = columns;
        board = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new int[columns]();
        }
    }

    bool update_board(int x, int y, int symbol) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0 || used_numbers.count(symbol) || symbol < 1 || symbol > 9) {
            return false;
        }

        if (n_moves % 2 == 0 && symbol % 2 == 0) {
            return false;
        }
        if (n_moves % 2 == 1 && symbol % 2 != 0) {
            return false;
        }

        board[x][y] = symbol;
        used_numbers.insert(symbol);
        n_moves++;
        return true;
    }

    void display_board() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j] << " ";
                if (j < 2) cout << "| ";
            }
            cout << endl;
            if (i < 2) cout << "---------" << endl;
        }
    }

    bool is_win() override {
        for (int i = 0; i < rows; ++i) {
            if (check_sum(board[i][0], board[i][1], board[i][2])) return true;
        }
        for (int j = 0; j < columns; ++j) {
            if (check_sum(board[0][j], board[1][j], board[2][j])) return true;
        }
        if (check_sum(board[0][0], board[1][1], board[2][2])) return true;
        if (check_sum(board[0][2], board[1][1], board[2][0])) return true;
        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

private:
    bool check_sum(int a, int b, int c) {
        return a != 0 && b != 0 && c != 0 && a + b + c == 15;
    }
};

class Humanplayer : public GamePlayers<int> {
public:
    Humanplayer(const string& n, int symbol) : GamePlayers<int>(n, symbol) {}

    void getmove(int& x, int& y, int& symbol) override {
        while (true) {
            cout << getname() << ", enter your move (row, column, and number): ";
            cin >> x >> y >> symbol;

            if (x >= 0 && x < 3 && y >= 0 && y < 3 && symbol >= 1 && symbol <= 9) {
                break;
            } else {
                cout << "Invalid input. Please enter a valid row, column, and number.\n";
            }
        }
    }
};

class NumericalRandomPlayer : public GamePlayers<int> {
public:
    NumericalRandomPlayer(int symbol) : GamePlayers<int>(symbol) {}

    void getmove(int& x, int& y, int& symbol) override {
        while (true) {
            x = rand() % 3;
            y = rand() % 3;
            symbol = rand() % 9 + 1;

            if ((symbol % 2 == 0 && getsymbol() % 2 == 0) || (symbol % 2 != 0 && getsymbol() % 2 != 0)) {
                if (boardPtr->update_board(x, y, symbol)) {
                    break;
                }
            }
        }
    }
};

#endif //FRIST_PROGECT_NUMERICALTICTACTOE_H