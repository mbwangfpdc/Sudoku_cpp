//
//  sudoku.cpp
//  Sudoku_cpp
//
//  Created by Morgan Borjigin-Wang on 1/2/18.
//  Copyright © 2018 Morgan Borjigin-Wang. All rights reserved.
//

#include "Board.hpp"
using namespace std;

ostream& operator<<(ostream& os, const Square& printed) {
    if (printed.value > -1) {
        os << printed.value + 1;
    } else {
        os << " ";
    }
    return os;
}

ostream& operator<<(ostream& os, const Board& printed) {
    cout << " --- --- ---" << endl;
    for (int row = 0; row < 9; ++row) {
        cout << "|";
        for (int col = 0; col < 9; ++col) {
            cout << printed.data[row * 9 + col];
            if (col % 3 == 2) {
                cout << "|";
            }
        }
        cout << endl;
        if (row % 3 == 2) {
            cout << " --- --- ---" << endl;
        }
    }
    return os;
}

int main() {
    cout << "Welcome to Sudoku!" << endl
         << "Please enter a valid sudoku starting board" << endl
         << "(One string, zeroes where empty squares are, spaces between lines of 9)" << endl;
    string input;
    getline(cin, input);
    cin.clear();
    Board board(input);
    cout << "Good luck!" << endl;
    cout << board;
    char cmd;
    cin >> cmd;
    bool auto_check = false;
    while (cmd != 'q' && !board.completed()) {
        switch (cmd) {
            case 'c':
                board.check_invariant();
                break;
                break;
            case '2':
                if (auto_check) {
                    auto_check = false;
                    cout << "Auto-check invariant turned off" << endl;
                } else {
                    auto_check = true;
                    cout << "Auto-check invariant turned on" << endl;
                }
                break;
            case 'e':
                if (board.solve_by_elim()) {
                    cout << "Something was solved by elimination!" << endl
                    << board;
                } else {
                    cout << "Nothing was solved by elimination" << endl;
                }
                break;
            case 'i':
                if (board.solve_by_isolation()) {
                    cout << "Something was solved by isolation!" << endl
                    << board;
                } else {
                    cout << "Nothing was solved by isolation" << endl;
                }
                break;
            case 'h':
                cout << "USAGE:\n u: update board\n c: check invariant\n 1: toggle automatic board update\n 2: toggle automatic invariant check\n e: solve part of the board through elimination\n i: solve part of the board through isolation\n q: quit" << endl;
            default:
                cout << "Invalid input" << endl << "Type 'h' for help, or 'q' to quit" << endl;
                break;
        }
        if (auto_check) {
            board.check_invariant();
            cout << "Automatically checked invariant" << endl;
        }
        cin >> cmd;
    }
    if (cmd == 'q') {
        cout << "Thanks for playing!" << endl;
    } else {
        cout << board;
        cout << "Congratulations!" << endl;
    }
    return 0;
}
