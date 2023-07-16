//
//  verbose.hpp
//
// Some helper declarations for verbose messages.

#ifndef verbose_h
#define verbose_h
#include <string>

namespace verbose {
    
    constexpr static char ROWS[] = "ABCDEFGHJ";
    constexpr static char COLS[] = "123456789";
    char row_as_char(const int row_num);
    char col_as_char(const int col_num);
    std::string coordinates(const int i);
};

#endif /* verbose_h */
