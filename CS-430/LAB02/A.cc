#include <bits/stdc++.h>
using namespace std;

vector<int> bins{};
int sum = 0;

int rec(int i)
{
    if (bins[i] < 2)
    {
        rec(i+1); 
    }
    

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    bins.push_back(0);

    int n; 
    cin >> n;
    for (int i = n-1; i--; )
    {
        int k;
        cin >> k;
        bins.push_back(k);
    }


}
