#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<int> tree;

void U(int i, int d)
{
    while (i<=n)
    {
        tree[i] += d;
        i += i & (-i);
    }
}

int Q(int i)
{
    int s = 0;
    while (i > 0)
    {
        s += tree[i];
        i -= i&(-i);
    }
    return s;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);


    int N, K;
    cin >> N >> K;
    n=N;

    tree = vector<int>(N+1, 0);
    vector<int> b(N+1, 0);

    while (K--)
    {
        char t;
        cin >> t;
        
        if (t=='F')
        {
            int i;
            cin>>i;
            if (b[i]==0)
            {
                b[i]=1;
                U(i, 1);
            } else {
                b[i]=0;
                U(i, -1);
            }
        }
        else 
        {
            int l, r;
            cin >> l >> r;
            cout << Q(r) - Q(l-1) << "\n";
        }
    }


}
