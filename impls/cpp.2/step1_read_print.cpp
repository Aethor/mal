#include "readline.hpp"
#include "reader.hpp"
#include "types.hpp"
#include "printer.hpp"
#include <memory>
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

int main(int argc,char* argv[]) {
    while (true) {
	print(eval(read()));
    }
    return 0;
}
