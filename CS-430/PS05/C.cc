#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> a(n, vector<ll>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m;j++)
        {
            cin >> a[i][j];
        }
    }

    ll T = 0;

   for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < m;j++)
        {
            ll low = 1;
            if (i > 0) low = max(low, a[i-1][j]+1);
            if (j>0) low = max(low, a[i][j-1]+1);

            int rp = (i+j)%2;
            if (a[i][j] != 0)
            {
                if (a[i][j] < low || (a[i][j] % 2) != rp)
                {
                    cout << "-1\n"; return 0;
                }
            } else {
                ll k = low;
                if ((k%2) != rp)
                    k++;
                a[i][j] = k;
            }
            T += a[i][j];

        }
    }
    cout << T<< "\n";
    return 0;

}
