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
    
  
    auto I = profs.begin();
    while (profs.size() > 1)
    {    

        int k = (distance(profs.begin(), I) + I->fav-1) % profs.size();
        I = profs.begin() + k;
        //cout << "erase " <<  I - profs.begin() << "\n";
        profs.erase(I);
        if (I == profs.end()) I = profs.begin();
    }
    cout << profs[0].pos << "\n";
}
