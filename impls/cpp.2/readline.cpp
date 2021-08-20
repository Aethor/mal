#include "readline.hpp"
#include <cstdlib>
#include <readline/history.h>
#include <readline/readline.h>

std::string string_readline(std::string const& prompt) {
    char *line = readline(prompt.c_str());
    add_history(line);
    std::string out = line;
    free(line);
    return out;
}
