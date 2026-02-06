#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    while (1)
    {
        int n, b;
        cin >> n >> b;
        if (n == -1) break;

        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        int l = 0, h = 0;
        for (int i = 0; i < n; i++)
            h = max(h, a[i]);
    
        while (l < h)
        {
            int m = (l+h)/2;
            int d = 0;
            for (int i = 0; i < n; i++)
            {
                d += (a[i]+m-1) / m;
            }
            if (d > b) l = m+1;
            else 
                h = m;
        }
        cout << l << "\n";
    }
}
