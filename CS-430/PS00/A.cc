#include <iostream>

int main(int argc, char** argv)
{
    int n, k;
    long long sum = 0;
    std::cin >> n;
    while (n-- > 0)
    {
        std::cin >> k;
        sum += k;
    }
    std::cout << sum;
}
