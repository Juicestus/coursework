#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int cnt(vector<int>& ns, int l, int r, int b)
{
    if (l == r) return 0;
    printf("(%d %d): ", l, r);
    vector<pair<int, int>> rng{};
    bool in = 0;
    int L = 0;
    for (int i = l; i < r; i++)
    {
        cout << i << " " ;
        if (ns[i] <= b)
        {
            cout << j << " " ;
            if (in)
            {
                rng.push_back(make_pair(L, i));
            }
            in = false;
        } else {
            in = true;
            L = i;
        }
    }
    for (int i = 0; i < rng.size(); i++)
    {
        printf("(%d %d) ", rng[i].first, rng[i].second);
    }

    int c = rng.size();
    cout << " " << c << "\n";
    for (int i = 0; i < c; i++)
    {
        c += cnt(ns, rng[i].first, rng[i].second, b+1);
    }
    return c;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    for (int k = 1; k <= n; k++)
    {
        int _k;
        cin >> _k;
        int nil = 0;
        vector<int> a(12);
        for (int i = 0; i < 12; i++)
        {
            cin >> a[i];
        }

        int c = cnt(a, 0, 12 , 0);

        cout << k << " " << c << "\n";
    }


}
