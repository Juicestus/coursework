#include <bits/stdc++.h>
using namespace std;

int ds(int k)
{
    int s = 0, m = 1;
    while (k>0)
    {
        s += (k % 10);
        k/=10;
        m *= 10;
    }
    return s;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    while (true)
    {
        int N;
        cin >> N;
        if (N == 0) break;

        int t = ds(N);
        //std::cout << "->" << N << " " << t << "\n";

        for (int m = 10+1; m < 100000; m++)
        {
            if (ds(m*N) == t)
            {
                //cout  << "=>" << m << " " << ds(m*N) << "\n";
                cout << m << "\n";
                break;
            }
        }
    }


}
