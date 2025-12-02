CXX=g++
CXXFLAGS=-std=c++23 -I. -g3 -Wpedantic -Wall -Wextra -Werror -Wconversion -Wfloat-equal


SRCS=Teller.cpp
DEPS=BankAccount.cpp
BINS=Teller
OBJS=Teller.o BankAccount.o

all: $(BINS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

$(BINS): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(BINS)

.PHONY: clean test
clean:
	@rm -f $(BINS) $(OBJS) out.trace ./test-files/cmd*.txt ./test-files/add*.txt

test: all
	@chmod u+x le5-tests.sh
	@./le5-tests.sh
