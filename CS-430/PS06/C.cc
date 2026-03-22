#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n,k;
    cin >>n>>k;
    double E = (n+1.0)/2.0;
    for (int j = 2; j<=k;j++)
    {
        int T = (int)ceil(E);
        T = max(T, 1);
        if (T>n)
            continue;
        int k = n-T+1;
        double sk = (double)(T+n) * (k/2.0);
        E = (sk + (double)(T-1) * E) / n;
    }
    //cout << E << "\n";
    printf("%.15f\n", E);

}
