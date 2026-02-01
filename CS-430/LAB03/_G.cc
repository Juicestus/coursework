#include <bits/stdc++.h>
using namespace std;

struct prof {
    int fav;
    int pos;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n ;
    cin >> n;
    vector<prof> profs(n);
    for (int i = 0; i < n; i++)
    {
        cin >> profs[i].fav;
        profs[i].pos = i + 1;
    }
    
    int I = 0;
    while (profs.size() > 1)
    {
        int k = profs[I].fav;
        I = (k - (profs.size() - I + 1)) % profs.size();
        profs.erase(profs.begin() + I);
        I += 1;
        I %= profs.size();
        //cout << I << "\n";
    }
    cout << profs[0].pos << "\n";
}
