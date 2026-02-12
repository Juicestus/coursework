#include <bits/stdc++.h>
using namespace std;
#define uset unordered_set

struct team {
    int a;
    int b;

    team() : a(0), b(0) {}
    team(int a, int b) : a(a), b(b) {}

    bool operator<(const team& t) 
    {
        if (a == t.a) return t.b > b;
        return a < t.a;
    }

    int cmp(const team& t) 
    {
        if (a == t.a) return t.b - b;
        return a - t.a;
    }

    void update(int p) 
    {
        a+=1;
        b += p;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    uset<int> ab;
    vector<team> teams(n);

    for (int i = 0; i < m; i++)
    {
        int t, p;
        cin >> t >> p;
        t--;

        teams[t].update(p);

        if (t==0)
        {
            vector<int> trm;
            for (int j : ab)
            {
                if (teams[0].cmp(teams[j]) >=0)
                    trm.push_back(j);
            }
            for (int x : trm)
                ab.erase(x);

        }
        if (teams[t].cmp(teams[0])>0) ab.insert(t);
        else ab.erase(t);
        cout << ab.size() + 1 << "\n";
    }
    return 0;

}
