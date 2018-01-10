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
    bool solved;
    int value;
    Nine_set poss;
    Square() : solved(false), value(0), poss(true) {}
};

#endif /* Square_hpp */
