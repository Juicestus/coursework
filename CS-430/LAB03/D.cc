#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int k;
    cin >> k;
    string before;
    string after;
    cin >> before;
    cin >> after;
    bool bad = false;

    for (int i = 0; i < before.size(); i++)
    {
        if (k % 2 == 1) {
            if (before[i] == after[i])
            {
                bad = true;
                break;
            }
        } else {
                //cout << "even\n";
            if (before[i] != after[i])
            {
                bad = true;
                break;
            }
        }
    }
    if (bad) cout << "Deletion failed";
    else cout << "Deletion succeeded";
        cout << "\n";



}
