#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N,K;
    while (cin>>N>>K)
    {
        if (!(N||K)) break;
        vector <int> a(N), b(N);
        int T = 0;
        for (int i = 0; i < N; i++)
        {
            cin >> a[i] >> b[i];
                T+= a[i] + b[i];
        }
#define BIG 1e9
        vector<vector<int>> dp(K+1, vector<int>(3, BIG));
        dp[0][0] = 0;

        for (int i = 0; i < N; i++) 
        {
            vector<vector<int>> ndp(K + 1, vector<int>(3, BIG));
            for (int j = 0; j <= K;j++) 
            {
                for (int s = 0;s < 3; s++) 
                {
                    if (dp[j][s] ==BIG) continue;

                    ndp[j][0] = min(ndp[j][0], dp[j][s]);
                    if (j+1<=K)
                    {

                    if (s != 2)
                        ndp[j+1][1] = min(ndp[j+1][1], dp[j][s] + a[i]);
                    if (s != 1)
                        ndp[j+1][2] = min(ndp[j+1][2], dp[j][s] + b[i]);
                    }

                }
            }
            dp=ndp;
        }
        int mc = BIG;
        for (int s = 0;s < 3; s++) 
            mc = min(mc, dp[K][s]);
        cout << T - mc << "\n";
    }

}
