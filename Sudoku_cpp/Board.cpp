//
//  Board.cpp
//  Sudoku_cpp
//
//  Created by Morgan Borjigin-Wang on 1/2/18.
//  Copyright © 2018 Morgan Borjigin-Wang. All rights reserved.
//

#include "Board.hpp"
using namespace std;

bool operator==(const Square& lhs, const Square& rhs) {
    for (int i = 0; i < 9; ++i) {
        if (lhs.poss[i] != rhs.poss[i]) {
            return false;
        }
    }
    return lhs.value == rhs.value;
}

Board::Board(std::string str_in) {
    for (int i = 0; i < 81; ++i) {
        data[i].value = int(str_in[i + i / 9] - '0' - 1);
    }
    for (int i = 0; i < 81; ++i) {
        // For every Square on the board, if you've solved that square
        // update the solved data associated with that Square
        Square& sqr = data[i];
        if (sqr.value >= 0) {
            row_solved[i / 9][sqr.value] = true;
            col_solved[i % 9][sqr.value] = true;
            box_solved[i / 27 * 3 + i % 9 / 3][sqr.value] = true;
        }
    }
    // After restrictions updated use them to update possible vals for each tile
    for (int i = 0; i < 81; ++i) {
        Square& sqr = data[i];
        if (sqr.value < 0) {
            sqr.poss.elim(row_solved[i / 9]);
            sqr.poss.elim(col_solved[i % 9]);
            sqr.poss.elim(box_solved[i / 27 * 3 + i % 9 / 3]);
        }
    }
}

bool Board::check_invariant() {
    vector<Nine_set> row_checks(9, Nine_set(false));
    vector<Nine_set> col_checks(9, Nine_set(false));
    vector<Nine_set> box_checks(9, Nine_set(false));
    for (int i = 0; i < 81; ++i) {
        const Square& sqr = data[i];
        if (sqr.value >= 0) {
            bool& seen_on_row = row_checks[i / 9][sqr.value];
            bool& seen_on_col = col_checks[i % 9][sqr.value];
            bool& seen_on_box = box_checks[i / 27 * 3 + i % 9 / 3][sqr.value];
            seen_on_row = !seen_on_row;
            seen_on_col = !seen_on_col;
            seen_on_box = !seen_on_box;
            if (!(seen_on_row && seen_on_col && seen_on_box)) {
                cout << "INVARIANT VIOLATED: CELL " << i << endl;
                return false;
            }
        } else if (sqr.poss.num_left() == 0) {
            cout << "Mistake made: Cell " << i << " cannot be completed" << endl;
            return false;
        }
    }
    cout << "Invariant holds" << endl;
    return true;
}

bool Board::completed() {
    for (int i = 0; i < 81; ++i) {
        if (data[i].value < 0) {
            return false;
        }
    }
    return true;
}

void Board::solve_cell(int i, int solution) {
    data[i].value = solution;
    int row = i / 9;
    int col = i % 9;
    int box = row / 3 * 3 + col / 3;
    row_solved[row][solution] = true;
    col_solved[col][solution] = true;
    box_solved[box][solution] = true;
    for (int sqr = 0; sqr < 9; ++sqr) {
        data[row * 9 + sqr].poss[solution] = false;
        data[sqr * 9 + col].poss[solution] = false;
        data[box / 3 * 27 + box % 3 * 3 + sqr / 3 * 9 + sqr % 3].poss[solution] = false;
    }
    print_board();
}

void Board::unsolve_cell(int i) {
    Square& cell = data[i];
    int row = i / 9;
    int col = i % 9;
    int box = row / 3 * 3 + col / 3;
    row_solved[row][cell.value] = false;
    col_solved[col][cell.value] = false;
    box_solved[box][cell.value] = false;
    for (int sqr = 0; sqr < 9; ++sqr) {
        data[row * 9 + sqr].poss[cell.value] = true;
        data[sqr * 9 + col].poss[cell.value] = true;
        data[box / 3 * 27 + box % 3 * 3 + sqr / 3 * 9 + sqr % 3].poss[cell.value] = true;
    }
    cell.value = -1;
}


bool Board::solve_by_elim() {
    bool e = false;
    for (int i = 0; i < 81; ++i) {
        Square& sqr = data[i];
        if (sqr.value < 0) {
            if (sqr.poss.num_left() == 1) {
                for (int val = 0; val < 9; ++val) {
                    if (sqr.poss[val]) {
                        solve_cell(i, val);
                        break;
                    }
                }
                e = true;
            }
        }
    }
    return e;
}

int Board::solve_by_isolation() {
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
                if (row_s.value < 0 && row_s.poss[num]) {
                    ++row_seen[num];
                }
                if (col_s.value < 0 && col_s.poss[num]) {
                    ++col_seen[num];
                }
                if (box_s.value < 0 && box_s.poss[num]) {
                    ++box_seen[num];
                }
            }
        }
        // Track position of first isolated cell, and return.
        int solved_cell = isolate_helper_row(region, row_seen);
        if (solved_cell < 0) {
            solved_cell = isolate_helper_col(region, col_seen);
        }
        if (solved_cell < 0) {
            solved_cell = isolate_helper_box(region, box_seen);
        }
        if (solved_cell >= 0) {
            return solved_cell;
        }
    }
    return -1;
}

int Board::isolate_helper_row(int row, int seen[]) {
    // Go through seen[] and check if any numbers are localized to a square
    for (int num = 0; num < 9; ++num) {
        // If so, go through squares to find where that number is
        if (seen[num] == 1) {
            for (int sqr = 0; sqr < 9; ++sqr) {
                int index = row * 9 + sqr;
                Square& s = data[index];
                // Find localized place and fill it.
                if (s.value < 0 && s.poss[num]) {
                    solve_cell(index, num);
                    return index;
                }
            }
        }
    }
    return -1;
}

int Board::isolate_helper_col(int col, int seen[]) {
    // Go through seen[] and check if any numbers are localized to a square
    for (int num = 0; num < 9; ++num) {
        // If so, go through squares to find where that number is
        if (seen[num] == 1) {
            for (int sqr = 0; sqr < 9; ++sqr) {
                int index = sqr * 9 + col;
                Square& s = data[index];
                // Find localized place and fill it.
                if (s.value < 0 && s.poss[num]) {
                    solve_cell(index, num);
                    return index;
                }
            }
        }
    }
    return -1;
}

int Board::isolate_helper_box(int box, int seen[]) {
    // Go through seen[] and check if any numbers are localized to a square
    for (int num = 0; num < 9; ++num) {
        // If so, go through squares to find where that number is
        if (seen[num] == 1) {
            for (int sqr = 0; sqr < 9; ++sqr) {
                int index = box / 3 * 27 + box % 3 * 3 + sqr / 3 * 9 + sqr % 3;
                Square& s = data[index];
                // Find localized place and fill it.
                if (s.value < 0 && s.poss[num]) {
                    solve_cell(index, num);
                    return index;
                }
            }
        }
    }
    return -1;
}

void Board::solve_by_hypothesis(const std::array<Square, 81>& last) {
    int min_options = 10;
    int pos = -1;
    // Find the cell with the fewest "possible" answers.  Also checks if completed
    for (int i = 0; i < 81; ++i) {
        if (data[i].value < 0) {
            int options = data[i].poss.num_left();
            if (options < min_options) {
                min_options = options;
                pos = i;
            }
        }
    }
    if (pos == -1 && check_invariant()) {
        return;
    }
    
    // From that cell, guess each poss value and add it to the trace, checking
    // validity using rules and recursive hypotheses
    std::array<Square, 81> trace = data;
    for (int guess = 0; guess < 9; ++guess) {
        if (data[pos].poss[guess]) {
            solve_cell(pos, guess);
            while (solve_by_isolation() >= 0) {}
            if (!check_invariant()) {
                data = trace;
                data[pos].poss[guess] = false;
            } else if (!completed()) {
                solve_by_hypothesis(trace);
            } else {
                return;
            }
        }
    }
    if (trace == data) {
        data = last;
    }
}

void Board::print_board() {
    cout << " --- --- ---" << endl;
    for (int row = 0; row < 9; ++row) {
        cout << "|";
        for (int col = 0; col < 9; ++col) {
            if (data[row * 9 + col].value > -1) {
                cout << data[row * 9 + col].value + 1;
            } else {
                cout << " ";
            }
            if (col % 3 == 2) {
                cout << "|";
            }
        }
        cout << endl;
        if (row % 3 == 2) {
            cout << " --- --- ---" << endl;
        }
    }
}
