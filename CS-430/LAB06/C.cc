#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int l, d, n;
    cin >> l >> d >> n;

    if (n==0)
    {
        cout << (l-12)/d + 1 << "\n";
    }
    else 
    {
        vector<int> birds(n);
        for (int i = 0; i < n-1; i++)
        {
            cin >> birds[i];
        }
        sort(birds.begin(), birds.end());

        int a = 0;
        for (int i = 0; i < n-1; i++)
        {
            int k = (birds[i+1] - birds[i])/d - 1;
            if (k>0) a += k;
            //cout << a << "\n";
        }
	    if (birds[0] != 6) 
        {
			int k = (birds[0] - 6)/d;
			if (k > 0) a += k;
		}
		if (birds[n - 1] != l - 6) 
        {
			int k = (l - 6 - birds[n - 1])/d;
			if (k > 0) a += k;
		}
        cout << a << "\n";

    }

}


