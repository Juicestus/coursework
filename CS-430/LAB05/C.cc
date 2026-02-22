#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin>>n;
    vector<int> a(n);
    while(n--)
    {
        int d;
        cin >> d;
        vector<int> L(12);
        for (int i = 0; i < 12;i++)cin>> L[i];
        int c=0;

        for (int l = 1; l <= 10; l++)
        {
            for (int s = 1; s < 13-l; s++)
            {
                int m = INT_MAX;
                for (int i = s; i < s+l; i++)
                {
                    m=min(m, L[i]);
                }
                if (L[s-1] < m && L[s+l]<m) c++;
            }
        }
        cout<< d << " " << c << "\n";
    }


}
