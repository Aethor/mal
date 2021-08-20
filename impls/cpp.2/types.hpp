#ifndef TYPES
#define TYPES

#include <list>
#include <memory>
#include <string>


class MalObject {
public:
    virtual ~MalObject() = default;
};


class MalAtom: public MalObject { };

class MalScalar: public MalAtom {
public:
    float value;
    MalScalar(float value) : value(value) { };
};

class MalSymbol: public MalAtom {
public:
    std::string value;
    MalSymbol(std::string const& value) : value(value) { };
};

class MalString: public MalAtom {
public:
    std::string value;
    MalString(std::string const& value) : value(value) { };
};

class MalBool: public MalAtom {
public:
    bool value;
    MalBool(bool value) : value(value) { };
};


class MalList: public MalObject {

public:

    std::list<std::shared_ptr<MalObject>> elements;

    MalList(std::list<std::shared_ptr<MalObject>> const& elements) : elements(elements) { };

};

#endif
