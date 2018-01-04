//
//  Board.cpp
//  Sudoku_cpp
//
//  Created by Morgan Borjigin-Wang on 1/2/18.
//  Copyright © 2018 Morgan Borjigin-Wang. All rights reserved.
//

#include "Board.hpp"
using namespace std;

Board::Board(std::string str_in) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            data[i * 9 + j].value = int(str_in[i * 9 + j] - '0' - 1);
            if (data[i * 9 + j].value != -1) {
                data[i * 9 + j].solved = true;
            }
        }
    }
}

void Board::update_solved() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // For every Square on the board, if you've solved that square
            // update the solved data associated with that Square
            const Square& sqr = data[row * 9 + col];
            if (sqr.solved) {
                row_solved[row].elim(sqr.value);
                col_solved[col].elim(sqr.value);
                box_solved[row / 3 * 3 + col / 3].elim(sqr.value);
            }
        }
    }
}

void Board::update_board_poss() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // For every Square on the board, if that square is unsolved then
            // narrow its possibilities using Nine_set::elim.
            Square& sqr = data[row * 9 + col];
            if (!sqr.solved) {
                sqr.remaining.elim(row_solved[row]);
                sqr.remaining.elim(col_solved[col]);
                sqr.remaining.elim(box_solved[row / 3 * 3 + col / 3]);
                if (sqr.remaining.single_left()) {
                    sqr.solved = true;
                    for (int i = 0; i < 9; ++i) {
                        if (sqr.remaining[i]) {
                            sqr.value = i;
                            break;
                        }
                    }
                }
            }
        }
    }
}
