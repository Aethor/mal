#include <string>
#include <iostream>

std::string read() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::string eval(std::string input) {
    return input;
}

void print(std::string input) {
    std::cout << input << "\n";
}

int main(int argc,char* argv[]) {
    while (true) {
	std::string input;
	std::cout << "user> ";
	print(eval(read()));
    }
    return 0;
}
