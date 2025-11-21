CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -ggdb -Og -fsanitize=address -fsanitize=undefined
CXXFLAGS_TSAN=-Wall -pedantic -std=c++17 -ggdb -Og -fsanitize=thread -D_GLIBCXX_DEBUG

all: pool-test pool-test-tsan

%-tsan.o: %.cc
	$(CXX) -c $(CXXFLAGS_TSAN) -o $@ $<

libpool.a: pool.o
	ar rcs $@ $^

libpool-tsan.a: pool-tsan.o
	ar rcs $@ $^

pool.o: pool.cc pool.h
pool-tsan.o: pool.cc pool.h

pool-test.o: pool-test.cc pool.h
pool-test-tsan.o: pool-test.cc pool.h

pool-test: pool-test.o libpool.a
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread

pool-test-tsan: pool-test-tsan.o libpool-tsan.a
	$(CXX) $(CXXFLAGS_TSAN) -o $@ $^ -lpthread

SUBMIT_FILENAME=pool-submission-$(shell date +%Y%m%d%H%M%S).tar.gz

submit:
	tar -zcf $(SUBMIT_FILENAME) $(wildcard *.cc *.h *.hh *.H *.cpp *.C *.c *.txt *.md *.pdf) Makefile 
	@echo "Created $(SUBMIT_FILENAME); please upload and submit this file."

skeleton: pool-base.h pool-base.cc
	rm -f pool-skeleton.tar.gz
	rm -rf for-skeleton
	mkdir -p for-skeleton/pool
	cp pool-base.h for-skeleton/pool/pool.h
	cp pool-base.cc for-skeleton/pool/pool.cc
	cp pool-test.cc Makefile for-skeleton/pool/
	cd for-skeleton && tar zcvf ../pool-skeleton.tar.gz pool

clean:
	rm -f *.o

.PHONY: all clean submit skeleton