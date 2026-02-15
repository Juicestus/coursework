#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    int s;
    cin >> s;
    vector<int> e(n);
    for (int i = 0; i < n; i++)
    {
        cin >> e[i];
    }
    sort(e.begin(), e.end());

    int S = 0, w = 0;
    for (int i = 0; i < e.size(); i++)
    {
        S += e[i] + 1;
        if (S > s) break;
        else w++;
    }
    

    cout << w << "\n";

}
