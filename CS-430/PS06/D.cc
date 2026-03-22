#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;
    while(N--)
    {
        int M;
        cin >>M;
        vector<int> d(M);
        int T = 0;
        for (int i = 0; i < M; i++)
        {
            cin>>d[i];
            T += d[i];
        }
#define BIG     1e9
        vector<int> dp(T+1, BIG);
        dp[0]=0;

        vector<vector<char>> ch(M, vector<char>(T+1, ' '));
        for (int i = 0; i <M;i++)
        {
            vector<int> ndp(T+1,BIG);
            for (int h = 0; h <= T; h++) 
            {
                if (dp[h] == BIG) continue;
                int nh=h+d[i];
                if (nh<=T)
                {
                    int nm=max(dp[h], nh);
                    if (nm<ndp[nh])
                    {
                        ndp[nh] = nm;
                        ch[i][nh] = 'U';
                    }
                }


                nh = h-d[i];
                if (nh >= 0)
                {
                    int nm = dp[h];
                    if (nm < ndp[nh])
                    {
                        ndp[nh] = nm;
                        ch[i][nh] = 'D';
                    }
                }
            }
            dp=ndp;
        }



        if (dp[0] ==BIG) cout << "IMPOSSIBLE\n";
        else 
        {
            string R(M, ' ');
            int H=0;
            for(int i = M-1; i >= 0; i--)
            {
                R[i] = ch[i][H];
                if (ch[i][H] == 'U') H -= d[i];
                else H+= d[i];
            }
            cout << R << "\n";
        }
    }
}
