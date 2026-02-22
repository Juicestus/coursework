#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool rep(ll t, ll c)
{
    ll a = t*c;
    ll b = c-t;

    if (b<=0) return false;
    return a%b == 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string s;
    while (cin>>s)
    {
        s.erase(0, 2);

        ll n = stoi(s), c = 0;
        for (ll i = n; i <= n*2; i++)
        {
            if (rep(n, i)) c++;
        }
        cout << c << "\n";
    }
}
