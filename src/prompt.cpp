//
//  prompt.cpp
//

#include "prompt.hpp"

#include "str8tscurses.hpp"


void prompt_puzzle(std::string & puzzle) {
    auto sc = Str8tscurses {"Press s to solve, q to quit!"};
        
    auto selected_row = 0, selected_col = 0;
    
    int key;
    while( (key = getch()) != 's' ) {
        
        if (key == 'q') {
            throw std::string("quit");
        }
        
        auto selected_row_old = selected_row;
        auto selected_col_old = selected_col;
        switch(key)
        {    case KEY_UP:
                selected_row = (selected_row + 9 - 1 ) % 9;
                break;
            case KEY_DOWN:
                selected_row = (selected_row + 9 + 1 ) % 9;
                break;
            case KEY_LEFT:
                selected_col = (selected_col + 9 - 1 ) % 9;
                break;
            case KEY_RIGHT:
                selected_col = (selected_col + 9 + 1 ) % 9;
                break;
        }
        auto current_cell = & sc.cell[selected_row][selected_col];
        const auto current_win = current_cell->win;
        
        if (selected_col == selected_col_old and selected_row == selected_row_old) {
            // keine Bewegung:
            if ( '1' <= key and key <= '9' and current_cell->content != key) {
                current_cell->content = key;
                mvwaddch(current_win, 1, 2, key);
            } else if (key == '#') {
                current_cell->blocked = !current_cell->blocked;
                const auto color = current_cell->blocked ? Str8tscurses::color_block : Str8tscurses::color_normal;
                wbkgd(current_win, color);
                mvwaddch(current_win, 1, 2, current_cell->content); // ???
            } else if (key <= '0') {
                current_cell->content = ' ';
                mvwaddch(current_win, 1, 2, ' ');
            }
        } else {
            // Bewegung
            auto previous_cell = & sc.cell[selected_row_old][selected_col_old];
            const auto previous_win = previous_cell->win;
            
            Str8tscurses::mark_cell(previous_win, false);
            Str8tscurses::mark_cell(current_win, true);
            
            if (current_cell->blocked) {
                wbkgd(current_win, Str8tscurses::color_block);
            } else {
                wbkgd(current_win, Str8tscurses::color_normal);
            }
            if (previous_cell->blocked) {
                
                wbkgd(previous_win, Str8tscurses::color_block);
            } else {
                wbkgd(previous_win, Str8tscurses::color_normal);
            }
            wrefresh(previous_win);
        }
        mvprintw(2, 14,
                 "Selected %c%c %s < %c >",
                 "ABCDEFGHI"[selected_row],
                 "123456789"[selected_col],
                 current_cell->blocked ? "block":
                 current_cell->content > '0' ? "!set!" :
                 "empty",
                 current_cell->content
                 );
        wrefresh(current_win);
            
    }
        
    
    for (auto row = 0; row != 9; ++row) {
        for (auto col = 0; col !=9; ++col) {
            auto c = & sc.cell[row][col];
            puzzle += Str8tscurses::output_cell(*c);
        }
    }
}
