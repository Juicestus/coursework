#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define MM 500000

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N;
    cin>>N;
    
    vector<char> u(MM+1, 0);

    int a = 0;
    for (int i = 0; i <N; i++)
    {
        int M;
        cin >> M;

        vector<int> t;
        t.reserve(M);

        bool ok=1;
        for(int j=0; j<M;j++)
        {
            int x;
            cin>>x;
            t.push_back(x);
            if (u[x]) ok=false;
        }

        if (ok)
        {
            a++;
            for (int x: t)
            {
                u[x]=1;
            }
        }
    }
    cout << a << "\n";



}
