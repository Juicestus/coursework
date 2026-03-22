#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    ll l, d;
    int n;
    cin >> l >> d >> n;
    
    vector<ll> p(n);
    for (int i=0; i <n;i++) cin >> p[i];
    sort(p.begin(), p.end());
    
    vector<ll> P;
    P.push_back(6-d);
    for (ll i:p) P.push_back(i);
    P.push_back(l-6+d);

    ll a = 0;
    for (int i = 1; i < P.size(); i++)
    {
        ll G = P[i] - P[i-1]  - d;
        if (G>=0)
            a += G/d;
    }
    cout << a << "\n";


}
