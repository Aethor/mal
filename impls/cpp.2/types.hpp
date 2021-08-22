#ifndef TYPES
#define TYPES

#include <functional>
#include <list>
#include <memory>
#include <string>
#include <vector>


class MalObject {
public:
    virtual ~MalObject() = default;
};


class MalAtom: public MalObject { };

class MalScalar: public MalAtom {
public:
    int value;
    MalScalar(int value) : value(value) { };
};

class MalSymbol: public MalAtom {
public:
    std::string value;
    MalSymbol(std::string value) : value(value) { };
};

class MalString: public MalAtom {
public:
    std::string value;
    MalString(std::string value) : value(value) { };
};

class MalBool: public MalAtom {
public:
    bool value;
    MalBool(bool value) : value(value) { };
};


class MalList: public MalObject {

public:

    std::list<std::shared_ptr<MalObject>> elements;

    MalList(std::list<std::shared_ptr<MalObject>> elements) : elements(elements) { };

    bool is_empty();

};


class MalFunction: public MalObject {

public:

    std::function<std::shared_ptr<MalObject>(std::list<std::shared_ptr<MalObject>>)> value;

    MalFunction(std::function<std::shared_ptr<MalObject>(std::list<std::shared_ptr<MalObject>>)> value) : value(value) {};

};

#endif
