#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define NN 500000
int tree[NN];

void U(int i, int v)
{
    while(i<NN)
    {
        tree[i]+=v;
        i+=i & (-i);
    }
}

int Q(int i)
{
    int t = 0;
    while (i >0)
    {
        t += tree[i];
        i -= i & (-i);
    }
    return t;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int T;
    cin >> T;

    while(T--)
    {
        int nm, nr;
        cin >> nm >> nr;

        for (int i = 0; i < NN; i++)
        {
            tree[i] = 0;
        }
        int c[nm+1];

        for (int i = 1; i <= nm; i++)
        {
            U(i, 1);
            c[i] = nm - i + 1;
        }

        for (int i = 0, C = nm; i < nr; i++)
        {
            int mid;
            cin >> mid;

            C++;

            int I = c[mid];
            int T = Q(I);

            U(c[mid], -1);

            c[mid] = C;
            U(c[mid], 1);

            if (i>0) cout << " ";
            cout << (nm-T);
        }
        cout << "\n";
    }

    return 0;
}
