#include "utils.hpp"
#include <sstream>

std::string join_strings(const std::list<std::string> &list, const std::string &separator) {

    int size = list.size();

    if (list.size() == 0) { return ""; }

    std::ostringstream ostream;
    int i = 0;
    for (auto str: list) {
	ostream << str;
	if (i != size - 1)
	    ostream << separator;
	i++;
    }
    return ostream.str();
}
