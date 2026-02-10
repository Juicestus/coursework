#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> grid{};
vector<vector<bool>> vis{};

int _N = 0;

bool K(int r, int c)
{
    return r >= 0 && r < _N && c >=0 && c < 3;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N;
    cin >> N;
    _N = N;
    string line;
    grid.reserve(N);
    for (int i = 0; i < N; i++)
    {
        cin >> line;
        grid.push_back(vector<char>(3));
        for (int j = 0; j < 3; j++) grid[i][j] = line[j];
    }

    vis.assign(N, vector<bool>(3, false));

    queue<pair<int,int>> q;
    for (int j = 0; j < 3; j++)
    {
        if (grid[0][j] == '.')
        {
            q.emplace(0, j);
            vis[0][j] = true;
        }
    }


    while (!q.empty())
    {
        auto [r,c] = q.front(); q.pop();
        if (r == N-1)
        {
            cout << "YES\n";
            return 0;
        }

        char cur = grid[r][c];
        for (int dc : {-1, 1})
        {
            int nc = c + dc;
            if (!K(r, nc)) continue;
            if (grid[r][nc] == cur && !vis[r][nc])
            {
                vis[r][nc] = true;
                q.emplace(r, nc);
            }
        }

        if (cur == '.')
        {
            if (K(r+1, c) && grid[r+1][c] == '.' && !vis[r+1][c])
            {
                vis[r+1][c] = true;
                q.emplace(r+1, c);
            }
            if (K(r+1, c) && grid[r+1][c] == '/' && K(r+2, c) && grid[r+2][c] == '*' && !vis[r+2][c])
            {
                vis[r+2][c] = true;
                q.emplace(r+2, c);
            }
        }
        else if (cur == '*')
        {
            if (K(r+1, c) && (grid[r+1][c] == '.' || grid[r+1][c] == '*') && !vis[r+1][c])
            {
                vis[r+1][c] = true;
                q.emplace(r+1, c);
            }
        }
    }

    cout << "NO\n";
    return 0;
}
