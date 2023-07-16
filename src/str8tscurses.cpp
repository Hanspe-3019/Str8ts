//
//  str8tscurses.cpp
//  str8ts
//
#include <iostream>

#include "str8tscurses.hpp"
#include "option.hpp"

Color Str8tscurses::color_block, Str8tscurses::color_outer, Str8tscurses::color_normal;

Str8tscurses::Str8tscurses(const char * title) {

    if (main_opt::debug) {
        std::cerr << "CTOR Str8tscurses at " << this << '\n';
    }
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0); // do not display cursour
    noecho();
    
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    color_normal = COLOR_PAIR(1);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    color_block = COLOR_PAIR(3);
    init_pair(4, COLOR_WHITE, COLOR_YELLOW);
    color_outer = COLOR_PAIR(4);
    
    mvprintw(0, 12, title);
    refresh();
    {
        auto outer_top = newwin(1, 1 + 9 * Cell::w, 4, 4);
        wbkgd(outer_top, color_outer);
        for (auto i = 0; i!= 9 ; ++i) {
            mvwaddch(outer_top, 0, 3 + i * Cell::w, '1' + i);
        }
        wrefresh(outer_top);
        auto outer_left = newwin(9 * Cell::h, 3, 5, 2);
        wbkgd(outer_left, color_outer);
        for ( auto i = 0; i != 9; ++i ) {
            mvwaddch(outer_left, 1 + i * Cell::h, 1, 'A' + i);
        }
        wrefresh(outer_left);
        auto outer_right = newwin(9 * Cell::h, 3, 5, 5 + 9 * Cell::w);
        wbkgd(outer_right, color_outer);
        wrefresh(outer_right);
        auto outer_bottom = newwin(1,1 + 9 * Cell::w + 1, 5 + 9 * Cell::h, 4);
        wbkgd(outer_bottom, color_outer);
        wrefresh(outer_bottom);
    }
    for ( auto row = 0; row != 9; ++row ) {
        for ( auto col = 0; col != 9; ++col ) {
            const auto startx = 5 + Cell::w * col;
            const auto starty = 5 + Cell::h * row;
            const auto win = newwin(Cell::h, Cell::w, starty, startx);
            fill_cell(win);
            
            cell[row] [col].win = win;
            if (row == 0 and col == 0) {
                mark_cell(win, true);
            }
            wbkgd(win, color_normal);
            wrefresh(win);
        }
    }
    
}
Str8tscurses::~Str8tscurses() {
    endwin();            /* End curses mode          */
    if (main_opt::debug) {
        std::cerr << "DTOR Str8tscurses at " << this << '\n';
    }
}
void Str8tscurses::fill_cell(WINDOW * win) {
    mvwaddch(win, 0, 0, ACS_ULCORNER);
    for (auto col = 1; col < (Cell::w - 1); ++col) {
        mvwaddch(win, 0, col, ACS_HLINE);
        mvwaddch(win, Cell::h - 1, col, ACS_HLINE);
    }
    mvwaddch(win, 0, Cell::w - 1, ACS_URCORNER);
    
    for (auto row = 1; row < (Cell::h - 1); ++row) {
        mvwaddch(win, row, 0, ACS_VLINE);
        mvwaddch(win, row, Cell::w - 1, ACS_VLINE);
    }
    mvwaddch(win, Cell::h - 1, 0, ACS_LLCORNER);
    mvwaddch(win, Cell::h - 1, Cell::w - 1, ACS_LRCORNER);
}
void Str8tscurses::mark_cell(WINDOW * win, const bool selected) {
    if (selected) {
        mvwaddch(win, Cell::h / 2, 0, '>');
        mvwaddch(win, Cell::h / 2, Cell::w - 1, '<');
    } else {
        mvwaddch(win, Cell::h / 2, 0, ACS_VLINE);
        mvwaddch(win, Cell::h / 2, Cell::w - 1, ACS_VLINE);
    }
}

char Str8tscurses::output_cell(const Cell & cell) {
    if (cell.blocked) {
        return cell.content > '0' ? cell.content + 'a' - '1': '#';
    }
    return cell.content > '0' ? cell.content : '.';
}
