#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    stack<int> S, I;

    int F = INT_MIN, mx = INT_MIN;

    for (int i = 0; i < n;i++)
    {
        int k;
        cin >> k;

        mx = max(mx, k);
        if (mx==k)
        {
            int f = -1;
            int M = INT_MIN, m = INT_MAX;

            while (!S.empty())
            {
                m = min(S.top(), m);
                M = max(S.top(), M);
    
                f=I.top();
                S.pop();
                I.pop();
            }
            if (i-f>1)
            {
                M = min(k, M);
                F = max(F, M-m);
            }
        }
        S.push(k);
        I.push(i);
    }

    int M = INT_MIN, m = INT_MAX;
    while (!S.empty())
            {
                if (S.top() >= M) {
                    if (m != INT_MAX) F = max(F, M-m);
                    M=S.top(); m=INT_MAX;
                }
                else {
                    m = min(S.top(), m);
                }
                I.pop();
                S.pop();
            }
    if (F<0) F=0;
    cout << F << "\n";


}
