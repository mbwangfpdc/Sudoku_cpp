//
//  sudoku.cpp
//  Sudoku_cpp
//
//  Created by Morgan Borjigin-Wang on 1/2/18.
//  Copyright © 2018 Morgan Borjigin-Wang. All rights reserved.
//

#include "Board.hpp"
using namespace std;

void run_debug(Board& board) {
    cout << "Good luck!" << endl;
    board.print_board();
    char cmd;
    cin >> cmd;
    while (cmd != 'q' && !board.completed() && board.check_invariant()) {
        switch (cmd) {
            case 'e':
                if (board.solve_by_elim()) {
                    cout << "Something was solved by elimination!" << endl;
                    board.print_board();
                } else {
                    cout << "Nothing was solved by elimination" << endl;
                }
                break;
            case 'i':
                if (board.solve_by_isolation() >= 0) {
                    cout << "Something was solved by isolation!" << endl;
                    board.print_board();
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
        cin >> cmd;
    }
    if (cmd == 'q') {
        cout << "Thanks for playing!" << endl;
    } else if (board.completed()){
        board.print_board();
        cout << "Congratulations!" << endl;
    }
}

void run_solver(Board& board) {
    while (board.solve_by_isolation() >= 0) {}
    board.solve_by_hypothesis(board.data);
    cout << "Great job you did nothing" << endl;
}

int main() {
    cout << "Welcome to Sudoku!" << endl
         << "Please enter a valid sudoku starting board" << endl
         << "(One string, zeroes where empty squares are, spaces between lines of 9)" << endl;
    string input;
    getline(cin, input);
    cin.clear();
    Board board(input);
    
    //run_debug(board);
    run_solver(board);
    return 0;
}


