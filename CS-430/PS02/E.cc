#include <bits/stdc++.h>
using namespace std;

struct ter{
    int h;
    int p;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    using ll = long long;
    stack<ter> s;

    int N;
    cin >> N;
    
    ll r = 0;
    for (int i = 0; i < N; i++)
    {
        int h;
        cin >> h;

        while (!s.empty() && s.top().h < h)
            s.pop();

        if (!s.empty() && s.top().h == h)
        {
            r += i - s.top().p-1;
            s.top().p = i;
        } else 
            s.push({h, i});
    }

    cout << r << "\n";
}
