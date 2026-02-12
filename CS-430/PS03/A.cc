#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<int> parent;
vector<int> sz;
vector<ll> sum;
vector<int> id;

int find(int a)
{
    if (parent[a]==a) return a;
    parent[a] = find(parent[a]);
    return parent[a];
}

void merge(int a, int b)
{
    int x = find(id[a]);
    int y = find(id[b]);
    if (x==y) return;

    if (sz[x]<sz[y])
    {
        parent[x]=y;
        sz[y] += sz[x];
        sum[y] += sum[x];
    }
    else
    {
        parent[y]=x;
        sz[x] += sz[y];
        sum[x] += sum[y];
    }
}

int nid = 0;

void move(int a, int b)
{
    int x = find(id[a]);
    int y = find(id[b]);

    sz[x]--;
    sum[x] -= a;

    id[a] = nid;

    parent[nid] = y;
    sz[y]++;
    sum[y] += a;
    nid++;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n, m;
    while (cin >> n >> m)
    {
        nid = n+1;
        parent.resize(2*n+100000);
        sz.resize(2*n+100000);
        sum.resize(2*n+100000);
        id.resize(n+1);
        
        for (int i = 1; i <=n; i++)
        {
            parent[i] = i;
            sz[i] = 1;
            sum[i] = i;
            id[i] = i;
        }

        for (int i = 0; i < m; i++)
        {
            int op, p, q;
            cin >> op;
            if (op==1)
            {
                cin >> p >> q;
                merge(p, q);
            } else if (op==2)
            {
                cin >> p >> q;
                move(p, q);
            }
            else {
                cin >> p;
                int r = find(id[p]);
                cout << sz[r] << " " << sum[r] << "\n";
            }
        }

    }

}
