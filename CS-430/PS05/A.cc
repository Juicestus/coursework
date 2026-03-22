#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct E {
    ll s, e;
};

bool cmp(E& a, E& b)
{
    if (a.e == b.e) return a.s < b.s;
    return a.e < b.e;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;
    
    vector<E> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].s >> v[i].e;
    }

    sort(v.begin(), v.end(), cmp);



    ll res = 0;
    multiset<ll> et;
    for (int i = 0; i < n; i++)
    {
        auto it = et.lower_bound(-v[i].s);
        if (it == et.end())
        {
            if (et.size() < k)
            {
                et.insert(-v[i].e - 1);
                res++;
            }
        }
        else 
        {
            et.erase(it);
            et.insert(-v[i].e - 1);
            res++;
        }
    }

    cout << res << "\n";


}
