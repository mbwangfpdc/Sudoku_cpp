//
//  Nine_set.hpp
//  Sudoku_cpp
//
//  Created by Morgan Borjigin-Wang on 1/3/18.
//  Copyright © 2018 Morgan Borjigin-Wang. All rights reserved.
//

#ifndef Nine_set_hpp
#define Nine_set_hpp

#include <stdio.h>

struct Nine_set {
    bool nums[9];
    // Sets all numbers as false
    Nine_set();
    
    // Sets all numbers as true or false
    Nine_set(bool);
    
    // Takes out a number from the Nine_set
    void elim(int);
    
    // Takes out all numbers in another set from this
    void elim(const Nine_set&);
    
    // Returns number of true values left in this
    int num_left();
    
    // Returns true if inputted number is present in this Nine_set
    bool& operator[](int);
};


#endif /* Nine_set_hpp */
