#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    while(n--)
    {
        int m;
        cin >> m;

        vector<array<int, 8>> P(m);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < 8;j++)
                cin >> P[i][j];

        vector<int> r(8);
        for (int s = 0; s < 8; s++) r[s] = s;

        for (int i = m - 1; i >= 0; i--)
        {
            vector<int> r2(8);
            for (int s = 0; s < 8; s++)
            {
                int o = -1;
                int p = 9;
                for (int F = 0; F < 3; F++)
                {
                    int ns = s ^ (1 << F);
                    int O = r[ns];
                    if (P[i][O] < p)
                    {
                        p = P[i][O];
                        o = O;
                    }
                }
                r2[s] = o;
            }
            r = r2;
        }
        
        int a = r[0];
        cout << ((a & 4) ? 'Y' : 'N');
        cout << ((a & 2) ? 'Y' : 'N');
        cout << ((a & 1) ? 'Y' : 'N');
        cout << "\n";

    }
}
