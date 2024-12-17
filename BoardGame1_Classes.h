
#ifndef _BOARDGAME1_CLASSES_H
#define _BOARDGAME1_CLASSES_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class GameBoard {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:
    virtual bool update_board(int x, int y, T symbol) = 0;
    virtual void display_board() = 0;
    virtual bool is_win() = 0;
    virtual bool is_draw() = 0;
    virtual bool game_is_over() = 0;

    virtual ~GameBoard() {
        for (int i = 0; i < rows; ++i)
            delete[] board[i];
        delete[] board;
    }
};

template <typename T>
class GamePlayers {
protected:
    string name;
    T symbol;
    GameBoard<T>* boardPtr;

public:
    GamePlayers(const string& n, T symbol);
    GamePlayers(T symbol);
    virtual void getmove(int& x, int& y, T& symbol) = 0;
    T getsymbol();
    string getname();
    void setBoard(GameBoard<T>* b);
};

template <typename T>
class GameMaster {
private:
    GameBoard<T>* boardPtr;
    GamePlayers<T>* players[2];

public:
    GameMaster(GameBoard<T>* bPtr, GamePlayers<T>* playerPtr[2]);
    void run();
};

template <typename T>
GameMaster<T>::GameMaster(GameBoard<T>* bPtr, GamePlayers<T>* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

template <typename T>
void GameMaster<T>::run() {
    int x, y, symbol;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i = 0; i < 2; ++i) {
            cout << players[i]->getname() << "'s turn.\n";

            players[i]->getmove(x, y, symbol);

            while (!boardPtr->update_board(x, y, symbol)) {
                cout << "Invalid move! Try again.\n";
                players[i]->getmove(x, y, symbol);
            }

            boardPtr->display_board();

            if (boardPtr->is_win()) {
                cout << players[i]->getname() << " wins!\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "It's a draw!\n";
                return;
            }
        }
    }
}

template <typename T>
GamePlayers<T>::GamePlayers(const string& n, T symbol) {
    this->name = n;
    this->symbol = symbol;
}

template <typename T>
GamePlayers<T>::GamePlayers(T symbol) {
    this->name = "Computer";
    this->symbol = symbol;
}

template <typename T>
T GamePlayers<T>::getsymbol() { return this->symbol; }

template <typename T>
string GamePlayers<T>::getname() { return this->name; }

template <typename T>
void GamePlayers<T>::setBoard(GameBoard<T>* b) { this->boardPtr = b; }

#endif //_BOARDGAME1_CLASSES_H6