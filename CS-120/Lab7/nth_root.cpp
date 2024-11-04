#include <iostream>
#include <string>

#define print(X) std::cout << X << std::endl

double nth_root(int n, double x) {
    // this code is here to estimate test coverage when running locally
    // it is not an implementation of the function
    // you should NOT implement this function for this labwork
    // you should NOT submit this file to Mimir
    // you are to ONLY WRITE TEST CASES (in test_nth_root.cpp)

    std::string covered;

    if (n == 0) {
        covered += "A";  // n = 0
    } else if (n%2 == 0 && x < 0) {
        covered += "B";  // even root of a negative number
    } else if (n < 0 && x == 0) {
        covered += "C";  // negative root of 0
    } else {
        if (n == 1) {
            covered += "D";  // n = 1
        }
        if (n == -1) {
            covered += "E";  // n = -1
        }
        if (n < 0) {
            covered += "F";  // n < 0
        }
        if (n < -5) {
            covered += "G";  // n < -5
        }
        if (n < -1 && n >= -5) {
            covered += "H";  // -5 <= n < -1
        }
        if (n > 5) {
            covered += "I";  // n > 5
        }
        if (n > 1 && n <= 5) {
            covered += "J";  // 1 < n <= 5
        }
        if (n > 0 && x == 0) {
            covered += "K";  // positive root of 0
        }
        if (x == 1) {
            covered += "L";  // nth root of 1
        }
        if (n%2 == 1 && x < 0 && x != -1) {
            covered += "M";  // odd root of a negative number other than -1
        }
        if (x > 2) {
            covered += "N";  // nth root of a number greater than 2
        }
        if (x - static_cast<int>(x) > 0) {
            covered += "O";  // nth root of a number with a fractional part
        }
        covered += "P";  // valid input
    }

    print(covered);

    return 0;
}
