#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int N;
    std::cin >> N;
    int K = 0;
    while (N--)
    {
        priority_queue<int, vector<int>, greater<int>> ag;
        priority_queue<int, vector<int>, greater<int>> am;

        int ng, nm, k;
        std::cin >> ng >> nm;
        //std::cout << ng << " " << nm << "\n";
        while (ng--)
        {
            cin >> k;
            ag.push(k);
        }
        while (nm--)
        {
            cin >> k;
            am.push(k);
        }
        
        while (!ag.empty() && !am.empty())
        {
            //std::cout << ag.size() << " " << am.size() << "\n";
            if (am.top() <= ag.top())
                am.pop();
            else 
                ag.pop();
        }

        if (ag.size() > am.size())
            cout << "Godzilla";
        else cout << "MechaGodzilla";
        cout << "\n";
    }
}
