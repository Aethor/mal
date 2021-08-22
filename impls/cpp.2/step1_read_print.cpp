#include "readline.hpp"
#include "reader.hpp"
#include "types.hpp"
#include "printer.hpp"
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>


std::shared_ptr<MalObject> read() {
    std::string input = string_readline("user> ");
    return read_str(input);
}

std::shared_ptr<MalObject> eval(std::shared_ptr<MalObject> const& input) {
    return input;
}

void print(std::shared_ptr<MalObject> const& input) {
    std::cout << pr_str(input) << "\n";
}

int main() {

    while (true) {

	std::shared_ptr<MalObject> input;
	try {
	     input = read();
	} catch(std::runtime_error& err) {
	    std::cerr << err.what() << "\n";
	    continue;
	}

	print(eval(input));
    }

    return 0;
}
