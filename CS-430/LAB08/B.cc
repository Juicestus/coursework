#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<pair<string, double>> a, b;
    while (n--)
    {
        string k;
        double _a, _b;
        cin >> k >> _a >> _b;
        a.push_back(make_pair(k, _a));
        b.push_back(make_pair(k, _b));
    }
    auto C = [](const auto& a, const auto& b) {
        return a.second < b.second;
    };
    sort(a.begin(), a.end(), C);
    sort(b.begin(), b.end(), C);
    
    vector<string> bnames(4);
    double bt = 1000000000;
    for (int i = 0; i < 4; i++)
    {
        double t = a[i].second;
        string fg = a[i].first;
        int p = 0;
        vector<string> names(4);
        names[0] = fg;
        for (int j = 0; j < 4; j++)
        {
            if (b[j].first == fg) continue;
            t += b[j].second;
            p++;
            names[p] = b[j].first;
            if (p == 3) break;
        }
        if (t < bt)
        {
            bt = t;
            bnames = names;
        }
    }
    cout << bt << "\n";
    for (auto n : bnames)
    {
        cout << n << "\n";
    }
}
