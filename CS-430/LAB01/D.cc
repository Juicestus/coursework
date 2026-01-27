#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;
    string m;
    string f;
    string k;//\n
    getline(cin, k);

    getline(cin, m);
    getline(cin, f);
    
    int s = 0;
    for (int i = 0; i < m.size(); i++)
    {
        if (m[i] == f[i])
            s++;
    }
    
//cout << m.size() << " " << s << " " << n << "\n";
    cout << m.size() - abs(s - n) << "\n";
    //std::cout << (m.size() - s) + n;
}
