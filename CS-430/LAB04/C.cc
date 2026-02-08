#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    while(true)
    {
        cin >> n;
        if (n==0) break;
    
        int mc = 0;
        string mw = "";
        while (n--)
        {
            string k;
            cin >> k;
            if (mw == "") mw = k;
            int c = 0;
            for (int i = 0; i < k.size()-1; i++)
            {
                if (k[i] == 'a'
                        || k[i] == 'e'
                        || k[i] == 'i'
                        || k[i] == 'o'
                        || k[i] == 'u'
                        || k[i] == 'y')
                {
                    if (k[i] == k[i+1]) { c++; }
                }
            }
            if (c > mc)
            {
                mc = c;
                mw = k;
            }
        }
        cout << mw << "\n";
    }


}
