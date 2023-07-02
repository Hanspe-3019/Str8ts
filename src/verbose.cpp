//
//  verbose.cpp
//
//

#include "verbose.hpp"


std::string Verbose::coordinates(const int i) {
    return { Verbose::ROWS[i/9], Verbose::COLS[i%9] };
}

char Verbose::row_as_char(const int i) {
    return Verbose::ROWS[i];
}
