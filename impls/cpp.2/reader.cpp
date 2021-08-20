#include "reader.hpp"
#include "types.hpp"
#include <iostream>
#include <list>
#include <memory>
#include <regex>
#include <string>


std::vector<std::string> tokenize(std::string const& str) {

    std::vector<std::string> matches;
    
    std::regex regex(
	R"([\s,]*(~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"?|;.*|[^\s\[\]{}('"`,;)]*))",
	std::regex_constants::ECMAScript
    );

    auto matches_start = std::sregex_iterator(str.begin(), str.end(), regex);
    auto matches_end = std::sregex_iterator();
    for (auto i = matches_start; i != matches_end; i++) {
	std::smatch match = *i;
	matches.push_back(match.str(1));
    }

    return matches;
}

std::shared_ptr<MalObject> read_str(std::string const& str) {
    auto tokens = tokenize(str);
    Reader reader(tokens);
    return reader.read_form();
}

std::string Reader::next() {
    std::string cur_token = this->tokens[this->cur_pos];
    this->cur_pos += 1;
    return cur_token;
}

std::string Reader::peek() {
    return this->tokens[this->cur_pos];
}

std::shared_ptr<MalList> Reader::read_list() {

    // consume "("
    this->next();

    std::list<std::shared_ptr<MalObject>> elements;

    while(true) {

	std::string token = this->peek();

	if (token == ")") {
	    this->next(); // consume ")"
	    return std::make_shared<MalList>(MalList(elements));
	}

	elements.push_back(this->read_form());

    } 
}

std::shared_ptr<MalAtom> Reader::read_atom() {

    std::string token = this->next();

    // number
    if (std::regex_match(token, std::regex(R"([0-9]+(\.[0-9]+)*)"))) {
	return std::make_shared<MalScalar>(std::stof(token));
	// return MalScalar(std::stof(token));
    } else { // symbol
	return std::make_shared<MalSymbol>(token);
	// return MalSymbol(token);
    }
}

std::shared_ptr<MalObject> Reader::read_form() {
    std::string cur_token = this->peek();
    if (cur_token == "(") {
	return this->read_list();
    } else {
	return this->read_atom();
    }
}
