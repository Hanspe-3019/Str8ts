//
//  verbose.cpp
//
//

#include "verbose.hpp"


std::string verbose::coordinates(const int i) {
    return { verbose::ROWS[i/9], verbose::COLS[i%9] };
}

char verbose::row_as_char(const int i) {
    return verbose::ROWS[i];
}
