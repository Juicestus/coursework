#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);


    int n ;
    cin >>n;
    vector<ll> v(n);
    for (int i=0; i <n; i++)
    {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    
    int s = 0;
    for (int i = v.size()-1; i>= 0; i--)
    {
        s++;
        if (v[i] < s)
        {
            cout << s-1 << "\n";
            return 0;
        } ;
    }
    cout << s << "\n";
}
