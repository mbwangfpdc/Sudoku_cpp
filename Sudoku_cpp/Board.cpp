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
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            data[row * 9 + col].value = int(str_in[row * 9 + col + row] - '0' - 1);
            if (data[row * 9 + col].value != -1) {
                data[row * 9 + col].solved = true;
            }
        }
    }
}

bool Board::check_invariant() {
    for (int region = 0; region < 9; ++region) {
        Nine_set row_checker(false);
        Nine_set col_checker(false);
        Nine_set box_checker(false);
        for (int sqr = 0; sqr < 9; ++sqr) {
            int val = data[region * 9 + sqr].value;
            if (val >= 0) {
                if (!row_checker[val]) {
                    row_checker[val] = true;
                } else {
                    cout << "Invariant violated: duplicates in row " << region + 1 << endl;
                    return false;
                }
            }
            
            val = data[sqr * 9 + region].value;
            if (val >= 0) {
                if (!col_checker[val]) {
                    col_checker[val] = true;
                } else {
                    cout << "Invariant violated: duplicates in column " << region + 1 << endl;
                    return false;
                }
            }
            
            val = data[region / 3 * 27 + region % 3 * 3 + sqr / 3 * 9 + sqr % 3].value;
            if (val >= 0) {
                if (!box_checker[val]) {
                    box_checker[val] = true;
                } else {
                    cout << "Invariant violated: duplicates in box " << region + 1 << endl;
                    return false;
                }
            }
            
            
            if (!data[region * 9 + sqr].solved) {
                bool checker = false;
                for (int i = 0; i < 9; ++i) {
                    if (data[region * 9 + sqr].poss[i]) {
                        checker = true;
                        break;
                    }
                }
                if (!checker) {
                    cout << "Mistake made: cell " << region << ", " << sqr << " cannot be completed" << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::completed() {
    for (int i = 0; i < 81; ++i) {
        if (!data[i].solved) {
            return false;
        }
    }
    return check_invariant();
}

void Board::update_whole() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // For every Square on the board, if you've solved that square
            // update the solved data associated with that Square
            Square& sqr = data[row * 9 + col];
            if (sqr.solved) {
                row_solved[row][sqr.value] = true;
                col_solved[col][sqr.value] = true;
                box_solved[row / 3 * 3 + col / 3][sqr.value] = true;
            }
        }
    }
    // After restrictions updated use them to update possible vals for each tile
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // For every Square on the board, if you've solved that square
            // update the solved data associated with that Square
            Square& sqr = data[row * 9 + col];
            if (!sqr.solved) {
                sqr.poss.elim(row_solved[row]);
                sqr.poss.elim(col_solved[col]);
                sqr.poss.elim(box_solved[row / 3 * 3 + col / 3]);
            }
        }
    }
}

void Board::update_cell(int i) {
    assert(data[i].solved && data[i].value >= 0);
    Square& sqr = data[i];
    int row = i / 9;
    int col = i % 9;
    int box = row / 3 * 3 + col / 3;
    row_solved[row][sqr.value] = true;
    col_solved[col][sqr.value] = true;
    box_solved[box][sqr.value] = true;
    for (int sqr = 0; sqr < 9; ++sqr) {
        data[row * 9 + sqr].poss.elim(data[i].value);
        data[sqr * 9 + col].poss.elim(data[i].value);
        data[box / 3 * 27 + box % 3 * 3 + sqr / 3 * 9 + sqr % 3].poss.elim(data[i].value);
    }
}

bool Board::solve_by_elim() {
    bool e = false;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // For every square, check if solved by process elimination
            Square& sqr = data[row * 9 + col];
            if (!sqr.solved) {
                if (sqr.poss.single_left()) {
                    sqr.solved = true;
                    for (int i = 0; i < 9; ++i) {
                        if (sqr.poss[i]) {
                            sqr.value = i;
                            update_cell(row * 9 + col);
                            break;
                        }
                    }
                    e = true;
                }
            }
        }
    }
    return e;
}

bool Board::solve_by_isolation() {
    bool i = false;
    for (int region = 0; region < 9; ++region) {
        // Make an array to track number of sightings
        int row_seen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int col_seen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int box_seen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        // For every square in this region
        for (int sqr = 0; sqr < 9; ++sqr) {
            Square& row_s = data[region * 9 + sqr];
            Square& col_s = data[sqr * 9 + region];
            Square& box_s = data[region / 3 * 27 + region % 3 * 3 + sqr / 3 * 9 + sqr % 3];
            // Tally #poss of each number
            for (int num = 0; num < 9; ++num) {
                if (!row_s.solved && row_s.poss[num]) {
                    ++row_seen[num];
                }
                if (!col_s.solved && col_s.poss[num]) {
                    ++col_seen[num];
                }
                if (!box_s.solved && box_s.poss[num]) {
                    ++box_seen[num];
                }
            }
        }
        //isolate_helper_row(region, row_seen) ? i = true:i = i;
        //isolate_helper_col(region, col_seen) ? i = true:i = i;
        isolate_helper_box(region, box_seen) ? i = true:i = i;
    }
    return i;
}

bool Board::isolate_helper_row(int row, int* seen) {
    bool h = false;
    // Go through seen[] and check if any numbers are localized to a square
    for (int num = 0; num < 9; ++num) {
        // If so, go through squares to find where that number is
        if (seen[num] == 1) {
            h = true;
            for (int sqr = 0; sqr < 9; ++sqr) {
                int index = row * 9 + sqr;
                Square& s = data[index];
                // Find localized place and fill it.
                if (!s.solved && s.poss[num]) {
                    s.solved = true;
                    s.value = num;
                    update_cell(index);
                    break;
                }
            }
            break;
        }
    }
    return h;
}

bool Board::isolate_helper_col(int col, int* seen) {
    bool h = false;
    // Go through seen[] and check if any numbers are localized to a square
    for (int num = 0; num < 9; ++num) {
        // If so, go through squares to find where that number is
        if (seen[num] == 1) {
            h = true;
            for (int sqr = 0; sqr < 9; ++sqr) {
                int index = sqr * 9 + col;
                Square& s = data[index];
                // Find localized place and fill it.
                if (!s.solved && s.poss[num]) {
                    s.solved = true;
                    s.value = num;
                    update_cell(index);
                    break;
                }
            }
            break;
        }
    }
    return h;
}

bool Board::isolate_helper_box(int box, int* seen) {
    bool h = false;
    // Go through seen[] and check if any numbers are localized to a square
    for (int num = 0; num < 9; ++num) {
        // If so, go through squares to find where that number is
        if (*seen == 1) {
            h = true;
            for (int sqr = 0; sqr < 9; ++sqr) {
                int index = box / 3 * 27 + box % 3 * 3 + sqr / 3 * 9 + sqr % 3;
                Square& s = data[index];
                // Find localized place and fill it.
                if (!s.solved && s.poss[num]) {
                    s.solved = true;
                    s.value = num;
                    update_cell(index);
                    break;
                }
            }
            break;
        }
        ++seen;
    }
    return h;
}
