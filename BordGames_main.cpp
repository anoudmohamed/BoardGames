#include<iostream>
#include "RunGames.h"

using namespace std;

void showMenu() {
    cout << "Welcome to the Board Game Collection!\n";
    cout << "1. Play Pyramic Tic-Tac-Toe\n";
    cout << "2. Play Four-in-a-row Tic-Tac-Toe\n";
    cout << "3. Play 5x5 Tic-Tac-Toe\n";
    cout << "4. Play Word Tic-Tac-Toe\n";
    cout << "5. Play Numerical Tic-Tac-Toe\n";
    cout << "6. Play Misere Tic-Tac-Toe\n";
    cout << "7. Play 4x4 Tic-Tac-Toe\n";
    cout << "8. Play Ultimate Tic-Tac-Toe\n";
    cout << "9. Play SUS\n";
    cout << "10. Exit\n";
    cout << "Please enter your choice: ";
}



int main(){
    int menu_choice;
    bool running = true;
    while (running){
        showMenu();
        cin >> menu_choice;
        switch (menu_choice){
            case 1: // Call function to initialize and run pyramic Tic-Tac-Toe
                playPyramicTicTacToe();
                break;
            case 2:  // Call function to initialize and run four in a row Tic-Tac-Toe
                playFourInRow();
                break;
            case 3: // Call function to initialize and run 5x5 Tic-Tac-Toe
                play5x5TicTacToe();
                break;
            case 4:  // Call function to initialize and run word Tic-Tac-Toe
                playWordTicTacToe();
                break;
            case 5: // Call function to initialize and run numerical Tic-Tac-Toe
                playNumericalTicTacToe();
                break;
            case 6: // Call function to initialize and run Inverse Tic-Tac-Toe
                playMisereTicTacToe();
                break;
            case 7: // Call function to initialize and run 4x4 Tic-Tac-Toe
                play4x4TicTacToe();
                break;
            case 8:
                playUltimateTicTacToe();
                break;
            case 9:
                playSUS();
                break;
            case 10:
                running = false;
                cout << "Thank you for playing!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n"; }
    }

    return 0;
}

