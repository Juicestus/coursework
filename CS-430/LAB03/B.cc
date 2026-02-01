#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct team {
    string name;
    ll pl;
};

bool cmp(const team& a, const team& b)
{
    return a.pl < b.pl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);


    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<team> teams(n);

        for (int i = 0; i < n; i++)
        {
            cin >> teams[i].name;
            cin >> teams[i].pl;
        }

        std::sort(teams.begin(), teams.end(), cmp);
        
        ll P = 1, b = 0;
        for (int i = 0; i < n; i++)
        {
            ll d = teams[i].pl;
            //std::cout << teams[i].name << " " << d << " " << P << " ";
            b += abs(P - d);
            P++;
        }
    
        cout << b << "\n";
    }



}
