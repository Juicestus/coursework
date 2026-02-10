#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;
    vector<int> ns;
    ns.reserve(n);
    while (n--)
    {
        int k;
        cin >> k;
        ns.push_back(k);
        //std::cout<<k<<"\n";
    }
    sort(ns.begin(), ns.end());
    //int l = INT32_MAX;
    int l = 0;
    vector<vector<int>> ser{};
    ser.push_back(vector<int>());

    for (int i = 0; i < ns.size(); i++)
    {
        int cur = ns[i];
        auto k = ser.back();
        if (!k.empty() && k.back() + 1 == cur)
        {
            ser.back().push_back(cur);
        } else{ 
            ser.push_back(vector<int>());
            ser.back().push_back(cur);
        }
    }
    
    string res = "";
    for (auto v : ser)
    {
        if (v.size() > 2)
        {
            res += to_string(v.front()) + "-" + to_string(v.back()) + " ";
        }
        else 
            for (int e : v)
                res += to_string(e) + " ";
    }
    cout << res << "\n";
}
