#include <iostream>
#include <cmath>
#include "nth_root.h"

#define test_nth_root(A, B) std::cout << "nth_root(" << A << ", " << B <<") = " << nth_root(A, B) << std::endl;

using std::cout, std::endl;

int main() {
    {   // MINIMUM REQUIREMENT (for this lab)
        // just call the function with various values of n and x
        // nth_root1);
        // nth_root(2, -2);
        // nth_root(-1, 0);
        // nth_root(1, 1);
        // nth_root(-1, 1);
        // nth_root(-2, 1);
        // nth_root(-10, 1);
        // nth_root(-3, 1);
        // nth_root(10, 1);
        // nth_root(2, 0);
        // nth_root(4, 1);
        // nth_root(1, -2);
        // nth_root(3, 2);
        // nth_root(3, 2.5);

        // nth_root(2, 1);
        // nth_root(4, 2);
        // nth_root(-1, 3);
        // nth_root(M_E, M_PI);
        // nth_root(2025, 7);
    }

    {   // TRY HARD
        // report the value
        try {
            test_nth_root(0, 1);
            cout << "[FAIL] expected an exception, none thrown." << endl;
        } catch (const std::domain_error& e) {
                cout << "[PASS] caught an exception." << endl;

        }
        try {
            test_nth_root(-1, 0);
            cout << "[FAIL] expected an exception, none thrown." << endl;
        } catch (const std::domain_error& e) {
                cout << "[PASS] caught an exception." << endl;
        }
        test_nth_root(1, 1);
        test_nth_root(-1, 1);
        test_nth_root(-2, 1);
        test_nth_root(-10, 1);
        test_nth_root(-3, 1);
        test_nth_root(10, 1);
         try {
            test_nth_root(0, 3);
            cout << "[FAIL] expected an exception, none thrown." << endl;
        } catch (const std::domain_error& e) {
                cout << "[PASS] caught an exception." << endl;
        }

         try {
            test_nth_root(-2, 0);
            cout << "[FAIL] expected an exception, none thrown." << endl;
        } catch (const std::domain_error& e) {
                cout << "[PASS] caught an exception." << endl;
        }

        try {
            test_nth_root(-2, 2);
            cout << "[FAIL] expected an exception, none thrown." << endl;
        } catch (const std::domain_error& e) {
                cout << "[PASS] caught an exception." << endl;
        }
         try {
            test_nth_root(2, -2);
            cout << "[FAIL] expected an exception, none thrown." << endl;
        } catch (const std::domain_error& e) {
                cout << "[PASS] caught an exception." << endl;
        }
        test_nth_root(4, 1);
        test_nth_root(1, -2);
        test_nth_root(3, 2);
        test_nth_root(3, 2.5);

        try {
            test_nth_root(-1.5, -1);
            cout << "[FAIL] expected an exception, none thrown." << endl;
        } catch (const std::domain_error& e) {
                cout << "[PASS] caught an exception." << endl;

        }

        test_nth_root(2, 1);
        test_nth_root(4, 2);
        test_nth_root(-1, 3);
        test_nth_root(M_E, M_PI);
        test_nth_root(2025, 7);

    }

    {   // TRY HARDER
        // compare the actual value to the expected value
        double actual = nth_root(2, 1);
        double expected = 1;
        if (std::fabs(actual - expected) > 0.00005) {
            std::cout << "[FAIL] (n=2, x=1)" << std::endl;
            std::cout << "  expected nth_root(2, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        } else {
            std::cout << "[PASS] (n=2, x=1)" << std::endl;
        }
    }
}
