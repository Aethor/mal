CXX=g++
CXX_FLAGS=-Wall -std=c++11
LD=$(CXX)
LD_FLAGS=-L.

STEPS_SOURCES=$(wildcard step*.cpp)
STEPS=$(patsubst %.cpp,%,$(STEPS_SOURCES))
STEPS_OBJS=$(patsubst %.cpp,%.o,$(STEPS_SOURCES))

$(info sources is $(STEPS_SOURCES))
$(info steps is $(STEPS))
$(info objs is $(STEPS_OBJS))


all: $(STEPS)

$(STEPS): $(STEPS_OBJS)
	$(LD) $^ -o $@ $(LD_FLAGS)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -rf $(STEPS_OBJS)
	rm -rf $(STEPS)
