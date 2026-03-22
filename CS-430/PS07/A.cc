#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int F(int m, vector<int>& p, int N, int W)
{
    int l = 0, r = m-1, i = 0;
    int c = 0;
    while(l<=r)
    {
        c++;
        
        if (i == W)return c;
        if (p[i]>r) l = p[i];
        else 
        {
            while (i < W && p[i]<=r) i++;
            l = r+1;
        }
        r = l+m - 1;
        if (r > N-1) r=N-1;
    }
    return c;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int T;
    cin>>T;
    while (T--)
    {
        int N, W, L;
        cin >> N>>W>>L;
        vector<int> p(W);
        for (int i=0; i <W; i++)
        {
            int I;
            cin>>I;
            p[i] = I-1;
        }

        int l = 1, r = N;
        while (l < r)
        {
            int m = (l+r)/2;
            if (F(m, p, N, W) <= L) r = m;
            else l = m+1;

        }
        cout << l << "\n";
    }
}
