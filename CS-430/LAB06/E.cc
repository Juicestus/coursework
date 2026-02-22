#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;
    string k;
    cin >> k;

    int i = 0;
    int d = 0;
    while (k.size() > 0)
    {   
        if (k[0] == 'M')  
        {
            if (d < n) 
            {
                d++;
                k.erase(0, 1);
            } else {
                if (k[1] == 'W')
                {
                    d--;
                    k.erase(1, 1);
                } else {
                    break;
                }
            }
        } 
        else if (k[0] == 'W') 
        {
            if (d > -n) 
            {
                d--;
                k.erase(0, 1);
            } else {
                if (k[1] == 'M')
                {
                    d++;
                    k.erase(1, 1);
                } else {
                    break;
                }
            }
        }
        i++;
    }
    cout << i << "\n";

}
