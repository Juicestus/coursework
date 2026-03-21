#include <bits/stdc++.h>
using namespace std;

using ll = long long;

deque<int> L{};
deque<int> R{};

void Bal()
{
    if (L.size() < R.size())
    {
        L.push_back(R.front());
        R.pop_front();
    }
    else if (L.size() > R.size() + 1)
        {
            R.push_front(L.back());
            L.pop_back();
        }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    while (n--)                         
    {                                   
        int N = L.size() + R.size();    
        string op;                      
        int x;                          
        cin >> op;                      
        cin >> x;                       
        if (op == "push_back")          
        {
            R.push_back(x);
            Bal();
           
        }
        if (op=="push_front")
        {
            L.push_front(x);
            Bal();
        }
        if (op == "push_middle")
        {
            if (L.size() > R.size())
            {
                R.push_front(x);
            } else {
                L.push_back(x);
            }
            Bal();
        }
        if (op == "get") 
        {
            if (x >= L.size())
            {
                x -= L.size();
                cout << R[x] << "\n";
            }
            else 
            {
                cout << L[x] << "\n";
            }
        }

    }
}
