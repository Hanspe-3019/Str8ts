//
//  runstats.hpp
//  Str8tsSolver
//

#ifndef runstats_hpp
#define runstats_hpp

#include <string>
#include <memory>
#include "option.hpp"

struct Node {
    friend class Runstats;
    Node(std::string name, Node * parent);
    ~Node();
private:
    std::string name;
    std::unique_ptr<Node> first;
    std::unique_ptr<Node> next;
    Node * parent;
    int count;
    
};

class Runstats {
private:
    Node  root = Node("**main**", nullptr);
    Node * current = & root;
public:
    static void start(const std::string &);
    static void stop(void);
    static void print_stats();
};

struct StartStop {
    StartStop(const std::string name) {
        if (main_opt::trace) Runstats::start(name);
    }
    ~StartStop() {
        // This code will run when object goes out of scope
        if (main_opt::trace) Runstats::stop();
    }
};

#endif /* runstats_hpp */
