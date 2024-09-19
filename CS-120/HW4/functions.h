#include <climits>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

const unsigned int MAX_ARRAY_SIZE = 1000;

// return true if the sum of the arguments is even
bool SumIsEven(int a, int b);

// return the largest of the arguments
int Largest(int a, int b, int c);

/// return the number of boxes needed to store the given number of apples
unsigned int BoxesNeeded(int apples);

// return true if section A performs better than section B
// throws std::invalid_argument if the arguments are invalid
bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total);

// return true if you had a good dinner
bool GoodDinner(int pizzas, bool is_weekend);

// return the sum of all integers from low to high (inclusive)
// throw std::invalid_argument if low and high are out of order
// throw std::overflow_error if the sum exceeds the maximum/minimum value of a signed 32-bit integer.
long long SumBetween(long long low, long long high);

// return the product of a and b
// throw std::overflow_error if the product exceeds the maximum/minimum value of a signed 32-bit integer.
long long Product(long long a, long long b);

#endif  // FUNCTIONS_H
