#include <iostream>


int main(int argc, char** argv)
{
    const int N = 20;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j < i; j++) std::cout << "#";
        for (int j = i; j < N; j++) std::cout << "0";
        std::cout << "\n";
    }
}
