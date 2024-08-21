#include <iostream>
#include "func.h"

int main(int argc, char** argv) {
    int val;
    std::cin >> val;
    std::cout << SumOfDigits(val) << "\n";
    return 0;
}
