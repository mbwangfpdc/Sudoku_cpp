//
//  Board.hpp
//  Sudoku_cpp
//
//  Created by Morgan Borjigin-Wang on 1/2/18.
//  Copyright © 2018 Morgan Borjigin-Wang. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include "Nine_set.hpp"
#include "Square.hpp"


struct Board {
    Board(std::string);
    
    // Board representation as an array and series of sets
    std::array<Square, 81> data;
    Nine_set row_solved[9];
    Nine_set col_solved[9];
    Nine_set box_solved[9];
    
    void solve_cell(int, int); // TODO: Turn update_cell into solve_cell
    void unsolve_cell(int);

    bool solve_by_elim();
    int solve_by_isolation();
    int isolate_helper_row(int, int[]);
    int isolate_helper_col(int, int[]);
    int isolate_helper_box(int, int[]);
    
    void solve_by_hypothesis(const std::array<Square, 81>&);
    
    bool check_invariant();
    bool completed();
    
    void print_board();
};









#endif /* Board_hpp */
