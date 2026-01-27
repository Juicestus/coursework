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
    vector<int> board{};
    vector<int> seen{};
    board.push_back(0);
    while (n--)
    {
        int k;
        cin >> k;
        board.push_back(k);
        seen.push_back(0);
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
      
        int k = s + v;
        if (k < 1) {
            cout << "left\n";
            break;
        } 
        if (k >= board.size())
        {
            cout << "right\n";
            break;
        }
        seen[s] = true;
        h++;
        s = k;
    }
    cout << h << "\n";
}
