#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<int> B(n);
    for (int i = 0; i < n; i++)
        cin >> B[i];

    sort(B.begin(), B.end());

    int c = 0, l = 0;

    int i;
    for (i = 0; i < B.size(); i++) 
    {
        if (B[i] - c > B.size() - l)
            break;
        if(B[i] > c) c++;
    }

    c += B.size() - i;
    cout << c << "\n";

}
