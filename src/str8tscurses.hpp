//
//  str8tscurses.hpp
//  str8ts
//

#ifndef str8tscurses_hpp
#define str8tscurses_hpp

#include <ncurses.h>

using Color = decltype(COLOR_PAIR(0));

struct Cell {
    WINDOW * win = nullptr;
    char content = ' ';
    bool blocked = false;
    static const auto h = 3;
    static const auto w = 5;
};
struct Str8tscurses {
    
    Cell cell[9][9];
    static Color color_outer, color_normal, color_block;
    
    Str8tscurses(const char *);
    ~Str8tscurses();
    
    static void curses_init(void);
    static void mark_cell(WINDOW * win, const bool selected);
    static char output_cell(const Cell &);
    static void fill_cell(WINDOW * win);

};





#endif /* str8tscurses_hpp */
