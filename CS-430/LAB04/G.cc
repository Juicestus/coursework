#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;
    while (N--)
    {
        int n;
        cin >> n;
        vector<string> w(n);
        for (int i = 0; i < n; i++)
        {
            cin >> w[i];
        }
        sort(w.begin(), w.end());

        for (int i = 0; i < w.size() - 1; i++)
        {
            if (w[i+1].rfind(w[i]) == 0)
            {
                cout << "NO\n";
                goto done;
            } 
        }
        cout << "YES\n";
done:
    }


}
