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
#include "Nine_set.hpp"
#include "Square.hpp"


struct Board {
    Board(std::string);
    std::vector<std::pair<int, Nine_set>> hypothesis;
    
    // Board representation as an array and series of sets
    Square data[81];
    Nine_set row_solved[9];
    Nine_set col_solved[9];
    Nine_set box_solved[9];
    
    void update_whole(); // TODO: Ditch this and test, should be okay (use in ctor)
    void update_cell(int); // TODO: Turn update_cell into solve_cell
    // TODO: implement unsolve_cell (can be exact opposite of solve_cell
    bool solve_by_elim();
    bool solve_by_isolation();
    bool isolate_helper_row(int, int[]);
    bool isolate_helper_col(int, int[]);
    bool isolate_helper_box(int, int[]);
    
    bool check_invariant();
    bool completed();
    
    void hypothesize();
};









#endif /* Board_hpp */
