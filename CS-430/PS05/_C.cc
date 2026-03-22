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
            if (a[i][j]!=0)
            {
                if (a[i][j] < low)
                {
                    cout << "-1\n"; return 0;
                }
                if (i > 0 && j > 0)
                {
                    if ((a[i][j] % 2) == (a[i-1][j-1] % 2))
                    {
                        cout << "-1\n"; return 0;
                    }
                }
                if (i>0&&j+1 < m && a[i-1][j+1]!=0)
                {
                    if ((a[i][j] % 2) == (a[i-1][j+1] % 2))
                    { cout << "-1\n"; return 0; }
                }
            } else 
            {
                ll k = low;
                ll nn=-1;
                if (i>0 && j > 0)
                    nn = 1-(a[i-1][j-1]%2);
                if (i>0&&j+1 < m) 
                {
                    ll n2 = 1-(a[i-1][j+1] % 2);
                    if (nn != -1 && nn != n2) { cout << "-1\n"; return 0; }
                    nn=n2;
                }
                if (nn!=-1 && (k%2) != nn) k++;
                a[i][j]=k;
            }
            T += a[i][j];

        }
    }
    cout << T<< "\n";
    return 0;

}
