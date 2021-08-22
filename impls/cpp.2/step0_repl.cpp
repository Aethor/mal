#include "readline.hpp"
#include <string>
#include <iostream>

std::string read() {
    return string_readline("user> ");
}

std::string eval(std::string input) {
    return input;
}

void print(std::string input) {
    std::cout << input << "\n";
}

int main() {
    while (true) {
	print(eval(read()));
    }
    return 0;
}
