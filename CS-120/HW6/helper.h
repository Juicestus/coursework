#ifndef HELPER_H
#define HELPER_H
#include "logic.h"

// constant value for tile width in console output
const int DISPLAY_WIDTH = 3;


// function signatures, do not change
void printInstructions();

void outputMap(char** board, const int maxRow, const int maxCol);

void outputStatus(const int status, const Player& player, int moves);

#endif
