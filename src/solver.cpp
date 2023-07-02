//
//  solver.cpp
//  Str8tsSolver
//

#include <iostream>
#include <chrono>
#include <ctime>

#include "Str8ts.hpp"
#include "runstats.hpp"
#include "option.hpp"

using namespace std;

void solve_it(Str8ts & puzzle);

int main(int argc, char * argv[])
{
    
    // loop over all input problems
    auto problems_given = 0;
    for (int j = 1; j < argc; j++) {

        const string file = argv[j];
        
        if ( main_opt::process_options(file) ) continue;
        
        cout << "Loading " << file << endl;
        problems_given += 1;

        Str8ts puzzle(file);

        if (puzzle.loaded()) {
            
            solve_it(puzzle);
        }
        else {
            cout << "Couldn't load problem.\n";
        }
    }
    if ( not problems_given) {
        Str8ts puzzle {"-i"}; // interactive mode ncurses
        solve_it(puzzle);
    }
    if ( main_opt::trace ) {
        Runstats::print_stats();
    }

    return 0;
}
void solve_it(Str8ts & puzzle) {
    puzzle.print_problem();
    
    cout << "Solving the puzzle..." << endl;
    
    auto start = chrono::system_clock::now();
    
    puzzle.solve();
    
    puzzle.print_solutions();
    
    auto end = chrono::system_clock::now();
    
    const string endmsg =
    puzzle.get_num_solutions() ?
    "Solved in " :
    "No solution found in "
    ;
    chrono::duration<double> elapsed_seconds = end - start;
    cout << endmsg << elapsed_seconds.count() << " sec.\n";
}

