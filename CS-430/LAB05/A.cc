#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<int> ns(n);
    vector<pair<int, int>> mn(n);
    for (int i = 0; i < n; i++)
    {
        cin >> ns[i];
        mn[i] = make_pair(ns[i], i);
    }
    sort(mn.begin(), mn.end());

    cout << mn[0].first << " " << mn[1].second << "\n";



}
