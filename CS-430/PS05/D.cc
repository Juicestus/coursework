#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n,k;
vector<string> G;
vector<int> S;
vector<vector<vector<pair<int,int>>>> P;
bool U[5][5];

ll R = 0;

void B(int i)
{
    if (i ==k)
    {
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++)
                if (G[r][c] == 'o' && !U[r][c]) return;
        R++;
        return;
    }
    for (auto& p : P[i])
    {
        bool ok=1;
        for(auto& [r, c] : p)
        {
            if (U[r][c]) {
                ok=0; break;}
        }
        if(!ok)continue;
        for (auto [r, c] : p)
            U[r][c] = true;
        B(i+1);
        for (auto [r, c] : p)
            U[r][c] = false;
    }

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >>n>>k;

    G.resize(n);
    for (int i = 0; i < n; i++) cin>>G[i];

    S.resize(k);
    for (int i = 0; i < k; i++) cin >> S[i];

    P.resize(k);
    for (int i = 0; i < k; i++)
    {
        int l = S[i];
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                if (c+l <= n)
                {
                    bool ok = 1;
                    vector<pair<int,int>> C;
                    for (int j = 0; j < l; j++) {
                        if (G[r][c+j]=='X') { ok=0; break; }
                        C.push_back({r, c+j});
                    }
                    if (ok) P[i].push_back(C);
                }


                if (r +l <= n)
                {
                    bool ok=1;
                    vector<pair<int,int>> C;
                    for (int j = 0; j<l;j++)
                    {
                        if (G[r+j][c] == 'X') { ok = false; break; }
                        C.push_back({r+j, c});
                    }
                    if (ok) P[i].push_back(C);
                }
            }
        }
    }
    B(0);
    cout << R << "\n";
    
}
