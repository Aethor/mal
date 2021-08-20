#include "printer.hpp"
#include "utils.hpp"
#include "types.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>


std::string pr_str(std::shared_ptr<MalObject> const& object) {

    // huh....
    if (dynamic_cast<MalScalar const*>(object.get())) {
	return std::to_string(dynamic_cast<MalScalar const*>(object.get())->value);
    }
    if (dynamic_cast<MalSymbol const*>(object.get())) {
	return dynamic_cast<MalSymbol const*>(object.get())->value;
    }
    if (dynamic_cast<MalString const*>(object.get())) {
	return dynamic_cast<MalString const*>(object.get())->value;
    }
    if (dynamic_cast<MalBool const*>(object.get())) {
	return std::to_string(dynamic_cast<MalBool const*>(object.get())->value);
    }
    if (dynamic_cast<MalList const*>(object.get())) {
	std::list<std::string> tokens = {};
	for (std::shared_ptr<MalObject> element: dynamic_cast<MalList const*>(object.get())->elements) {
	    tokens.push_back(pr_str(element));
	}
	return "(" + join_strings(tokens, " ") + ")";
    }

    throw std::invalid_argument("tried to print unprintable MAL type");
}
