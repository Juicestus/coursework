#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    map<string, vector<int>> trips{};

    int N;
    cin >> N;
    while (N--)
    {
        string k;
        int v;
        cin >> k >> v;
        trips[k].push_back(v);
        //cout << k << "->" << v << "\n";
    }

    for (auto& [k, vl] : trips)
    {
        sort(trips[k].begin(), trips[k].end());
        //std::cout << k << "->" << trips[k].size() << "\n";
    }

    cin >> N;
    while (N--)
    {
        string k;
        int v;
        cin >> k >> v;
        cout << trips[k][v-1] << "\n";
    }

}
