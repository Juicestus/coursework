#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int M;
    char P;
    string S;

    int IA[26]{0};
    int CT[26]{0};

    for(;;)
    {
        cin >> M >> P >> S;
        if (M == -1) break;
        if (CT[P-'A'] == 0)
        {
            if (S == "right")
                CT[P-'A'] = M;
            else
                IA[P-'A']++;
        }
    }
    long long s = 0, c = 0;
    for (char k = 'A'; k <= 'Z'; k++)
    {
        //cout << "CT[" << k << "] = " << CT[k-'A'] << "\t\t"
            //<< "IA[" << k << "] = " << IA[k-'A'] << "\n";
        if (CT[k-'A'] > 0)
        {
            c++;
            s += CT[k-'A'];
            s += 20 * IA[k-'A'];
        }
    }
   cout << c << " " << s;
}
