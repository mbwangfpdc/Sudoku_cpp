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

Nine_set::Nine_set(const Nine_set& other) {
    copy(other);
}

void Nine_set::copy(const Nine_set& other) {
    for (int i = 0; i < 9; ++i) {
        nums[i] = other.nums[i];
    }
}

void Nine_set::elim(const Nine_set& other) {
    for (int i = 0; i < 9; ++i) {
        if (other.nums[i]) {
            nums[i] = false;
        }
    }
}

int Nine_set::num_left() const {
    int count = 0;
    for (bool buul : nums) {
        if (buul) {
            ++count;
        }
    }
    return count;
}

bool& Nine_set::operator[](int i) {
    return nums[i];
}

bool Nine_set::operator[](int i) const {
    return nums[i];
}
