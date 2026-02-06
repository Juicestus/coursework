#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n, s, m;
    cin >> n >> s >> m;
    //string _;
    //getline(cin, _);
    vector<int> board(n+1);
    vector<int> seen(n+1, 0);
    board.push_back(0);

    for (int i = 1; i < n; i++)
    {
        cin >> board[i];
    }
    //s--;
    int h = 0;
    while (true)
    {
        int v = board[s];

        if (v == m)
        {
            cout << "magic\n";
            break;
        }

        if (seen[s])
        {
            cout << "cycle\n";
            break;
        }
        
        seen[s] = 1;
        s += v;
        h++;
        if (s < 1) {
            cout << "left\n";
            break;
        } 
        if (s >= n)
        {
            cout << "right\n";
            break;
        }
    }
    cout << h << "\n";
}
