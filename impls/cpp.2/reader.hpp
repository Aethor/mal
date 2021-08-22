#ifndef READER
#define READER

#include "types.hpp"
#include <memory>
#include <string>
#include <vector>


std::vector<std::string> tokenize(std::string const& str);

std::shared_ptr<MalObject> read_str(std::string const& str);

class Reader {

private:

    std::vector<std::string> tokens;
    long unsigned int cur_pos;

    std::string next(void);

    std::string peek(void);

public:

    Reader(std::vector<std::string> const& tokens) : tokens(tokens), cur_pos(0) { }

    std::shared_ptr<MalList> read_list();

    std::shared_ptr<MalAtom> read_atom();

    std::shared_ptr<MalObject> read_form();
    
};

#endif
