#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll N, M;
    cin >> M >> N;

    vector<int> kids;
    ll sum = 0;
    for (int _N = N; _N--; )
    {
        int k;
        cin >> k;
        kids.push_back(k);
        sum += k;
    }
    //std::sort(kids.begin(), kids.end(), std::greater<int>());
    std::sort(kids.begin(), kids.end());
    
    //for (int i = 0; i < N; i++)
        //std::cout << kids.at(i) << "\n";

    ll anger = 0; 
    ll D = sum - M;
    for (int i = 0; i < N; i++)
    {
        ll nrem = N - i;
        ll each = D / N;
        ll rem = D % nrem;
        ll d = each;
        if (i < rem)d++;
        d = min(d, (ll)kids[i]);
        anger += d*d;
    }



       cout << anger << "\n";
}
