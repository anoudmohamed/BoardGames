#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

class WordTicTacToeBoard : public Board<char> {
public:
    WordTicTacToeBoard() {
        rows = 3;
        columns = 3;
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            fill(board[i], board[i] + columns, ' ');
        }
        n_moves = 0; // Initialize number of moves
    }

    ~WordTicTacToeBoard() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    bool update_board(int x, int y, char letter) override {
        if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
            board[x][y] = letter;
            n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "\nCurrent Board: \n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << "[" << board[i][j] << "] ";
            }
            cout << endl;
        }
    }

    bool is_win() override {
        // Check rows, columns, and diagonals for valid words
        for (int i = 0; i < 3; ++i) {
            // Check row
            string row = {board[i][0], board[i][1], board[i][2]};
            if (isValidWord(row)) return true;
            // Check column
            string col = {board[0][i], board[1][i], board[2][i]};
            if (isValidWord(col)) return true;
        }

        // Check diagonals
        string diag1 = {board[0][0], board[1][1], board[2][2]};
        string diag2 = {board[0][2], board[1][1], board[2][0]};
        if (isValidWord(diag1) || isValidWord(diag2)) return true;

        return false;
    }

    bool is_draw() override {
        return n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    void loadWords(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            exit(1);  // Exit if the file can't be opened
        }

        string word;
        while (getline(file, word)) {
            // Convert word to uppercase to avoid case mismatch
            for (char& c : word) {
                c = toupper(c);
            }
            dictionary.insert(word); // Add the word to the dictionary
        }

        file.close();
        if (dictionary.empty()) {
            cerr << "The dictionary is empty. Exiting game." << endl;
            exit(1);
        }
    }

private:
    unordered_set<string> dictionary;

    bool isValidWord(const string& word) {
        return dictionary.find(word) != dictionary.end();
    }
};

class HumanPlayer : public Player<char> {
public:
    HumanPlayer(string n) : Player(n, ' ') {} // No symbol needed

    void getmove(int& x, int& y) override {
        cout << name << "'s turn. Enter row and column (0-2): ";
        cin >> x >> y;
    }

    void getletter(char& letter) {
        while (true) {
            cout << "Enter a letter (A-Z): ";
            cin >> letter;

            // Check if the letter is valid (uppercase and a single character)
            if (isalpha(letter) && isupper(letter) && letter >= 'A' && letter <= 'Z') {
                break;  // Valid letter input
            } else {
                cout << "Invalid letter. Please enter a single uppercase letter." << endl;
            }
        }
    }
};

class RandomComputerPlayer : public RandomPlayer<char> {
public:
    RandomComputerPlayer() : RandomPlayer<char>(' ') {}

    void getmove(int& x, int& y) override {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 2);
        x = dis(gen);
        y = dis(gen);
        cout << "Computer's move: " << x << ", " << y << endl;
    }

    char getRandomLetter() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 25);
        return 'A' + dis(gen);
    }
};

int main() {
    WordTicTacToeBoard board;
    string filename;

    cout << "Enter the dictionary file name: ";
    cin >> filename;
    board.loadWords(filename);

    HumanPlayer player1("Player 1");
    HumanPlayer player2("Player 2");
    RandomComputerPlayer computerPlayer;
    Player<char>* players[2];

    char choice;
    cout << "Do you want to play against a computer? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        players[0] = &player1;
        players[1] = &computerPlayer;
    } else {
        players[0] = &player1;
        players[1] = &player2;
    }

    int currentPlayer = 0; // 0 for player1, 1 for player2/computer

    while (!board.game_is_over()) {
        board.display_board();

        cout << "change the roles.\n";

        int x, y;
        char letter;

        // Get the letter from the current player
        if (dynamic_cast<HumanPlayer*>(players[currentPlayer])) {
            dynamic_cast<HumanPlayer*>(players[currentPlayer])->getletter(letter);
        } else {
            letter = dynamic_cast<RandomComputerPlayer*>(players[currentPlayer])->getRandomLetter();
            cout << "Computer's letter: " << letter << endl;
        }

        // Get the move coordinates from the current player
        players[currentPlayer]->getmove(x, y);

        // Try to update the board
        if (!board.update_board(x, y, letter)) {
            cout << "Invalid move. Try again." << endl;
            continue; // Skip the rest of the loop and let the same player retry
        }

        // Check if the game is over
        if (board.is_win()) {
            board.display_board();
            cout << "We have a winner!" << endl;
            return 0;
        }

        if (board.is_draw()) {
            board.display_board();
            cout << "The game is a draw!" << endl;
            return 0;
        }

        // Switch to the other player
        currentPlayer = 1 - currentPlayer;
    }

    return 0;
}


