#include <iostream>
#include "practicefunctions.h"

using std::cin, std::cout, std::endl;

void printary(std::ostream& os, const char*, unsigned int);
void loadary(std::istream& is, char*, unsigned int);

int main() {

  unsigned int size = 0;

  cout << "size: ";
  cin >> size;

  char* ary = nullptr;

  // make ary on heap
  makeary(ary, size);

  // load ary
  loadary(cin, ary, size);

  // print ary
  printary(cout, ary, size);

  // weird calculation
  cout << "sum values: " << sumary(ary, size) << endl;

  deleteary(ary, size);

}

void printary(std::ostream& os, const char* ary, unsigned int size) {
  for (unsigned int i=0; i<size; ++i) {
    os << ary[i] << " ";
  }
  os << endl;
}

void loadary(std::istream& is, char* ary, unsigned int size) {
  for (unsigned int i=0; i<size; ++i) {
    is >> ary[i];
  }
}
