#include <iostream>
#include <limits>

int main(int argc, char** argv) {
    double sum = 0, count = 0;
    for (double current ; ; count++) {
        std::cin >> current;
        if (current < 0) break;
        sum += current;
    }
    if (count <= 0) return 1;
    std::cout << sum / count << "\n";
}

