#include <bits/stdc++.h>
#include <queue>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    priority_queue<int> lq;
    priority_queue<int, vector<int>, greater<int>> hq;

    string s;
    while (cin >> s)
    {
        if (s == "#")
        {
            cout << hq.top() << "\n";
            hq.pop();

            if (hq.size() < lq.size())
            {
                hq.push(lq.top());
                lq.pop();
            }
        } else {
            int x = stoi(s);
            if (hq.empty() || x >= hq.top())
                hq.push(x);
            else lq.push(x);

            if (hq.size() > lq.size() + 1)
            {
                lq.push(hq.top());
                hq.pop();
            } 
            else if (lq.size() > hq.size() )
            {
                hq.push(lq.top());
                lq.pop();
            }
        }
    }
}
