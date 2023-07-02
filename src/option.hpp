//
//  option.hpp
//  str8ts
//

#ifndef option_hpp
#define option_hpp

#include <string_view>

namespace main_opt {

extern bool debug;
extern bool trace;
extern bool verbose;
extern bool all;

bool process_options(std::string_view arg);
}

#endif /* option_hpp */
