#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    map<string, ll> B;
    string R;
    cin >> R;

    map<string, set<string>> A;
    map<string, int> D;

    for (int i = 0; i < n; i++)
    {
        string c, a, b;
        cin >> c >> a>>b;

        B[a]=0;
        B[b]=0;
        B[c]=0;

        A[a].insert(c);
        A[b].insert(c);
        D[a]+=0;
        D[b]+=0;
        D[c] += 2;
    }
    B[R]= 1llu << 55;
    queue<string> DZ;
    for(auto& [N, d] : D) if(d==0) DZ.push(N);

    while (!DZ.empty())
    {
        string N = DZ.front();
        DZ.pop();

        for (auto K:A[N])
        {
            B[K] += B[N]>>1;
            D[K]--;
            if (!D[K]) DZ.push(K);
        }
    }

    string T="";
    for (int i = 0; i < m; i++)
    {
        string t;
        cin >> t;
        if (B[t] > B[T]) T =t;
    }
    cout << T << "\n";




}
