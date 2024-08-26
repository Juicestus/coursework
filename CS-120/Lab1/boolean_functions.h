#ifndef BOOLEAN_FUNCTIONS_H
#define BOOLEAN_FUNCTIONS_H

#include <string>

// 1. [5 points] Print the truth table for NOT
void printNOT();
// 2. [5 points] Print the truth table for OR
void printOR();
// 3. [5 points] Print the truth table for AND
void printAND();
// 4. [5 points] Print the truth table for XOR
void printXOR();
// 5. [15 points] Compute x OR y OR z, given an assignment of truth values
bool booleanLogic1(bool x, bool y, bool z);
// 6. [15 points] Compute x AND y AND z, given an assignment of truth values
bool booleanLogic2(bool x, bool y, bool z);
// 7. [15 points] Compute x XOR y XOR z, given an assignment of truth values
bool booleanLogic3(bool x, bool y, bool z);
// 8. [5 points] debug function
// function counts the letters in the string
unsigned int countLetters(std::string str);
// 9. [15 points] find boolean formula for the truth table
bool f(bool x, bool y, bool z);
// 10. [15 points] find assignments to satisfy boolean formula
// you do not need to implement this function, just assign values to the variables
void setAssignments(bool& w, bool& x, bool& y, bool& z);

#endif