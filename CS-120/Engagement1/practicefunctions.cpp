#include "practicefunctions.h"

void makeary(char*& ary, unsigned int size) {
    ary = new char[size];
}

unsigned int sumary(const char* ary, unsigned int size) {
    unsigned int s = 0;
    for (unsigned int i = 0; i < size; i++) s += ary[i];
    return s;
}

void deleteary(char*& ary, unsigned int& size) {
    delete[] ary;
    ary = nullptr;
    size = 0;
}
