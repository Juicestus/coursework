#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;
    
    vector<int> v(N, 0), M(N), m(N);
    
    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }
    
    M[0]=v[0];
    for (int i = 1; i < N; i++)
        if (v[i] > M[i-1])
            M[i]=v[i];
        else M[i]=M[i-1];

    m[N-1]=v[N-1];
    for (int i = N-2; i >= 0; i--)
        if (v[i] < m[i+1])
            m[i]=v[i];
        else m[i]=m[i+1];

    long long C = 0;
    if (v[0] <m[1]) C++;
    if (v[N-1] > m[N-2])C++;

    for (int i = 1; i < N-1; i++)
    {
        if (v[i] < m[i+1] && v[i] > M[i-1])
            C++;
    }

    cout << C;
}
