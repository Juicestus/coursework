#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define pq priority_queue
#define umap unordered_map
#define uset unordered_set

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    map<int, pq<int>> m;

    while (n--)
    {
        string op;
        cin >> op;

        if (op == "add")
        {
            int e, g;
            cin >> e >> g;
            if (m.find(e) == m.end())
                m[e] = pq<int>();
            m[e].push(g); 
        }
        else
        {
            int e;
            cin >> e;
            ll sum = 0;
            while (!m.empty())
            {
                auto it = m.upper_bound(e);
                if (it==m.begin()) break;
                --it;

                int bk=it->first;
                sum+=it->second.top();
                e-=bk;
                it->second.pop();

                if (it->second.empty()) m.erase(it);
            }
            cout << sum << "\n";
        }
    }


}
