#ifndef ACM_SUS_H
#define ACM_SUS_H
#include "BoardGame_Classes.h"
# include <bits/stdc++.h>

class SUSBoard : public Board<char> {
public:
    SUSBoard() {
        rows = 3;
        columns = 3;
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            for (int j = 0; j < columns; ++j) {
                board[i][j] = ' ';
            }
        }
    }

    bool update_board(int x, int y, char symbol) override {
        if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << " " << board[i][j] << " ";
                if (j < columns - 1) cout << "|";
            }
            cout << endl;
            if (i < rows - 1) cout << "---|---|---" << endl;
        }
        cout << "\n";
    }

    int count_sus_sequences(char symbol) {
        int count = 0;

        for (int i = 0; i < rows; ++i) {
            if (board[i][0] == 'S' && board[i][1] == 'U' && board[i][2] == 'S') count++;
            if (board[0][i] == 'S' && board[1][i] == 'U' && board[2][i] == 'S') count++;
        }

        if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') count++;
        if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') count++;
        return count;
    }

    bool is_win() override {
        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns;
    }

    bool game_is_over() override {
        return is_draw();
    }

    ~SUSBoard() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }
};

class SUSPlayer : public Player<char> {
public:
    int score;

    SUSPlayer(string n, char symbol) : Player(n, symbol), score(0) {}
    SUSPlayer(char symbol) : Player(symbol), score(0) {}

    void getmove(int& x, int& y) override {
        cout << name << ", enter your move (row and column): ";
        cin >> x >> y;
    }

    void increment_score() {
        score++;
    }
};

class SUSRandomPlayer : public RandomPlayer<char> {
public:
    SUSRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {
        srand(std::time(0));
    }

    void getmove(int& x, int& y) override {
        x = rand() % 3;
        y = rand() % 3;
        cout << "Computer chooses: " << x << " " << y << endl;
    }
};
# endif