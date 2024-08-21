#include "func.h"

int SumOfDigits(int val) {
    int sum = 0;
    for (; val > 0; val /= 10)
        sum += val % 10;
    return sum;
}
