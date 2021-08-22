#include "readline.hpp"
#include "reader.hpp"
#include "types.hpp"
#include "printer.hpp"
#include <cstdlib>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>


typedef std::map<std::string, MalFunction> MalEnv;


std::shared_ptr<MalObject> read() {
    std::string input = string_readline("user> ");
    return read_str(input);
}

// declare eval
std::shared_ptr<MalObject> eval(std::shared_ptr<MalObject> const& input, MalEnv& env);

std::shared_ptr<MalObject> eval_ast(std::shared_ptr<MalObject> const& input, MalEnv& env) {

    if (dynamic_cast<MalList*>(input.get()) != nullptr) {
	std::list<std::shared_ptr<MalObject>> elements;
	for (auto elt: dynamic_cast<MalList*>(input.get())->elements) {
	    std::shared_ptr<MalObject> evaled = eval(elt, env);
	    elements.push_back(evaled);
	}
        return std::make_shared<MalList>(elements);
    }

    if (dynamic_cast<MalSymbol*>(input.get()) != nullptr) {
	MalSymbol *symbol = dynamic_cast<MalSymbol *>(input.get());
	auto it = env.find(symbol->value);
	if (it == env.end()) {
	    throw std::runtime_error("unknown symbol");
	}
	return std::make_shared<MalFunction>(it->second.value);
    }

    return input;
}

std::shared_ptr<MalObject> eval(std::shared_ptr<MalObject> const& input, MalEnv& env) {

    if (dynamic_cast<MalList *>(input.get()) != nullptr) {

	MalList *list = dynamic_cast<MalList *>(input.get());

	if (list->is_empty()) {
	    return input;
	}

	auto evaled = eval_ast(input, env);
	MalList *evaled_list = dynamic_cast<MalList *>(evaled.get());
	// function
        MalFunction *fn = dynamic_cast<MalFunction *>(evaled_list->elements.front().get());
	// arguments (copied ??? sadness lies here)
        std::list<std::shared_ptr<MalObject>> args;
        for (auto it = std::next(evaled_list->elements.begin()); it != evaled_list->elements.end(); it++) {
	    args.push_back(*it);
	}
	return fn->value(args);

    }

    return eval_ast(input, env);
}

void print(std::shared_ptr<MalObject> const& input) {
    std::cout << pr_str(input) << "\n";
}


int main() {

    MalEnv env = {
	{
	    "*",
	    MalFunction(
		[](std::list<std::shared_ptr<MalObject>> args) -> std::shared_ptr<MalObject> {
		    MalScalar *a = dynamic_cast<MalScalar*>(args.front().get());
		    args.pop_front();
		    MalScalar *b = dynamic_cast<MalScalar*>(args.front().get());
		    return std::make_shared<MalScalar>(a->value * b->value);
		}
	    )
	},
	{
	    "+",
	    MalFunction(
		[](std::list<std::shared_ptr<MalObject>> args) -> std::shared_ptr<MalObject> {
		    int sum = 0;
		    for (auto object: args) {
			sum += dynamic_cast<MalScalar*>(object.get())->value;
		    }
		    return std::make_shared<MalScalar>(sum);
		}
	    )
	},
	{
	    "-",
	    MalFunction(
		[](std::list<std::shared_ptr<MalObject>> args) -> std::shared_ptr<MalObject> {
		    MalScalar *a = dynamic_cast<MalScalar*>(args.front().get());
		    args.pop_front();
		    MalScalar *b = dynamic_cast<MalScalar*>(args.front().get());
		    return std::make_shared<MalScalar>(a->value - b->value);
		}
	    )
	},
	{
	    "/",
	    MalFunction(
		[](std::list<std::shared_ptr<MalObject>> args) -> std::shared_ptr<MalObject> {
		    MalScalar *a = dynamic_cast<MalScalar*>(args.front().get());
		    args.pop_front();
		    MalScalar *b = dynamic_cast<MalScalar*>(args.front().get());
		    return std::make_shared<MalScalar>(a->value / b->value);
		}
	    )
	},
	{
	    "exit",
	    MalFunction(
		[]([[maybe_unused]] std::list<std::shared_ptr<MalObject>> args) -> std::shared_ptr<MalObject> {
		    std::exit(0);
		}
	    )
	}
    };

    while (true) {

	std::shared_ptr<MalObject> input;
	try {
	     input = read();
	} catch(std::runtime_error& err) {
	    std::cerr << err.what() << "\n";
	    continue;
	}

	print(eval(input, env));
    }

    return 0;
}
