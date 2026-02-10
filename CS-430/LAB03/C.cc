#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    map<ll, int> freq;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        vector<int> cs(5);
        for (int j = 0; j < 5; j++) cin >> cs[j];
        sort(cs.begin(), cs.end());
        long long hash = 0, M = 1;
        for (int j = 0; j < 5; j++) {
            hash += cs[j] * M;
            M *= 1000;
        }
        freq[hash]++;
        //cout << hash << "\n";
    }
    
    int m = 0;
    for (auto& [k, v] : freq)
    {
        m = max(m, v);
    }
    ll s = 0;
    for (auto& [k, v] : freq)
    {
        if (v == m)
            s += v;
    }

    cout << s << "\n";


}
