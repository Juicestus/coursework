#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);


    int n, s, m;
    cin >> n >> s >> m;

    vector<int> b(n+1);
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    int h = 0;
    while (true)
    {
        if (b[s] == m)
        {
            cout << "magic\n";
            break;
        }
        if (b[s] == 0)
        {
            cout << "cycle\n";
            break;
        }
        int k = s;
        s += b[s];
        h++;
        b[k] = 0;
        if (s <= 0)
        {
            cout << "left\n";
            break;
        }
        if (s > n)
        {
            cout << "right\n";
            break;
        } 
    }
    
    cout << h << "\n";
}
