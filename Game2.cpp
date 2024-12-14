//كود شغال

#include "BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>

class FourInARowBoard : public Board<char> {
public:
    FourInARowBoard() {
        rows = 6;
        columns = 7;
        n_moves = 0;
        board = new char* [rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            fill(board[i], board[i] + columns, ' ');
        }
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= columns || board[0][x] != ' ') return false;
        for (int i = rows - 1; i >= 0; --i) {
            if (board[i][x] == ' ') {
                board[i][x] = symbol;
                ++n_moves;
                return true;
            }
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << (board[i][j] == ' ' ? ' ' : board[i][j]);
                if (j < columns - 1) cout << " | ";
            }
            cout << endl;
            if (i < rows - 1) {
                for (int j = 0; j < columns; ++j) {
                    cout << "---";
                    if (j < columns - 1) cout << "-";
                }
                cout << endl;
            }
        }
    }

    bool is_win() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] != ' ' && (
                        check_direction(i, j, 0, 1) ||
                        check_direction(i, j, 1, 0) ||
                        check_direction(i, j, 1, 1) ||
                        check_direction(i, j, 1, -1)))
                    return true;
            }
        }
        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

private:
    bool check_direction(int x, int y, int dx, int dy) {
        char symbol = board[x][y];
        for (int k = 1; k < 4; ++k) {
            int nx = x + k * dx, ny = y + k * dy;
            if (nx < 0 || ny < 0 || nx >= rows || ny >= columns || board[nx][ny] != symbol)
                return false;
        }
        return true;
    }
};

class FourInARowPlayer : public Player<char> {
public:
    FourInARowPlayer(string n, char symbol) : Player<char>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << name << "'s turn (" << symbol << "). Enter column (0-6): ";
        cin >> x;
        y = -1;
    }
};

class FourInARowRandomPlayer : public RandomPlayer<char> {
public:
    FourInARowRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {
        srand(time(0));
    }

    void getmove(int& x, int& y) override {
        do {
            x = rand() % 7;
        } while (boardPtr->update_board(x, 0, this->symbol) == false);
        y = -1;
    }
};

Player<char>* create_player(string name, char symbol) {
    int choice;
    cout << "Choose type for " << name << " (1 - Human, 2 - Computer): ";
    cin >> choice;

    if (choice == 1) {
        return new FourInARowPlayer(name, symbol);
    }
    else if (choice == 2) {
        return new FourInARowRandomPlayer(symbol);
    }
    else {
        cout << "Invalid choice. Defaulting to Human player." << endl;
        return new FourInARowPlayer(name, symbol);
    }
}

int main() {
    FourInARowBoard board;

    cout << "Welcome to Four in a Row!" << endl;


    Player<char>* players[2];
    players[0] = create_player("Player 1", 'X');
    players[1] = create_player("Player 2", 'O');


    players[0]->setBoard(&board);
    players[1]->setBoard(&board);


    GameManager<char> gameManager(&board, players);
    gameManager.run();


    delete players[0];
    delete players[1];
    return 0;
}

