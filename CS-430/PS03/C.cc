#include <bits/stdc++.h>
using namespace std;

using ll = long long;

map<string, string> parent;
map<string, int> sz;

void make(string b)
{
    if (parent.find(b) == parent.end())
    {
        parent[b] = b;
        sz[b] = 1;
    }
}

string find(string b)
{
    if (parent[b] != b)
    {
        parent[b] = find(parent[b]);
    }
    return parent[b];
}

int merge(string b1, string b2)
{
    string r1 = find(b1);
    string r2 = find(b2);

    if (r1 == r2) return sz[r1];

    if (sz[r1] < sz[r2]) swap(r1, r2);
    parent[r2] = r1;
    sz[r1] += sz[r2];
    return sz[r1];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    cin.ignore();

    while (n--)
    {
        string b1, b2;
        cin >> b1 >> b2;
        make(b1);
        make(b2);

        int r = merge(b1, b2);

        cout << r << "\n";
    }

}
