#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int N;
    std::cin >> N;
    int K = 0;
    while (N--)
    {
        vector<int> v1, v2;
        int n, k;
        std::cin >> n;
        v1.reserve(n);
        v2.reserve(n);
        for(int _n = n; _n--; )
        {
            cin >> k;
            v1.push_back(k);
        }
        for(int _n = n; n--; )
        {
            cin >> k;
            v2.push_back(k);
        }
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end(), greater<int>());
        long long s  =0;
        for (int i = 0; i < v1.size(); i++)
        {
            s += (long long)v1[i] * (long long)v2[i];
            //s += v1[i] * v2[i];
        }
        std::cout << "Case #" << (++K) << ": " << s << "\n";
    }
}
