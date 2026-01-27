#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int N, M;
    std::cin >> N >> M;

    map<int, int> s{};

    for (int n = 1; n <= N; n++)
    {
        for (int m = 1; m <= M; m++)
        {
            //std::cout << n << " " << m << "\n";
            s[n+m]++;
        }
    }
    
    int m = 0;
    for (const auto& p : s) 
    {
        //cout << p.first << " " << p.second << "\n";
        m = max(p.second, m);
    }
    for (const auto& p : s) 
    {
        if (p.second == m)
        {
            std::cout << p.first << "\n";
        }
    }

}
