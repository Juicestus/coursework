#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    string k;
    getline(cin, k);
    while (n--)
    {
        string w;
        getline(cin, w);
        int m = ceil(sqrt(w.size()));
        int M = m * m;
        int i, j;
        vector<vector<char>> in{};
        for (i  =0; i < m; i++)
        {
            in.push_back(vector<char>());
            in.back().resize(m);
            for (j  =0; j < m; j++)
            {
                int I = i * m + j;
                if (I >= w.size())
                    in[i][j] = '*';
                else
                    in[i][j] = w[I];
            }
        }

        auto out(in);
        for (i  =0; i < m; i++)
        {
            //out.push_back(vector<char>());
            //out.back().resize(m+1);
            for (j  =0; j < m; j++)
            {
                //std::cout << in[i][j] << " ";
                //std::cout << i << " " << j << " -> " << j << " " << m-i-1 << "\n";
                out[j][m-i-1] = in[i][j];
            }
            //cout << "\n";
        }
        //std::cout << "bruh\n";
        string res = "";
        for (i  =0; i < m; i++)
        {
            for (j  =0; j < m; j++)
            {
                //std::cout << out[i][j] << " ";
                char k = out[i][j];
                if (k != '*')
                    res += k;
            }
            //cout << "\n";
        }
        std::cout << res << "\n";
    }
}
