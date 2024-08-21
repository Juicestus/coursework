#include "func.h"

int SumOfDigits(int val) {
    bool neg = val < 0;
    int sum = 0, ld = 0, rd = val % 10;
    for (val /= 10; val != 0; val /= 10) {
        ld = val % 10;
        if (ld % 2 == 0) sum += rd;
        else sum -= rd;
        rd = ld;
    }
    sum += ld;
    if (neg) sum *= -1;
    return sum;
}
