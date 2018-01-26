//
//  Square.hpp
//  Sudoku_cpp
//
//  Created by Morgan Borjigin-Wang on 1/5/18.
//  Copyright © 2018 Morgan Borjigin-Wang. All rights reserved.
//

#ifndef Square_hpp
#define Square_hpp
#include <cassert>
#include <stdio.h>

struct Square {
    int value;
    Nine_set poss;
    Square() : value(-1), poss(true) {}
};

#endif /* Square_hpp */
