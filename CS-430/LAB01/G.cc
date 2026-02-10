#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int s, t, n, k;
    cin >> s >> t >> n;
    vector<int> ds, bs, cs;
    for (int i = 0; i <= n; i++)
    {
        cin >> k;
        ds.push_back(k);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> k;
        bs.push_back(k);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> k;
        cs.push_back(k);
    }
    int T = s;
    for (int i = 0; i < n; i++)
    {
        T += ds[i];
        //if (T > cs[i]) { cout << "no"; return 0; }
        //std::cout << T << " ";
        //T = cs[i] + bs[i];
        T = T / cs[i] + cs[i] + bs[i];
        //std::cout << T << "\n";
    }
    //std::cout << T << "\n";
    if (T + ds.back() <= t)
        std::cout << "yes";
    else
        cout << "no";
}
