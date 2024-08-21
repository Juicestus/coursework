#include <iostream>

double quad(double x, double a, double b, double c) {
    return a * x * x + b * x + c;
}

int main(int argc, char** argv) {
    double a = 0, b = 0, c = 0;
    std::cin >> a >> b >> c;

    double det = b * b - 4 * a * c;

    if (a == 0 || det < 0) {
        std::cout << "Can't solve.";
        return 0;
    }

    double x1 = ( -b - std::sqrt(det)) / (2 * a);

    std::cout << x1 << "\n";
    std::cout << quad(x1, a, b, c) << "\n";
}

