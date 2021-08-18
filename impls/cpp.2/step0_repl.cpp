#include <string>
#include <iostream>

std::string& read(std::string& input) {
    return input;
}

std::string& eval(std::string& input) {
    return input;
}

std::string& print(std::string& input) {
    return input;
}

int main(int argc,char* argv[]) {
    while (true) {
	std::string input;
	std::cout << "user> ";
	//std::cin >> input;
	std::getline(std::cin, input);
	std::cout << read(eval(print(input))) << "\n";
    }
    return 0;
}
