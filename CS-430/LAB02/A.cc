#include <bits/stdc++.h>
using namespace std;


int main()
{
    using ll = long long;
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n; 
    cin >> n;
    vector<ll> v(n-1); 
    for (int i = 0; i < v.size(); i++)
    {
        cin >> v[i];
    }

    double tc = 0;
    ll need = 1;
    bool ok = false;

    double le = 0.594603557501, se = 0.420448207627;

    for (int i = 0; i < v.size() ;i++)
    {
        tc += need * le;
        double t = se;
        se = le / 2;
        le = t;

        need = (need * 2) - v[i];
        if (need <= 0) { ok = true; break; }
    }
    if (ok)
        printf("%.11f\n", tc);
    else cout << "impossible\n";

}
