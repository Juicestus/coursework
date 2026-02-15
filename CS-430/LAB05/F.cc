#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<int> ppl;
vector<double> mon;

int find(int i )
{
    if (ppl[i] == i) return i;

    return find(ppl[i]);
}

void unin(int i, int j)
{
    int ir = find(i);
    int jr = find(j);
    ppl[ir] = jr;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    ppl.resize(n * 100);
    mon.resize(n * 100);
    for (int i = 0; i < n; i++)
    {
        ppl[i] = i;
        int I;
        cin >> I;
        mon[i] = I;
    }
    for (int i = 0 ; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
        //int a = (ppl[l] + ppl[r]) / 2;
        //ppl[l] = a;
        //ppl[r] = a;
        //
        unin(l, r);
    }
    
    vector<int> res(n * 10, 0);
    for (int i = 0; i < n; i++)
    {
        //cout << i << " " << ppl[i] << "\n";
        int k = find(i);
        res[k] += mon[i];
        //if (ppl[i] < 0) {
            //cout << "IMPOSSIBLE\n";
            //return 0;
        //}
    }
    for (int i = 0; i < n; i++)
    {
        if (res[i] != 0)
        {
            
    cout << "IMPOSSIBLE\n";
    return 0;
        }
    }
    cout << "POSSIBLE\n";
    return 0;
}
