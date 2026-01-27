#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> grid{};
vector<vector<bool>> dp{};
int endi = 0;

bool rec(int i, int j)
{
    cout << "rec(" << i << " " << j << ")\n";
    if (i == endi) return true;
    if (dp[i][j]) return false;
    dp[i][j] = true;

    if (grid[i][j] == '*')
    {
        if (j != 0 && grid[i][j-1] == '*')
            if (rec(i, j-1)) return true;
        if (j != 2 && grid[i][j+1] == '*')
            if (rec(i, j+1)) return true;
        if (grid[i+1][j] == '*' || grid[i+1][j] == '.')
            if (rec(i+1, j)) return true;

        return false;
    }

    if (grid[i][j] == '.')
    {
        if (j != 0 && grid[i][j-1] == '.')
            if (rec(i, j-1)) return true;
        if (j != 2 && grid[i][j+1] == '.')
            if (rec(i, j+1)) return true;
        if (grid[i+1][j] == '.')
            if (rec(i+1, j)) return true;

        if (grid[i+1][j] == '/')
            if (rec(i+2, j)) return true;

        return false;
    }

    return false;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int N;
    cin >> N;
    string _;
    getline(cin, _);
    endi = N-1;
    
    while (N--)
    {
        string r;
        cin >> r;
        grid.push_back(vector<char>());
        grid.back().push_back(r[0]);
        grid.back().push_back(r[1]);
        grid.back().push_back(r[2]);
        dp.push_back(vector<bool>());
        dp.back().push_back(0);
        dp.back().push_back(0);
        dp.back().push_back(0);

    }
    
    for (int i = 0; i < 2; i++)
    {
        if (grid[0][i] != '.') continue;
        if (rec(0, i))
        {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";

}
