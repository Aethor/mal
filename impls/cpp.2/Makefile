CXX=g++
CXX_FLAGS=-Wall -std=c++14
LD=$(CXX)
LD_FLAGS=-L. -lreadline -lhistory


STEPS_SOURCES=$(wildcard step*.cpp)
STEPS=$(patsubst %.cpp,%,$(STEPS_SOURCES))

LIB_SOURCES=readline.cpp reader.cpp printer.cpp utils.cpp
LIB_OBJS=$(patsubst %.cpp,%.o,$(LIB_SOURCES))


all: $(STEPS)

debug: CXX_FLAGS += -DDEBUG -g
debug: $(STEPS)

$(STEPS): %: %.o libmal.a
	$(LD) $^ -o $@ $(LD_FLAGS)

libmal.a: $(LIB_OBJS)
	ar rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf libmal.a
	rm -rf $(STEPS)
