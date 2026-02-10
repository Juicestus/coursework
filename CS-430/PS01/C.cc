#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    vector<long long> c{};
    c.push_back(0);
    c.push_back(0);
    c.push_back(0);

    string s;
    cin >> s;

    for (char k : s)
    {
        c[k-'0']++;
    }


    long long S = 0;
    for (char k : s)
    {
        if (k == '0') c[0]--;
        else S+= c[0];
    }


    for (char k : s)
    {
        if (k=='1') c[1]--;
        if (k == '2') S +=c[1];
    }

    cout << S << "\n";

}
