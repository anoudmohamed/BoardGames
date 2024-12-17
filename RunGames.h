#ifndef _RUNGAMES_H
#define _RUNGAMES_H

#include<iostream>
#include "BoardGame_Classes.h"
#include "BoardGame1_Classes.h"
#include "4x4X_O.h"
#include "5x5X_O.h"
#include "Misere_X_O.h"
#include "FourInARow.h"
#include "Numerical_X_O.h"
#include "Word_X_O.h"
#include "Pyramic_X_O.h"
#include "SUS.h"
# include "UltimateTicTacToe.h"


using namespace std;

/*************************************************************************************************/
int play4x4TicTacToe(){
    int choice;
    Player<char>* players[2];
    X_O_Board<char>* B = new X_O_Board<char>();
    string playerXName, player2Name;

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new X_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new X_O_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player X. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player O name: ";
    cin >> player2Name;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new X_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new X_O_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player O. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}


/*************************************************************************************************/


int playMisereTicTacToe(){
    int choice;
    Player<char>* players[2];
    Misere_X_O_Board<char>* B = new Misere_X_O_Board<char>();
    string playerXName, player2Name;

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Misere_X_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Misere_X_O_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player X. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player O name: ";
    cin >> player2Name;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Misere_X_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Misere_X_O_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player O. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> inverse_x_o_game(B, players);
    inverse_x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}


/*************************************************************************************************/


int play5x5TicTacToe(){
    int choice;
    Player<char>* players[2];
    Tic_Tac_Toe_Board<char>* B = new Tic_Tac_Toe_Board<char>();
    string playerXName, player2Name;

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Tic_Tac_Toe_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Tic_Tac_Toe_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player O name: ";
    cin >> player2Name;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Tic_Tac_Toe_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Tic_Tac_Toe_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}


/*************************************************************************************************/


int playPyramicTicTacToe(){
    Pyramic_X_O_Board<char> game;
    char players[2] = {'X', 'O'};
    int current_player = 0;

    cout << "Welcome to Pyramidal Tic-Tac-Toe!" << endl;

    while (!game.game_is_over()) {
        game.display_board();
        cout << "Player " << players[current_player] << "'s turn." << endl;

        int x, y;
        cout << "Enter row and column (0-based and separated by spaces): ";
        cin >> x >> y;

        if (!game.update_board(x, y, players[current_player])) {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        current_player = 1 - current_player;
    }

    game.display_board();

    if (game.is_win()) {
        cout << "Player " << game.get_winner() << " wins!" << endl;
    } else if (game.is_draw()) {
        cout << "It's a draw!" << endl;
    }
}


/*************************************************************************************************/


void playFourInRow(){
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
}


/*************************************************************************************************/


int playWordTicTacToe(){
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
}


/*************************************************************************************************/


void playNumericalTicTacToe(){
    srand(time(0));

    NumericalTicTacToe board;

    GamePlayers<int>* players[2];
    for (int i = 0; i < 2; ++i) {
        string type;
        cout << "Is Player " << i + 1 << " a human or computer? ";
        cin >> type;
        if (type == "human") {
            string name;
            cout << "Enter name for Player " << i + 1 << ": ";
            cin >> name;
            players[i] = new Humanplayer(name, i == 0 ? 1 : 2);
        } else {
            players[i] = new NumericalRandomPlayer(i == 0 ? 1 : 2);
        }
        players[i]->setBoard(&board);
    }

    GameMaster<int> gameManager(&board, players);
    gameManager.run();

    delete players[0];
    delete players[1];
}


/************************************************************************************************** */

int playUltimateTicTacToe(){
    UltimateTicTacToe<char> game;
    UltimateHumanPlayer<char> player1("Player 1", 'X');
    UltimateHumanPlayer<char> player2("Player 2", 'O');

    int x, y;

    while (!game.game_is_over()) {
        game.display_board();

        cout << player1.getname() << "'s turn:\n";
        player1.getmove(x, y);
        if (!game.update_board(x, y, player1.getsymbol())) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        if (game.game_is_over()) break;

        game.display_board();

        cout << player2.getname() << "'s turn:\n";
        player2.getmove(x, y);
        if (!game.update_board(x, y, player2.getsymbol())) {
            cout << "Invalid move. Try again.\n";
            continue;
        }
    }

    game.display_board();
    if (game.is_win()) {
        cout << "We have a winner!\n";
    } else {
        cout << "It's a draw!\n";
    }


}

void playSUS(){
    SUSBoard board;
    SUSPlayer player1("Player 1", 'S');
    Player<char>* player2;

    cout << "Choose your opponent:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        player2 = new SUSPlayer("Player 2", 'U');
    } else {
        player2 = new SUSRandomPlayer('U');
    }

    Player<char>* players[2] = { &player1, player2 };
    GameManager<char> gameManager(&board, players);

    player1.setBoard(&board);
    player2->setBoard(&board);

    while (!board.game_is_over()) {
        for (int i : {0, 1}) {
            int x, y;
            players[i]->getmove(x, y);
            while (!board.update_board(x, y, players[i]->getsymbol())) {
                cout << "Invalid move. Try again.\n";
                players[i]->getmove(x, y);
            }
            board.display_board();
            int sus_count = board.count_sus_sequences(players[i]->getsymbol());
            if (i == 0) {
                static_cast<SUSPlayer*>(players[i])->score = sus_count;
            } else {
                static_cast<SUSPlayer*>(players[i])->score = sus_count;
            }

            if (board.game_is_over()) break;
        }
    }

    cout << "Game over!\n";
    cout << player1.getname() << " score: " << player1.score << "\n";
    cout << static_cast<SUSPlayer*>(player2)->getname() << " score: " << static_cast<SUSPlayer*>(player2)->score << "\n";

    if (player1.score > static_cast<SUSPlayer*>(player2)->score) {
        cout << player1.getname() << " wins!\n";
    } else if (static_cast<SUSPlayer*>(player2)->score > player1.score) {
        cout << static_cast<SUSPlayer*>(player2)->getname() << " wins!\n";
    } else {
        cout << "It's a draw!\n";
    }

    delete player2;
}




#endif //_RUNGAMES_H
