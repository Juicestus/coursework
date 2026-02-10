#include <bits/stdc++.h>
#include <queue>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    while (1)
    {
        int n;  // c++ is so ugly
        if (!(cin >> n)) break;

        queue<int> Q;
        stack<int> S;
        priority_queue<int> PQ;
        bool q = 1, s = 1, pq  =1;

        for (int i = 0; i < n; i++)
        {
            int op, v;
            cin >> op >> v;

            if (op == 1)
            {
                Q.push(v);
                S.push(v);
                PQ.push(v);
            }
            else if (op == 2)
            {
                if (Q.empty() || Q.front() != v) q=0;
                if (!Q.empty()) Q.pop();

                if (S.empty() || S.top() != v)s= 0;
                if (!S.empty()) S.pop();

                if (PQ.empty() || PQ.top() != v) pq=0;
                if (!PQ.empty()) PQ.pop();
            }
        }
    
        if (q && !s && !pq) cout << "queue\n";
        else if (!q && s && !pq) cout << "stack\n";
        else if (!q && !s && pq) cout << "priority queue\n";
        else if (!q && !s && !pq) cout << "impossible\n";
        else cout << "not sure\n";

    }
}
