#include <bits/stdc++.h>
using namespace std;

using ll = long long;


vector<int> tree;
int n;

void insert(int i, int d)
{
    i++;
    while (i <= n)
    {
        tree[i] += d;
        i += i & (-i);
    }
}

int query(int i)
{
    i++;
    int s = 0;
    while (i > 0) {
        s += tree[i];
        i -= i & (-i);
    }
    return s;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    tree = vector<int>(n+1, 0);

    vector<pair<int, int>> k(n);
    for (int i = 0; i < n; i++)
    {
        int o;
        cin >> o;
        k[i] = {o, i};
    }

    sort(k.begin(), k.end());

    ll tm=0;
    int P=0;

    for (int s = 0; s < n; s++)
    {
        int t = k[s].second;

        int db = t>0 ? query(t-1) : 0;
        int p  = t-db;

        int r = n-s;

        int s1 = (p - P + r) % r;
        int s2 = (P - p + r) % r;

        tm += min(s1, s2)+1;
        P = p;

        insert(t, 1);
    }
    cout << tm << "\n";

}
