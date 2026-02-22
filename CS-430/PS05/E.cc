#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    double l, w;
    while (cin >>n>>l>>w)
    {
        vector<pair<double, double>> ivals;
        for(int i = 0; i < n; i++)
        {
            double x, R;
            cin>>x>>R;
            if (R<(w/2.0)) continue;
            double dx = sqrt(R*R - (w/2.0) * (w/2.0));
            double l = x - dx, r = x + dx;
            ivals.push_back({l, r});
        }

        sort(ivals.begin(), ivals.end());

        double c = 0.0;
        int i = 0, u = 0;

        bool ok= true;

        while (c < l)
        {
            double b = c;
            while (i<ivals.size() && ivals[i].first <= c)
                b = max(b, ivals[i++].second);
            if (b==c) { 
                ok=false; break; }

            c=b;
            u++;
        }

        if(!ok) cout << "-1\n";
        else cout << u << "\n";
    }
    return 0;

}
