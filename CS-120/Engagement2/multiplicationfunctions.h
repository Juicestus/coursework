#ifndef MULTIPLICATIONFUNCTIONS_H
#define MULTIPLICATIONFUNCTIONS_H

void makeTable(int**& table, unsigned int rows, unsigned int cols);
void initializeTable(int** table, unsigned int rows, unsigned int cols);
void printTable(const int*const* nums, unsigned int rows, unsigned int cols);
void releaseTable(int**& table, unsigned int& rows, unsigned int& cols);

#endif
