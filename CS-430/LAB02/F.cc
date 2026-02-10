#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    
    vector<int> lens;
    int n = 0;
    string line;
    while (getline(cin, line))
    {
        lens.push_back(line.size());
        if (line.size() > n)
            n = line.size();
    }
    long long k = 0;
    for (int i = 0; i < lens.size() - 1; i++)
    {
        int m = lens[i];
        k += (n- m) * (n-m);
        //cout << m << " " << m-n << " " << (n-m)*(n-m) << " " << k << "\n";
    }
    cout << k << "\n";

}
