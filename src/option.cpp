//
//  option.cpp
//  str8ts
//

#include "option.hpp"
#include "helpme.hpp"
#include <iostream>

namespace main_opt {

bool debug;
bool trace;
bool verbose;
bool all;

bool process_options(std::string_view arg) {
    if ( arg[0] != '-') return false;   // all options start with '-'
    
    if (arg == "-") return false;      // Read puzzle from stdin
    
    if (arg == "-v" or arg == "--verbose") {
        verbose = true;
    } else if (arg == "-h" or arg == "-?" or arg == "--help") {
        givehelp();
    } else if (arg == "-a" or arg == "--all") {
        all = true;
    } else if (arg == "-d" or arg == "--debug") {
        debug = true;
    } else if (arg == "-t" or arg == "--trace") {
        trace = true;
    } else {
        std::cerr << "option not recognized: " << arg << '\n';
        givehelp();
    }
    return true;
}
}

