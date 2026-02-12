#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<int> par;
vector<set<int>> cc;

int find(int a)
{
    if (par[a]==a)return a;
    par[a] = find(par[a]);
    return par[a];
}

void merge(int a , int b)
{
    int x = find(a);
    int y = find(b);
    if (x==y) return;

    for (int i : cc[y])
    {
        cc[x].insert(i);
    }
    par[y]=x;
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<set<int>> rec(n);

    for (int i=0; i <n; i++)
    {
        int k;
        cin >> k;
        for (int j=0; j <k;j++)
        {
            int I;
            cin >> I;
            rec[i].insert(I);
        }
    }
    
#define N 1000000
    par.resize(N+1);
    cc.resize(N+1);
    for (int i=0; i <= N; i++)
    {
        par[i]=i;
        cc[i].insert(i);
    }

    int C =0;
    for (int _i=0; _i <n; _i++)
    {
        set<int> t = rec[_i];

        bool ok=false;

        if (!t.empty())
        {
            int f = *t.begin();
            int r = find(f);
            bool s=true;
            for (int i : t)
            {
                if (find(i)!=r) { s=false; break;}
            }
            if (s&&cc[r] == t) ok=true;
        }

        //if (ok)
        //{
            //C++;
        //}else {
        if (!ok) {

            set<int> rn;
            for(int i: t)
            {
                rn.insert(find(i));
            }
            set<int> mi;
            for (int r : rn)
            {
                for (int i : cc[r])
                {
                    mi.insert(i);
                }
            }

            if (mi == t)
            {
                ok=true;

                int f=*rn.begin();
                for (int r : rn)
                {
                    if (r!=f) merge(f, r);
                }
            }

        }
            if (ok)
                C++;
    }
    cout << C << "\n";



}
