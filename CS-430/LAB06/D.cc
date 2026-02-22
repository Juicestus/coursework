#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);


    int p, n;
    cin >> p >> n;

    set<string> K{};

        for (int i = 1; i <= n; i++)
    {
        string k;
        cin >> k;
        K.insert(k);

        if (K.size() >= p)
        {
            cout << i << "\n";
            return 0;
        }
    }
        cout << "paradox avoided\n";


}
