#include <iostream>
#include <iomanip>
#include "multiplicationfunctions.h"

using std::cin, std::cout, std::endl;
using std::setw;

void initializeTable(int** table, unsigned int rows, unsigned int cols) {
  for (unsigned int row=0; row<rows; ++row) {
    for (unsigned int col=0; col<cols; ++col) {
      table[row][col] = 0;
    }
  }
}


void printTable(const int*const* table, unsigned int rows, unsigned int cols) {
  if (rows == 0 || cols == 0) {
    throw std::invalid_argument("Must have at least one row and one column");
  }
  // print header
  cout << setw(3) << "|";
  for (unsigned int col=0; col<cols; ++col) {
    cout << setw(3) << (col+1);
  }
  cout << endl;
  for (unsigned int col=0; col<=cols; ++col) {
    cout << "---";
  }
  cout << endl;
  for (unsigned int row=0; row<rows; ++row) {
    cout << (row+1) << " |";
    for (unsigned int col=0; col<cols; ++col) {
      cout << setw(3) << table[row][col];
    }
    cout << endl;
  }
}

void makeTable(int**& table, unsigned int rows, unsigned int cols) {
    // create 2d array on the heap
    table = new int*[rows];
    for (unsigned int i = 0; i < rows; i++) {
        table[i] = new int[cols];
    }
}

void releaseTable(int**& table, unsigned int& rows, unsigned int& cols) {
    // release memory from the heap and set variables to values consistent with an empty array
    for (unsigned int i = 0; i < rows; i++) {
        delete[] table[i];
    }
    delete[] table;
    table = nullptr;
    rows = 0;
    cols = 0;
}
