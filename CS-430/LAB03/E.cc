#include <bits/stdc++.h>
using namespace std;

void srt(
    vector<vector<char>>& grid,
    int c, int l, int u)
{
    //printf("[%d %d]\n", l, u);
    int a = 0;
    for (int r = l; r >= u; r--)
    {
        if (grid[r][c] == 'a')a++;
    }
    for (int r = l; r >= u; r--)
    {
        if (a)
        {
            grid[r][c] = 'a';
            a--;
        } else 
            grid[r][c] = '.';
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int R, C;
    cin >> R >> C;
    vector<vector<char>> grid(R);
    for (int r = 0; r < R; r++)
    {
        string row;
        cin >> row;
        grid[r] = vector<char>(C);
        for (int c = 0; c < C; c++)
            grid[r][c] = row[c];
    }


    for (int c = 0; c < C; c++)
    {
        //cout << c << ":\n";
        int b = R-1;
        for (int r = R - 1; r >= 0; r--)
        {
            if (grid[r][c] == '#')
            {
                srt(grid, c, b, r+1);
                b = r-1;
            }
        }
        srt(grid, c, b, 0);
    }

    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
            cout << grid[r][c];
        cout << "\n";
    }

}
