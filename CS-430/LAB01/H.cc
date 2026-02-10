#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    // take stack and give stack 
    //
    // any time you take dishes => go onto the take stack (1)
    // any time you give dishes => from the give stack (2)
    // any time the give stack is empty => move whole take to give
    //

    while (true)
    {
        int n;
        cin >> n;
        if (n == 0) break;
        //string _;
        //getline(cin, _);
        //
        int s1 = 0, s2 = 0;

        while (n--)
        {
            string a, c;
            cin >> a >> c;
            if (a == "TAKE")
            {
                s1+=c;
            }
            if (a == "DROP")
            {
                s2 = s1;
                s1 = 0;
                s2 -= c;
                // give c
            }



        }

    }


}
