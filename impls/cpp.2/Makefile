CXX=g++
CXX_FLAGS=-Wall -std=c++11
LD=$(CXX)
LD_FLAGS=-L. -lreadline -lhistory


STEPS_SOURCES=$(wildcard step*.cpp)
STEPS=$(patsubst %.cpp,%,$(STEPS_SOURCES))
STEPS_OBJS=$(patsubst %.cpp,%.o,$(STEPS_SOURCES))

LIB_SOURCES=readline.cpp
LIB_OBJS=$(patsubst %.cpp,%.o,$(LIB_SOURCES))


all: $(STEPS)

$(STEPS): $(STEPS_OBJS) libmal.a
	$(LD) $^ -o $@ $(LD_FLAGS)

libmal.a: $(LIB_OBJS)
	ar rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -rf $(STEPS_OBJS)
	rm -rf $(STEPS)
