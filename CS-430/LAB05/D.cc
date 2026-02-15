#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    map<string, int> kat;
    map<string, int> dom;

    for (int i = 0; i < n; i++)
    {
        string wd;
        cin >> wd;
        kat[wd]++;
    }
    for (int i = 0; i < n; i++)
    {
        string wd;
        cin >> wd;
        dom[wd]++;
    }

    int res = 0;
    
    for (auto [a, b] : kat)
    {
        //cout << a << b << "\n";
        res += min(b, dom[a]);
    }
    /*cout << "----\n";
    for (auto [a, b] : dom)
    {
        cout << a << b << "\n";
    }*/
    cout << res << "\n";




}
