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
#include "Nine_set.hpp"
#include "Square.hpp"

struct Board {
    Board(std::string);
    
    // Board representation as an array and series of sets
    Square data[81];
    Nine_set row_solved[9];
    Nine_set col_solved[9];
    Nine_set box_solved[9];
    
    void update_whole();
    void update_cell(int);
    bool solve_by_elim();
    bool solve_by_isolation();
    bool isolate_helper_row(int, int*);
    bool isolate_helper_col(int, int*);
    bool isolate_helper_box(int, int*);
    
    bool check_invariant();
    bool completed();
};









#endif /* Board_hpp */
