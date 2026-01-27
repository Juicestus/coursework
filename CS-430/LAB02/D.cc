#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M;
    cin >> N >> M;

    vector<int> kids;
    for (int _N = N; _N--; )
    {
        int k;
        cin >> k;
        kids.push_back(k);
    }
    
    int g = 0; 
    while (g < M)
    {
        int m = INT32_MAX;
        for (int i =0; i < N; i++)
        {
            if (kids[i] > 0 && kids[i] < m)
            {
                m = kids[i];
            }
        }

        if (m * N > M)
        {
            
            break;
        }
    }

}
