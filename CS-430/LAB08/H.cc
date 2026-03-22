#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;
    ll k = 0;
    for (int i = n-1; i >= 0; i--)
    {
        char s;
        cin >> s;
        if (s == 'O')
            k |= (1llu << i);
    }

    cout << k << "\n"; 
}
