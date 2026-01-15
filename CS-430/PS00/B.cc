#include <iostream>
using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0);
    int N, P;
    cin >> N;
    cin >> P;
    string D;
    while (N--)
    {
        getline(cin, D);
    }
    std::cout << P;
}
