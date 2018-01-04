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
#include "Nine_set.hpp"


    

struct Square {
    bool solved;
    int value;
    Nine_set remaining;
    Square() : solved(false), value(0) {}
};

class Board {
    // Board representation as an array and series of sets
    Square data[81];
    Nine_set row_solved[9];
    Nine_set col_solved[9];
    Nine_set box_solved[9];
public:
    Board(std::string);
private:
    void update_solved();
    void update_board_poss();
};









#endif /* Board_hpp */
