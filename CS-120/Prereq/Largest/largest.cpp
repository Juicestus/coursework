#include <iostream>
#include <limits>

#define IN_EXP 3    // number of expected inputs

int main(int argc, char** argv) {
    double largest = std::numeric_limits<double>().min();
    double current = 0;
    for (int i = 0; i < IN_EXP; i++) {
        std::cin >> current;
        if (current > largest) {
            largest = current;
        }
    }
    std::cout << largest << "\n";
}

