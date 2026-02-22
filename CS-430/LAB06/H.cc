#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int R, C;

vector<vector<char>> G;
vector<vector<bool>> V;

int mvs = 0;
bool out = false;

bool rec(int r, int c)
{
    if (c < 0 || c >= C || r == R || r < 0) {
        out = true;
        return false;
    }
    char k = G[r][c];
    if (V[r][c])  return false;
    V[r][c] = 1;
    mvs++;
    if (k == 'N') return rec(r-1, c);
    if (k == 'S') return rec(r+1, c);
    if (k == 'W') return rec(r, c-1);
    if (k == 'E') return rec(r, c+1);
    if (k == 'T') return true;
    mvs--;
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> R >> C;
    G = vector<vector<char>>(R, vector<char>(C));
    V = vector<vector<bool>>(R, vector<bool>(C, false));

    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            cin >> G[r][c];
        }
    }
    if (rec(0, 0)) 
        cout << mvs-1 << "\n";
    else  {
        if (out) cout << "Out\n";
        else cout << "Lost";
    }





}
