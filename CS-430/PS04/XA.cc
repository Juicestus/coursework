#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    vector<int> k(n);
    for (int i = 0; i < n; i++)
    {
        cin >> k[i];
        k[i]--;
    }

    ll tm=0;

    for (int s = 0; s < n; s++)
    {
        int t = k[s];
        int p = t;
        for (int j = 0; j < s; j++)
        {
            if (k[j] < t) p--;
        }

        int r = n-s;
        tm += min(p, r-p) +1;
    }
    cout << tm << "\n";

}
