CXX=g++
CXXFLAGS=-std=c++17 -g -pedantic -Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer
LDLIBS=-lrt


SRCS=MasterChef.cpp
DEPS=Step.cpp StepList.cpp
BINS=$(SRCS:%.cpp=%.exe)
OBJS=$(DEPS:%.cpp=%.o)


all: clean $(BINS)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.exe: %.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(patsubst %.exe,%,$@) $^ $(LDLIBS)


.PHONY: clean test

clean:
	rm -f MasterChef ./test-files/cmd*.txt out1.txt out2.txt trace.txt

test: all
	chmod u+x le5-tests.sh
	./le5-tests.sh