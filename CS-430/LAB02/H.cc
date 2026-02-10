#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;
    vector<int> ws{};
    while (N--)
    {
        int k;
        cin >> k;
        ws.push_back(k);
    }
    
    long long c = 0;
    for (int i = ws.size() - 1; i > 0; i--)
    {
        if (ws[i] == 0) {
            cout << "1\n";
            return 0;
        }
        if (ws[i-1] + 1 < ws[i])    // we ok
                                    continue;


        int d = ws[i-1] - ws[i] + 1;
        c += d;
        ws[i-1] -= d;
    }
    cout << c << "\n";
}
