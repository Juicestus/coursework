#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class FWT{
    int n;
    vector<ll> b;
public:
    FWT(int n):n(n), b(n+1, 0) {}

    void U(int i, ll d)
    {
        while ( i<=n)
        {
            b[i] += d;
            i += i  & (-i);
        }
    }

    ll Q(int i)
    {
        ll s = 0;
        while (i>0)
        {
            s += b[i];
            i -= i & (-i);
        }
        return s;
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, Q;
    cin >> N>>Q;
    vector<ll> v(7);
    for (int i = 1; i <= 6; i++)
    {
        cin >> v[i];
    }
    string s;
    cin >> s;

    vector<FWT> trees;
    for (int i = 0; i < 6; i++)
    {
        trees.emplace_back(N);
    }

    vector<int> typ(N+1);
    for (int i=1; i <= N; i++)
    {
        typ[i] = s[i-1] - '0';
        trees[typ[i]-1].U(i, 1); 
    }
    
    while (Q--)
    {
        int t;
        cin >> t;

        if (t==1)
        {
            int k, p;
            cin >>k>>p;
            int o = typ[k];
            if (o != p)
            {
                trees[o-1].U(k, -1);
                trees[p-1].U(k, 1);
                typ[k]=p;
            }
        }
        else if (t==2)
        {
            int P;
            ll V;
            cin >> P >> V;
            v[P]=V;
        }
        else 
        {
            int l, r;
            cin >> l >> r;

            ll R = 0;
            for (int i = 1; i <= 6; i++)
            {
                ll c = trees[i-1].Q(r) - trees[i-1].Q(l-1);
                R += c * v[i];
            }
            cout << R << "\n";
        }
    }

    
}
