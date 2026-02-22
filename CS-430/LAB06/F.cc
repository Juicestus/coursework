#include <bits/stdc++.h>
using namespace std;

using ll = long long;

map<string, string> par;

string find(string i)
{
    if (par[i] == i) return i;
    return (par[i] = find(par[i]));
}

void unin(string i, string j)
{
    string ir = find(i);
    string jr = find(j);
    par[ir] = jr;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    
    vector<pair<string, string>> k(n);
    for (int i = 0; i < n; i++)
    {
        string a, b;
        cin >> a >> b;
        par[a] = a;
        par[b] = b;
        k[i] = make_pair(a, b);
    }

    for (auto& [a, b] : k)
    {
        unin(a, b);
    }

    for (auto& [a, b] : k)
    {
        cout << a << " " << find(a) << "\n";
    }

}
