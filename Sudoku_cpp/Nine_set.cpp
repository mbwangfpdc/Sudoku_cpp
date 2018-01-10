//
//  Nine_set.cpp
//  Sudoku_cpp
//
//  Created by Morgan Borjigin-Wang on 1/3/18.
//  Copyright © 2018 Morgan Borjigin-Wang. All rights reserved.
//

#include "Nine_set.hpp"
using namespace std;

Nine_set::Nine_set() {
    for (int i = 0; i < 9; ++i) {
        nums[i] = false;
    }
}

Nine_set::Nine_set(bool buul) {
    for (int i = 0; i < 9; ++i) {
        nums[i] = buul;
    }
}

void Nine_set::elim(int i) {
    nums[i] = false;
}

void Nine_set::elim(const Nine_set& other) {
    for (int i = 0; i < 9; ++i) {
        if (other.nums[i]) {
            nums[i] = false;
        }
    }
}

bool Nine_set::single_left() {
    int count = 0;
    for (bool buul : nums) {
        if (buul) {
            ++count;
            if (count == 2) {
                return false;
            }
        }
    }
    return true;
}

bool& Nine_set::operator[](int i) {
    return nums[i];
}
