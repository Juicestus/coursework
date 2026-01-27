#include <bits/stdc++.h>
using namespace std;



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    int I = 1;
    while (n--)
    {
    
        string N, S, T;
        cin >> N >> S >> T;

        reverse(N.begin(), N.end());

        long long k = 0;
        for (int i = 0; i < N.size(); i++)
        {
            for (int j = 0; j < S.size(); j++)
            {
                if (N[i] == S[j])
                    k += j * pow(S.size(), i); 
            }
        }

        string O = "";
        while (k > 0)
        {
            O += T[k % T.size()] ;
            k /= T.size();
        }

        reverse(O.begin(), O.end());
        cout << "Case #" << I++ << ": " << O << "\n";
        
    }

}
