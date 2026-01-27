#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int x = 0;
    int y = 0;
    int sx = 0, sy =0;

    vector<string> G(1, "*");  // list?

    string c;
    while (cin >> c)
    {
        if (c=="down")
        {
            if (++y >= G.size())
                G.push_back(string(G[0].size(), ' '));
        }



         if (c=="up")
        {
            if (--y < 0)
            {
                sy++;
                y++;
                G.insert(G.begin(), string(G[0].size(), ' '));
            }
        }

    if (c=="left")
        {
            if (--x <0)
            {
                sx++;
                x++;
                for( string& s : G)
                    s.insert(s.begin(), ' ');   //head
            }
        }

         if (c=="right")
        {
            if (++x >= G[0].size())
            {
                for( string& s : G)
                    s.push_back(' ');
            }
        }

     

         G[y][x] = '*';
    }

    G[sy][sx]='S';
    G[y][x] = 'E';  
    
    for (int i = 0; i < G[0].size()+2; i++)
        cout << '#';
    cout << '\n';
    for (string s : G)
        cout << '#' << s << "#\n";
    for (int i = 0; i < G[0].size()+2; i++)
        cout << '#';
    cout << '\n';

}
